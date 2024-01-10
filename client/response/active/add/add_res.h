#pragma once

#include <active/active_res.h>

class add_res : public active_res {
    public:
	add_res();
	~add_res();

    protected:
	virtual command_type get_command() override;
};
