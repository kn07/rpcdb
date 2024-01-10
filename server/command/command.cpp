#include "command.h"

#include <server.h>

#include <exception>
#include <unordered_map>
#include <utility>

using std::exception;

command::command()
{
}

command::~command()
{
}

bool command::user_exists(string username)
{
	auto it = server_::active_users->find(username);

	if (it == server_::active_users->end())
		return false;

	return true;
}

bool command::session_key_exists(unsigned long key)
{
	auto it = server_::db->find(key);

	return it == server_::db->end() ? false : true;
}

void command::insert_new_user(string username, unsigned long key)
{
	server_::active_users->insert({ username, key });
	server_::db->insert({ key, new vector<sensor_data>() });
}

void command::remove_user(string username, unsigned long key)
{
	server_::active_users->erase(username);
	server_::db->erase(key);
}

// void command::cleanup_db()
// {
// 	unordered_map<unsigned long, vector<sensor_data> *> *db_cache =
// 		new unordered_map<unsigned long, vector<sensor_data> *>();

// 	for (auto it : *server_::active_users) {
// 		db_cache[it.second] = server_::db[it.second];
// 		server_::db->erase(it.second);
// 	}

// 	for (auto it : *server_::db) {
// 		delete it.second;
// 	}

// 	delete server_::db;

// 	server_::db = db_cache;
// }

unsigned long command::get_user_key(string username)
{
	auto it = server_::active_users->find(username);

	if (it == server_::active_users->end())
		return 0;

	return it->second;
}

vector<sensor_data> *command::get_user_db(unsigned long key)
{
	auto it = server_::db->find(key);

	if (it == server_::db->end())
		throw exception();

	return it->second;
}

response command::execute(request *req)
{
	if (req->type != get_command())
		throw exception();

	return perform(req);
}
