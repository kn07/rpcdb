#include <server.h>

#include <command_list.h>

#include <iostream>
#include <stdexcept>

using std::exception;

unordered_map<string, unsigned long>* server_::active_users = nullptr;
unordered_map<unsigned long, vector<sensor_data>*>* server_::db = nullptr;

unordered_map<command_type, command*>* server_::commands = nullptr;

server_::server_()
{
}

void server_::init_commands()
{
    server_::commands = new unordered_map<command_type, command*>();
    server_::commands->insert({ LOGIN_CMD, new cmd_login() });
    server_::commands->insert({ LOGOUT_CMD, new cmd_logout() });
    server_::commands->insert({ ADD_CMD, new cmd_add() });
    server_::commands->insert({ UPDATE_CMD, new cmd_update() });
    server_::commands->insert({ DELETE_CMD, new cmd_delete() });
    server_::commands->insert({ READ_CMD, new cmd_read() });
    server_::commands->insert({ READ_ALL_CMD, new cmd_read_all() });
    server_::commands->insert({ GET_STAT_CMD, new cmd_get_stat() });
    server_::commands->insert({ GET_STAT_ALL_CMD, new cmd_get_stat_all() });
    server_::commands->insert({ LOAD_CMD, new cmd_load() });
    server_::commands->insert({ STORE_CMD, new cmd_store() });
}

void server_::init_resources()
{
    server_::active_users = new unordered_map<string, unsigned long>();
    server_::db = new unordered_map<unsigned long, vector<sensor_data>*>();
}

void server_::init()
{
    server_::init_resources();
    server_::init_commands();
}

response server_::execute(request* req)
{
    if (req == nullptr)
        throw exception();

    return server_::commands->at(req->type)->execute(req);
}
