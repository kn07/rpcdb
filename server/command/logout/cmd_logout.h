#pragma once

#include <command.h>

class cmd_logout : public command {
    public:
	cmd_logout();
	~cmd_logout();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
