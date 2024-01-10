#pragma once

#include <active/active_res.h>

class load_res : public active_res {
    public:
	load_res();
	~load_res();

    protected:
	virtual command_type get_command() override;
};
