// Copyright 2022 Po-Yu Huang
#include <memory>

#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

/// @brief print 5 logging level stream
/// @param request
/// @param response
void add(
    const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
    std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response) {
  int result = (request->a) % 5;
  response->sum = result;
  if (result == 1) {
    RCLCPP_DEBUG_STREAM(rclcpp::get_logger("rclcpp"),
                        "This is the DEBUG STREAM NUMBER: " << result);
  } else if (result == 2) {
    RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
                       "This is the INFO STREAM NUMBER: " << result);
  } else if (result == 3) {
    RCLCPP_WARN_STREAM(rclcpp::get_logger("rclcpp"),
                       "This is the WARN STREAM NUMBER: " << result);
  } else if (result == 4) {
    RCLCPP_ERROR_STREAM(rclcpp::get_logger("rclcpp"),
                        "This is the ERROR STREAM NUMBER: " << result);
  } else {
    RCLCPP_FATAL_STREAM(rclcpp::get_logger("rclcpp"),
                        "This is the FATAL STREAM NUMBER: " << result);
  }
}
/// @brief main function
/// @param argc
/// @param argv
/// @return
int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node =
      rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
      node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints",
                                                                &add);
  RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"),
                     "\nShpw five different logger in the terminal: \n 1. "
                     "Debug 2. INFO 3. WARN 4. ERROR 5. FATAL \n");
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
