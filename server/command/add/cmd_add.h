#pragma once

#include <command.h>

class cmd_add : public command {
    public:
	cmd_add();
	~cmd_add();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
