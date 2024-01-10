#pragma once

#include <command.h>

class cmd_read_all : public command {
    private:
	sensor_data *sensors;

    public:
	cmd_read_all();
	~cmd_read_all();

	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
