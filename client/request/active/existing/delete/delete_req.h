#pragma once

#include <active/existing/existing_req.h>

class delete_req : public existing_req {
    public:
	delete_req();
	~delete_req();

    protected:
	virtual command_type get_command() override;
};
