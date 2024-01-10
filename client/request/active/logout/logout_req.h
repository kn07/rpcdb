#pragma once

#include <active/active_req.h>

#include <string>

using std::string;

class logout_req : public active_req {
private:
    string username;

public:
    logout_req();
    ~logout_req();

protected:
    virtual command_type get_command() override;
    virtual request create(istringstream* stream) override final;
};
