#pragma once

#include <active/active_res.h>

class delete_res : public active_res {
    public:
	delete_res();
	~delete_res();

    protected:
	virtual command_type get_command() override;
};
