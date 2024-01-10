#include "cmd_get_stat_all.h"

#include <algorithm>
#include <exception>
#include <numeric>

#ifdef DEBUG
#include <iostream>

using std::cout;
using std::endl;
#endif

using std::accumulate;
using std::exception;
using std::sort;

cmd_get_stat_all::cmd_get_stat_all()
{
    stats = nullptr;
}

cmd_get_stat_all::~cmd_get_stat_all()
{
    if (stats != nullptr)
        delete[] stats;
}

command_type cmd_get_stat_all::get_command()
{
    return command_type::GET_STAT_ALL_CMD;
}

response cmd_get_stat_all::perform(request* req)
{
    memset(&res, 0, sizeof res);
    res.type = get_command();

    vector<sensor_data>* data;

    try {
        data = get_user_db(req->request_u.everything.session_key);
    } catch (exception& e) {
        res.response_u.get_stat_all.response = status::INVALID_SESSION_KEY;

        return res;
    }

    if (stats != nullptr)
        delete[] stats;

    stats = new sensor_stat[data->size()];

    for (int i = 0; i < data->size(); i++) {
        sensor_data sensor = data->at(i);
        sensor_stat* stat = &stats[i];

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
    }

    res.response_u.get_stat_all.stats.stats_val = stats;
    res.response_u.get_stat_all.stats.stats_len = data->size();
    res.response_u.get_stat_all.response = status::VALID;

    return res;
}
