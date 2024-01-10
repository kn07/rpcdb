#pragma once

#include <active/existing/existing_req.h>

class read_req : public existing_req {
    public:
	read_req();
	~read_req();

    protected:
	virtual command_type get_command() override;
};
