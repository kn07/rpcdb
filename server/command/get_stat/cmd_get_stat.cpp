#include "cmd_get_stat.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>

using std::accumulate;
using std::exception;
using std::sort;

cmd_get_stat::cmd_get_stat()
{
}

cmd_get_stat::~cmd_get_stat()
{
}

command_type cmd_get_stat::get_command()
{
    return command_type::GET_STAT_CMD;
}

response cmd_get_stat::perform(request* req)
{
    memset(&res, 0, sizeof res);
    res.type = get_command();

    vector<sensor_data>* data;

    try {
        data = get_user_db(req->request_u.existing.session_key);
    } catch (exception& e) {
        res.response_u.read.response = status::INVALID_SESSION_KEY;

        return res;
    }

    for (sensor_data sensor : *data) {
        if (sensor.sensor_id == req->request_u.existing.sensor_id) {
            sensor_stat* stat = &res.response_u.get_stat.stat;
            int n = sensor.values.values_len;
            vector<float> values(sensor.values.values_val,
                                 sensor.values.values_val + sensor.values.values_len);
            float sum = accumulate(values.begin(), values.end(), 0.0f);

            sort(values.begin(), values.end());

            stat->sensor_id = sensor.sensor_id;
            stat->min = values[0];
            stat->max = values.back();
            stat->avg = sum / static_cast<float>(values.size());

            if (n <= 0)
                stat->med = 0;
            else if (n == 1)
                stat->med = values[0];
            else if (n % 2 == 0)
                stat->med = values[(n + 1) / 2];
            else
                stat->med = (values[n / 2] + values[(n / 2) + 1]) / 2.0f;

            res.response_u.get_stat.response = status::VALID;

            return res;
        }
    }

    res.response_u.get_stat.response = status::NO_DATA_FOUND;

    return res;
}
