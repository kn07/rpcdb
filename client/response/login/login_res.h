#pragma once

#include <response.h>

class login_res : public interpret_response {
    public:
	login_res();
	~login_res();

	virtual command_type get_command() override;
	virtual int perform(response *res) override;
};
