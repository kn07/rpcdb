#include "client.h"

bool client_::logged_in = false;
bool client_::cmd_issued = false;
string *client_::username = new string();
unsigned long client_::session_key = 0;
