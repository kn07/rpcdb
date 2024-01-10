#pragma once

#include <command.h>

class cmd_load : public command {
    public:
	cmd_load();
	~cmd_load();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
