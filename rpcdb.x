const RESPONSE_SIZE = 50;
const USERNAME_SIZE = 15;

enum status {
	VALID = 0,
	INVALID_USER = 1,
	EXISTING_USER = 2,
	INVALID_SESSION_KEY = 3,
	SESSION_KEY_NOT_FOUND = 4,
	INVALID_REQUEST = 5,
	INVALID_DATA = 6,
	EXISTING_RECORD = 7,
	NO_DATA_FOUND = 8,
	NO_DB_FOUND = 9
};

/*-----------------data structs begin-----------------*/
struct sensor_data {
    int sensor_id;
    float values<>;
};

struct sensor_stat {
    int sensor_id;
    float min;
    float max;
    float avg;
    float med;
};

enum command_type {
    LOGIN_CMD,
    LOGOUT_CMD,
    LOAD_CMD,
    STORE_CMD,
    ADD_CMD,
    DELETE_CMD,
    UPDATE_CMD,
    READ_CMD,
    READ_ALL_CMD,
    GET_STAT_CMD,
    GET_STAT_ALL_CMD,
    BAD_CMD
};
/*------------------data structs end------------------*/


/*---------------response structs begin---------------*/
struct login_response {
    status response;
    unsigned hyper session_key;
};

struct basic_response {
    status response;
};

struct sensor_response {
    status response;
    float values<>;
};

struct sensors_response {
    status response;
    sensor_data data<>;
};

struct stat_response {
    status response;
    sensor_stat stat;
};

struct stats_response {
    status response;
    sensor_stat stats<>;
};

struct bad_response {
    status response;
};
/*----------------response structs end----------------*/

/*----------------request structs begin---------------*/
struct login_request {
    string username<USERNAME_SIZE>;
};

struct logout_request {
    unsigned hyper session_key;
    string username<>;
};

struct basic_request {
    unsigned hyper session_key;
};

struct add_update_request {
    unsigned hyper session_key;
    sensor_data data;
};

struct sensor_request {
    unsigned hyper session_key;
    int sensor_id;
};

struct sensors_request {
    unsigned hyper session_key;
    sensor_data sensors<>;
};
/*-----------------request structs end----------------*/

union request switch(command_type type) {
    case LOGIN_CMD:
        login_request login;

    case LOGOUT_CMD:
        logout_request logout;

    case LOAD_CMD:
        sensors_request load;

    case ADD_CMD:
    case UPDATE_CMD:
        add_update_request empty;

    case DELETE_CMD:
    case READ_CMD:
    case GET_STAT_CMD:
        sensor_request existing;

    case STORE_CMD:
    case READ_ALL_CMD:
    case GET_STAT_ALL_CMD:
        basic_request everything;
};

union response switch(command_type type) {
    case LOGIN_CMD:
        login_response login;

    case ADD_CMD:
    case UPDATE_CMD:
    case DELETE_CMD:
    case LOAD_CMD:
    case LOGOUT_CMD:
        basic_response active;

    case GET_STAT_CMD:
        stat_response get_stat;

    case GET_STAT_ALL_CMD:
        stats_response get_stat_all;

    case READ_CMD:
        sensor_response read;

    case STORE_CMD:
    case READ_ALL_CMD:
        sensors_response read_all;

    case BAD_CMD:
         bad_response bad;
};

program RPC_PROG {
        version RPC_VERS {
                response rpc_call(request) = 1;
        } = 1;
} = 1;
