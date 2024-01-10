#pragma once

#include <active/active_req.h>

#include <vector>

using std::vector;

class empty_req : public active_req {
protected:
    vector<float>* values;

protected:
    empty_req();
    virtual ~empty_req();

    void parse_input(istringstream* stream, sensor_data* data);

    request create(istringstream* stream);
};
