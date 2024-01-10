#pragma once

#include <active/active_res.h>

class update_res : public active_res {
    public:
	update_res();
	~update_res();

    protected:
	virtual command_type get_command() override;
};
