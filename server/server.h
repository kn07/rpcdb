#pragma once

#include <command/command.h>

#include <rpcdb.h>

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

class server_ {
private:
    static unordered_map<string, unsigned long>* active_users;
    static unordered_map<unsigned long, vector<sensor_data>*>* db;

    static unordered_map<command_type, command*>* commands;

private:
    server_();

private:
    static void init_resources();
    static void init_commands();

public:
    static void init();
    static response execute(request* req);

    friend class command;
    friend class interpret_request;
    friend class create_response;
};
