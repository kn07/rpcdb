#pragma once

#include <request.h>
#include <rpcdb.h>

class load_req : public create_request {
    protected:
	sensor_data *db;

    public:
	load_req();
	~load_req();

    protected:
	virtual void check() override;
	virtual request create(istringstream *stream) override;
};
