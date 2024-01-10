#pragma once

#include <command.h>

class cmd_update : public command {
    public:
	cmd_update();
	~cmd_update();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
