#include "ros/ros.h"
#include "fibonacci_pkg/calc_fib.h"
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
    if (argc != 2 || argv[1] == 0) {
        ROS_INFO("Must only have 1 arg and length > 0");
        return 1;
    }

    ros::init(argc, argv, "calc_fib_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<fibonacci_pkg::calc_fib>("calc_fib");

    fibonacci_pkg::calc_fib calc_fib_service;
    calc_fib_service.request.iterations = atoi(argv[1]);

    std::vector<int32_t> *fib_sequence = &calc_fib_service.response.fib_sequence;
    if (client.call(calc_fib_service)) {
        ROS_INFO("Successfully created length of %d", calc_fib_service.request.iterations);
        std::stringstream ss;
        for (int i = 0; i < fib_sequence->size(); ++i) {
            ss << (*fib_sequence)[i] << " ";
        }
        ROS_INFO("Sequence: %s", ss.str().c_str());
    }
    else {
        ROS_ERROR("Error");
        return 1;
    }

    return 0;
}