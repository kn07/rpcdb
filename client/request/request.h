#pragma once

#include <rpcdb.h>

#include <sstream>
#include <string>

using std::istringstream;
using std::string;

class create_request {
protected:
    create_request();

    /* client_ modifiers begin */
    bool get_logged_in();
    void set_logged_in(bool value);

    bool get_cmd_issued();
    void set_cmd_issued(bool value);

    string get_username();
    void set_username(string username);

    unsigned long get_session_key();
    void set_session_key(unsigned long session_key);
    /* client_ modifiers end */

    void throw_login_error();

    virtual void check() = 0;
    virtual request create(istringstream* stream) = 0;

public:
    virtual ~create_request();

    request generate(istringstream* stream);
};
