#pragma once

#include <command.h>

class cmd_get_stat_all : public command {
    private:
	sensor_stat *stats;

    public:
	cmd_get_stat_all();
	~cmd_get_stat_all();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
