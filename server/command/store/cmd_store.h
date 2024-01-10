#pragma once

#include <command.h>

class cmd_store : public command {
    protected:
	sensor_data *sensors;

    public:
	cmd_store();
	~cmd_store();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
