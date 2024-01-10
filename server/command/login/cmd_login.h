#pragma once

#include <command.h>
#include <random_gen/random_gen.h>

class cmd_login : public command {
    private:
	random_gen rand;

    public:
	cmd_login();
	~cmd_login();

    protected:
	virtual command_type get_command() override;
	virtual response perform(request *req) override;
};
