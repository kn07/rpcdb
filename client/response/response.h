#pragma once

#include <rpcdb.h>

#include <string>

using std::string;

class interpret_response {
protected:
    interpret_response();

public:
    virtual ~interpret_response();

    int interpret(response* res);

protected:
    bool get_logged_in();
    void set_logged_in(bool value);

    string get_username();
    void set_username(string username);

    unsigned long get_session_key();
    void set_session_key(unsigned long session_key);

    virtual command_type get_command() = 0;
    virtual int perform(response* res) = 0;
};
