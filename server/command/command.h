#pragma once

#include <rpcdb.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

class command {
protected:
    response res;

protected:
    command();

    /* NOTE: Server checkers begin. */
    bool user_exists(string username);
    bool session_key_exists(unsigned long key);

    void insert_new_user(string username, unsigned long key);
    void remove_user(string username, unsigned long key);
    unsigned long get_user_key(string username);
    vector<sensor_data>* get_user_db(unsigned long key);
    /* NOTE: Server checkers end. */

    virtual command_type get_command() = 0;
    virtual response perform(request* req) = 0;

public:
    virtual ~command();

    response execute(request* req);
};
