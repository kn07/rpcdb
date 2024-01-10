#pragma once

#include <command.h>

class cmd_get_stat : public command {
    public:
	cmd_get_stat();
	~cmd_get_stat();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
