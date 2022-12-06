// Copyright 2022 Po-Yu Huang
#include "my_package/subscriber.hpp"

MinimalSubscriber::MinimalSubscriber()
: Node("minimal_subscriber")
{

  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
}

void MinimalSubscriber::topic_callback(const std_msgs::msg::String& msg) const {
    int num_recieved = stoi(msg.data)%5;
    if(num_recieved == 1) {
      RCLCPP_DEBUG_STREAM(rclcpp::get_logger("rclcpp"),
        "This is the DEBUG STREAM NUMBER: "<< msg.data);
    } else if(num_recieved == 2) {
      RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
        "This is the INFO STREAM NUMBER: "<< msg.data);
    } else if(num_recieved == 3) {
      RCLCPP_WARN_STREAM(rclcpp::get_logger("rclcpp"),
        "This is the WARN STREAM NUMBER: "<< msg.data);      
    } else if(num_recieved == 4) {
      RCLCPP_ERROR_STREAM(rclcpp::get_logger("rclcpp"),
        "This is the ERROR STREAM NUMBER: "<< msg.data);     
    } else {
      RCLCPP_FATAL_STREAM(rclcpp::get_logger("rclcpp"),
        "This is the FATAL STREAM NUMBER: "<< msg.data);      
    }
  }
