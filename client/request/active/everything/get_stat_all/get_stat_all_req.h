#pragma once

#include <active/everything/everything_req.h>

class get_stat_all_req : public everything_req {
    public:
	get_stat_all_req();
	~get_stat_all_req();

    protected:
	virtual command_type get_command() override;
};
