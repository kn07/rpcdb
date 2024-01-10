#pragma once

#include <response.h>

class get_stat_res : public interpret_response {
    public:
	get_stat_res();
	~get_stat_res();

    protected:
	virtual command_type get_command() override;
	virtual int perform(response *res) override;
};
