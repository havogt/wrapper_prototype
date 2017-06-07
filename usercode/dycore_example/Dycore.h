#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <storage/storage-facility.hpp>
#include "../../wrapper/include/wrappable.h"
#include "dycore_helper.h"

class Configuration {

};
class ConstantFields {

};

class Dycore {
public:
    Dycore(Configuration&& config, ConstantFields&& constantFields):
        m_config(config), m_constantFields(constantFields)
    {

    }

    /**
     * This is an example of the consistency check handling.
     * Some operations shoud be abstracted, e.g. outdate operation.
     */
    template < typename Input, typename Output >
    void DoStep(Input input, Output output) {
        auto & [ u, v ] = input;
        auto & [out] = output;

        // invalidate the output on the fortran side as we are going to change it!
        for_each_in_tuple([](auto &field) { field.fortran_is_uptodate = false; }, output);

        // Do the great timestep
        // do_stuff(input(u),output(out));

        // invalidate all input fields as they are now consumed and should be updated in fortran
        for_each_in_tuple([](auto &field) { field.cpp_is_uptodate = false; }, input);
    }
private:
    Configuration m_config;
    ConstantFields m_constantFields;
};
