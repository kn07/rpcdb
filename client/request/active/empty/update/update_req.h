#pragma once

#include <active/empty/empty_req.h>

class update_req : public empty_req {
    public:
	update_req();
	~update_req();

    protected:
	virtual command_type get_command() override;
};
