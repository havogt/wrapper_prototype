#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <storage/storage-facility.hpp>
#include "../../wrapper/include/wrappable.h"
#include "dycore_helper.h"

#include <memory>
#include "Dycore.h"
/**
 * This is just an example to attach to state flags to the storage to allow a consistency check between fortran and cpp
 */
template < typename DataStore >
struct dycore_field {
    bool cpp_is_uptodate;
    bool fortran_is_uptodate;
    DataStore field;
};

class DycoreWrapper : public wrappable {
  public:
    abstract_storage_info get_abstract_storage_info(std::string name, std::vector< int > dims) override {
        return make_abstract_storage_info(storage_info_t(dims[0], dims[1], dims[2]));
    }

    void init_optional(std::string name, std::vector< int > dims, bool external_ptr, void *ptr) override {
        if (m_fields.count(name) == 0) {
            storage_info_t meta_data(dims[0], dims[1], dims[2]);
            if (external_ptr) {

                m_fields.emplace(name,
                    dycore_field< data_store_t >{true,
                        true,
                        data_store_t(meta_data, (float_type *)ptr, gridtools::ownership::ExternalCPU, name)});
                std::cout << "initialized a new gridtools field in pointer sharing mode" << std::endl;
            } else {
                m_fields.emplace(name, dycore_field< data_store_t >{true, true, data_store_t(meta_data, name)});
                std::cout << "initialized a new gridtools field" << std::endl;
            }
        }
    }

    void *get_pointer(std::string name) override {
        if (m_fields.count(name) > 0) {
            return (void *)m_fields[name].field.get_storage_ptr()->get_cpu_ptr();
        } else
            return nullptr;
    }

    void notify_push(std::string name) override { m_fields[name].cpp_is_uptodate = true; };
    void notify_pull(std::string name) override { m_fields[name].fortran_is_uptodate = true; };

    virtual int call(const std::string &action) override {
        if (action == "init") {
            std::cout << "Init" << std::endl;
            // Prepare configuration
            Configuration config;
            ConstantFields constantFields;
            m_dycore = std::make_unique<Dycore>(std::move(config), std::move(constantFields));
            return WRAPPER_RETURN_SUCCESS;
        }
        if (action == "DoStep") {
            if (m_dycore == nullptr) {
                throw std::runtime_error("The Dycore is not initalized yet");
            }
            if (!check_cpp_fields_uptodate()) {
                throw std::runtime_error("C++ fields are not up-to date");
            }
            m_dycore->DoStep(input(m_fields["some_input"], m_fields["some_input"]), output(m_fields["some_output"]));
            // Do some stuff to the fortran fields
            return WRAPPER_RETURN_SUCCESS;
        }

        if (action == "check_cpp_fields_uptodate") {
            return check_cpp_fields_uptodate();
        }
        if (action == "check_fortran_fields_uptodate") {
            return check_fortran_fields_uptodate();
        }
        throw std::runtime_error("DycoreWrapper.h: Action "+action+" is unknown");
    }

    bool check_cpp_fields_uptodate() {
        bool uptodate = true;
        for (auto &field : m_fields) {
            uptodate = uptodate && field.second.cpp_is_uptodate;
        }

        if (!uptodate)
            std::cout << "a cpp field is not up-to-date." << std::endl;
        else
            std::cout << "all fields are up-to-date. NICE!" << std::endl;

        return uptodate;
    }

    bool check_fortran_fields_uptodate() {
        bool uptodate = true;
        for (auto &field : m_fields) {
            uptodate = uptodate && field.second.fortran_is_uptodate;
        }
        return uptodate;
    }

  private:
    std::map< std::string, dycore_field< data_store_t > > m_fields;
    std::unique_ptr<Dycore> m_dycore = nullptr;
};
