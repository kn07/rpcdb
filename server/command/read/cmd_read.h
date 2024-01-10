#pragma once

#include <command.h>

class cmd_read : public command {
    public:
	cmd_read();
	~cmd_read();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
