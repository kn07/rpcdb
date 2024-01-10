#pragma once

#include <request.h>

class login_req : public create_request {
    private:
	char *user;

    public:
	login_req();
	~login_req();

    protected:
	void check() override;
	request create(istringstream *stream) override;
};
