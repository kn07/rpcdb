#include "status_codes.h"

#include <stdexcept>

#define SERVER_PREFIX "[SERVER] "

#define MESSAGE_NOT_FOUND "Unknown response code."
#define STATUS_CODE_NOT_INIT_ERROR                                             \
	"Please call init method before use status_code object."

#define INVALID_USER_ERROR "User not found."
#define EXISTING_USER_ERROR "User already logged in."
#define INVALID_SESSION_KEY_ERROR "Username and session key does not match."
#define SESSION_KEY_NOT_FOUND_ERROR "Session key not found."
#define INVALID_REQUEST_ERROR "Recived invalid request."
#define INVALID_DATA_ERROR "Recived invalid data."
#define EXISTING_RECORD_ERROR "Sensor already exists."
#define NO_DATA_FOUND_ERROR "Sensor not found."
#define NO_DB_FOUND_ERROR "Database not found."

unordered_map<status, string> *status_codes::messages = nullptr;

using std::bad_alloc;
using std::logic_error;
using std::runtime_error;

void status_codes::init()
{
	status_codes::messages = new unordered_map<status, string>;

	if (status_codes::messages == nullptr)
		throw bad_alloc();

	status_codes::messages->insert(
		{ status::INVALID_USER, INVALID_USER_ERROR });
	status_codes::messages->insert(
		{ status::EXISTING_USER, EXISTING_USER_ERROR });
	status_codes::messages->insert(
		{ status::INVALID_SESSION_KEY, INVALID_SESSION_KEY_ERROR });
	status_codes::messages->insert(
		{ status::SESSION_KEY_NOT_FOUND, SESSION_KEY_NOT_FOUND_ERROR });
	status_codes::messages->insert(
		{ status::INVALID_REQUEST, INVALID_REQUEST_ERROR });
	status_codes::messages->insert(
		{ status::INVALID_DATA, INVALID_DATA_ERROR });
	status_codes::messages->insert(
		{ status::EXISTING_RECORD, EXISTING_RECORD_ERROR });
	status_codes::messages->insert(
		{ status::NO_DATA_FOUND, NO_DATA_FOUND_ERROR });
	status_codes::messages->insert(
		{ status::NO_DB_FOUND, NO_DB_FOUND_ERROR });
}

void status_codes::destroy()
{
	if (status_codes::messages == nullptr)
		throw logic_error(STATUS_CODE_NOT_INIT_ERROR);

	delete messages;
}

string status_codes::get(status r)
{
	if (status_codes::messages == nullptr)
		throw logic_error(STATUS_CODE_NOT_INIT_ERROR);

	if (messages->find(r) == messages->end())
		throw runtime_error(MESSAGE_NOT_FOUND);

	return SERVER_PREFIX + messages->at(r);
}
