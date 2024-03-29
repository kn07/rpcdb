/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPCDB_H_RPCGEN
#define _RPCDB_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define RESPONSE_SIZE 50
#define USERNAME_SIZE 15

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
	NO_DB_FOUND = 9,
};
typedef enum status status;

struct sensor_data {
	int sensor_id;
	struct {
		u_int values_len;
		float *values_val;
	} values;
};
typedef struct sensor_data sensor_data;

struct sensor_stat {
	int sensor_id;
	float min;
	float max;
	float avg;
	float med;
};
typedef struct sensor_stat sensor_stat;

enum command_type {
	LOGIN_CMD = 0,
	LOGOUT_CMD = 1,
	LOAD_CMD = 2,
	STORE_CMD = 3,
	ADD_CMD = 4,
	DELETE_CMD = 5,
	UPDATE_CMD = 6,
	READ_CMD = 7,
	READ_ALL_CMD = 8,
	GET_STAT_CMD = 9,
	GET_STAT_ALL_CMD = 10,
	BAD_CMD = 11,
};
typedef enum command_type command_type;

struct login_response {
	status response;
	u_quad_t session_key;
};
typedef struct login_response login_response;

struct basic_response {
	status response;
};
typedef struct basic_response basic_response;

struct sensor_response {
	status response;
	struct {
		u_int values_len;
		float *values_val;
	} values;
};
typedef struct sensor_response sensor_response;

struct sensors_response {
	status response;
	struct {
		u_int data_len;
		sensor_data *data_val;
	} data;
};
typedef struct sensors_response sensors_response;

struct stat_response {
	status response;
	sensor_stat stat;
};
typedef struct stat_response stat_response;

struct stats_response {
	status response;
	struct {
		u_int stats_len;
		sensor_stat *stats_val;
	} stats;
};
typedef struct stats_response stats_response;

struct bad_response {
	status response;
};
typedef struct bad_response bad_response;

struct login_request {
	char *username;
};
typedef struct login_request login_request;

struct logout_request {
	u_quad_t session_key;
	char *username;
};
typedef struct logout_request logout_request;

struct basic_request {
	u_quad_t session_key;
};
typedef struct basic_request basic_request;

struct add_update_request {
	u_quad_t session_key;
	sensor_data data;
};
typedef struct add_update_request add_update_request;

struct sensor_request {
	u_quad_t session_key;
	int sensor_id;
};
typedef struct sensor_request sensor_request;

struct sensors_request {
	u_quad_t session_key;
	struct {
		u_int sensors_len;
		sensor_data *sensors_val;
	} sensors;
};
typedef struct sensors_request sensors_request;

struct request {
	command_type type;
	union {
		login_request login;
		logout_request logout;
		sensors_request load;
		add_update_request empty;
		sensor_request existing;
		basic_request everything;
	} request_u;
};
typedef struct request request;

struct response {
	command_type type;
	union {
		login_response login;
		basic_response active;
		stat_response get_stat;
		stats_response get_stat_all;
		sensor_response read;
		sensors_response read_all;
		bad_response bad;
	} response_u;
};
typedef struct response response;

#define RPC_PROG 1
#define RPC_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define rpc_call 1
extern  response * rpc_call_1(request *, CLIENT *);
extern  response * rpc_call_1_svc(request *, struct svc_req *);
extern int rpc_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rpc_call 1
extern  response * rpc_call_1();
extern  response * rpc_call_1_svc();
extern int rpc_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_status (XDR *, status*);
extern  bool_t xdr_sensor_data (XDR *, sensor_data*);
extern  bool_t xdr_sensor_stat (XDR *, sensor_stat*);
extern  bool_t xdr_command_type (XDR *, command_type*);
extern  bool_t xdr_login_response (XDR *, login_response*);
extern  bool_t xdr_basic_response (XDR *, basic_response*);
extern  bool_t xdr_sensor_response (XDR *, sensor_response*);
extern  bool_t xdr_sensors_response (XDR *, sensors_response*);
extern  bool_t xdr_stat_response (XDR *, stat_response*);
extern  bool_t xdr_stats_response (XDR *, stats_response*);
extern  bool_t xdr_bad_response (XDR *, bad_response*);
extern  bool_t xdr_login_request (XDR *, login_request*);
extern  bool_t xdr_logout_request (XDR *, logout_request*);
extern  bool_t xdr_basic_request (XDR *, basic_request*);
extern  bool_t xdr_add_update_request (XDR *, add_update_request*);
extern  bool_t xdr_sensor_request (XDR *, sensor_request*);
extern  bool_t xdr_sensors_request (XDR *, sensors_request*);
extern  bool_t xdr_request (XDR *, request*);
extern  bool_t xdr_response (XDR *, response*);

#else /* K&R C */
extern bool_t xdr_status ();
extern bool_t xdr_sensor_data ();
extern bool_t xdr_sensor_stat ();
extern bool_t xdr_command_type ();
extern bool_t xdr_login_response ();
extern bool_t xdr_basic_response ();
extern bool_t xdr_sensor_response ();
extern bool_t xdr_sensors_response ();
extern bool_t xdr_stat_response ();
extern bool_t xdr_stats_response ();
extern bool_t xdr_bad_response ();
extern bool_t xdr_login_request ();
extern bool_t xdr_logout_request ();
extern bool_t xdr_basic_request ();
extern bool_t xdr_add_update_request ();
extern bool_t xdr_sensor_request ();
extern bool_t xdr_sensors_request ();
extern bool_t xdr_request ();
extern bool_t xdr_response ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPCDB_H_RPCGEN */
