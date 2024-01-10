#pragma once

#include <active/empty/empty_req.h>

class add_req : public empty_req {
    public:
	add_req();
	~add_req();

    protected:
	virtual command_type get_command() override;
};
