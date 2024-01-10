#pragma once

#include <response.h>

class read_all_res : public interpret_response {
    public:
	read_all_res();
	~read_all_res();

    protected:
	virtual command_type get_command() override;
	virtual int perform(response *res) override;
};
