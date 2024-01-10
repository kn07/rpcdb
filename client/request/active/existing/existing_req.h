#pragma once

#include <active/active_req.h>

class existing_req : public active_req {
    protected:
	existing_req();
	~existing_req();

	virtual void parse_input(istringstream *stream, int *sensor_id);
	virtual request create(istringstream *stream) override final;
};
