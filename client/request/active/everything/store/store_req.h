#pragma once

#include <active/everything/everything_req.h>

class store_req : public everything_req {
    public:
	store_req();
	~store_req();

    protected:
	virtual command_type get_command() override;
};
