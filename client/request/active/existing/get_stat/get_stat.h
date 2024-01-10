#pragma once

#include <active/existing/existing_req.h>

class get_stat_req : public existing_req {
    public:
	get_stat_req();
	~get_stat_req();

    protected:
	virtual command_type get_command() override;
};
