#include "status_codes.h"
#include <call_rpc_list.h>
#include <input_list.h>
#include <request_list.h>
#include <response_list.h>

#include <rpcdb.h>

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#define WRONG_PARAMS_ERROR "Wrong parameters."
#define USAGE_FORMAT "usage: %s server_host input_file\n"

#define INTERACTIVE_OPTION "-i"

#define EXEC_ARG 0
#define HOST_ARG 1
#define FILENAME_ARG 2
#define OPTION_ARG 2
#define ARG_COUNT 3

#define LOGIN_COMMAND "login"
#define LOGOUT_COMMAND "logout"
#define LOAD_COMMAND "load"
#define STORE_COMMAND "store"
#define ADD_COMMAND "add"
#define DELETE_COMMAND "delete"
#define UPDATE_COMMAND "update"
#define READ_COMMAND "read"
#define READ_ALL_COMMAND "read_all"
#define GET_STAT_COMMAND "get_stat"
#define GET_STAT_ALL_COMMAND "get_stat_all"

#define UNRECOGNIZED_COMMAND "Unrecognized command."

#define LINE_BREAK "----------------------------------------"

using std::cerr;
using std::cout;
using std::endl;

using std::strcmp;

using std::bad_alloc;
using std::domain_error;
using std::invalid_argument;
using std::logic_error;
using std::out_of_range;
using std::runtime_error;

using std::unordered_map;

void init_commands(unordered_map<string, command_type> *commands)
{
	commands->insert({ LOGIN_COMMAND, LOGIN_CMD });
	commands->insert({ LOGOUT_COMMAND, LOGOUT_CMD });
	commands->insert({ LOAD_COMMAND, LOAD_CMD });
	commands->insert({ STORE_COMMAND, STORE_CMD });
	commands->insert({ ADD_COMMAND, ADD_CMD });
	commands->insert({ DELETE_COMMAND, DELETE_CMD });
	commands->insert({ UPDATE_COMMAND, UPDATE_CMD });
	commands->insert({ READ_COMMAND, READ_CMD });
	commands->insert({ READ_ALL_COMMAND, READ_ALL_CMD });
	commands->insert({ GET_STAT_COMMAND, GET_STAT_CMD });
	commands->insert({ GET_STAT_ALL_COMMAND, GET_STAT_ALL_CMD });
}

void destroy_commands(unordered_map<string, command_type> *commands)
{
	delete commands;
}

void init_requests(unordered_map<command_type, create_request *> *requests)
{
	requests->insert({ LOGIN_CMD, new login_req() });
	requests->insert({ LOGOUT_CMD, new logout_req() });

	requests->insert({ ADD_CMD, new add_req() });
	requests->insert({ UPDATE_CMD, new update_req() });

	requests->insert({ DELETE_CMD, new delete_req() });
	requests->insert({ READ_CMD, new read_req() });
	requests->insert({ GET_STAT_CMD, new get_stat_req() });

	requests->insert({ READ_ALL_CMD, new read_all_req() });
	requests->insert({ GET_STAT_ALL_CMD, new get_stat_all_req() });

	requests->insert({ LOAD_CMD, new load_req() });
	requests->insert({ STORE_CMD, new store_req() });
}

void destroy_requests(unordered_map<command_type, create_request *> *requests)
{
	for (auto it = requests->begin(); it != requests->end(); it++)
		delete it->second;

	delete requests;
}

void init_responses(unordered_map<command_type, interpret_response *> *responses)
{
	responses->insert({ LOGIN_CMD, new login_res() });
	responses->insert({ LOGOUT_CMD, new logout_res() });
	responses->insert({ LOAD_CMD, new load_res() });
	responses->insert({ STORE_CMD, new store_res() });
	responses->insert({ ADD_CMD, new add_res() });
	responses->insert({ DELETE_CMD, new delete_res() });
	responses->insert({ UPDATE_CMD, new update_res() });
	responses->insert({ READ_CMD, new read_res() });
	responses->insert({ READ_ALL_CMD, new read_all_res() });
	responses->insert({ GET_STAT_CMD, new get_stat_res() });
	responses->insert({ GET_STAT_ALL_CMD, new get_stat_all_res() });
}

void destroy_responses(
	unordered_map<command_type, interpret_response *> *responses)
{
	for (auto it = responses->begin(); it != responses->end(); it++)
		delete it->second;

	delete responses;
}

int main(int argc, char *argv[])
{
	call_rpc *rpc;
	input_controller *input;
	int code = EXIT_SUCCESS;

	unordered_map<string, command_type> *commands;
	unordered_map<command_type, create_request *> *requests;
	unordered_map<command_type, interpret_response *> *responses;

	try {
		if (argc < ARG_COUNT)
			throw invalid_argument(WRONG_PARAMS_ERROR);

		rpc = new call_rpc();
		rpc->init(argv[HOST_ARG]);

		if (strcmp(argv[OPTION_ARG], INTERACTIVE_OPTION) == 0)
			input = new stdin_input();
		else
			input = new file_input(argv[FILENAME_ARG]);

		commands = new unordered_map<string, command_type>();
		init_commands(commands);

		requests = new unordered_map<command_type, create_request *>();
		init_requests(requests);

		responses =
			new unordered_map<command_type, interpret_response *>();
		init_responses(responses);

		status_codes::init();
	} catch (invalid_argument &e) {
		cerr << e.what() << endl;
		fprintf(stderr, USAGE_FORMAT, argv[EXEC_ARG]);

		code = EINVAL;
	} catch (bad_alloc &e) {
		cerr << e.what() << endl;

		code = ENOMEM;
	} catch (runtime_error &e) {
		cerr << e.what() << endl;

		code = EPROTO;
	}

	if (code != EXIT_SUCCESS)
		return code;

	while (input->get_next_line()) {
		string token;
		command_type cmd;
		create_request *req;
		interpret_response *res;
		request gen_req;
		response *gen_res;

		try {
			token = input->get_command();
			cmd = commands->at(token);

			auto it_req = requests->find(cmd);
			req = it_req->second;

			auto it_res = responses->find(cmd);
			res = it_res->second;

			gen_req = req->generate(input->get_command_stream());
			gen_res = rpc->get_response(gen_req);

			code = res->interpret(gen_res);
		} catch (runtime_error &e) {
			cout << e.what() << endl;
		} catch (out_of_range &e) {
			cout << UNRECOGNIZED_COMMAND << endl;
		} catch (domain_error &e) {
			cerr << e.what() << endl;
		} catch (logic_error &e) {
			cerr << e.what() << endl;
			code = -1;
			break;
		}

		cout << LINE_BREAK << endl;
	}

	delete rpc;
	delete input;

	destroy_commands(commands);
	destroy_requests(requests);
	destroy_responses(responses);
	status_codes::destroy();

	return code;
}
