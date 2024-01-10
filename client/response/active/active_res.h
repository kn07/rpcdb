#pragma once

#include <response.h>

class active_res : public interpret_response {
protected:
    active_res();
    virtual ~active_res();

    virtual void action();
    int perform(response* res);
};
