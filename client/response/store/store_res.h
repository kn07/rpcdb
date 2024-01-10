#pragma once

#include <response.h>

class store_res : public interpret_response {
    public:
	store_res();
	~store_res();

    protected:
	virtual command_type get_command() override;
	virtual int perform(response *res) override;
};
