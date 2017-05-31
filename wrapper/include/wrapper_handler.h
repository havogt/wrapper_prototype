#pragma once

class wrapper_handler {
  public:
    virtual void push() = 0;
    virtual void pull() = 0;
};
