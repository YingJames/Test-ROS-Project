#include "ros/ros.h"
#include "std_msgs/String.h"
#include "fibonacci_pkg/calc_fib.h"

bool calc_fib_sequence(fibonacci_pkg::calc_fib::Request &request,
    fibonacci_pkg::calc_fib::Response &response) {

    ROS_INFO("Received an input: %d", request.iterations);
    for (int32_t i = 0; i < request.iterations; i++) {
        if (i == 0) {
            response.fib_sequence.push_back(0);
        } else if (i == 1) {
            response.fib_sequence.push_back(1);
        } else {
            int first_num = response.fib_sequence[i-1];
            int second_num = response.fib_sequence[i-2];
            response.fib_sequence.push_back(first_num + second_num);
        }
    }

    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "calc_fib_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("calc_fib", calc_fib_sequence);

    ROS_INFO("Requesting integer length for fibonacci sequence");
    ros::spin();
    return 0;
}