#pragma once

#include <active/everything/everything_req.h>

class read_all_req : public everything_req {
    public:
	read_all_req();
	~read_all_req();

    protected:
	virtual command_type get_command() override;
};
