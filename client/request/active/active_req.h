#pragma once

#include <request.h>

class active_req : public create_request {
protected:
    active_req();
    ~active_req();

    void throw_param_error();

    void check();
    virtual command_type get_command() = 0;
};
