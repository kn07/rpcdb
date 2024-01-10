#pragma once

#include <command.h>

class cmd_delete : public command {
    public:
	cmd_delete();
	~cmd_delete();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
