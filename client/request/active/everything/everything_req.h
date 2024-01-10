#pragma once

#include <active/active_req.h>

class everything_req : public active_req {
    protected:
	everything_req();
	~everything_req();

	virtual request create(istringstream *stream) override final;
};
