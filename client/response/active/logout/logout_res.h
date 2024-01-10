#pragma once

#include <active/active_res.h>

class logout_res : public active_res {
    public:
	logout_res();
	~logout_res();

    protected:
	virtual command_type get_command() override;
	virtual void action() override;
};
