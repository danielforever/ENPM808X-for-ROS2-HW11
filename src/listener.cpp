// Copyright 2022 Po-Yu Huang
#include "my_package/subscriber.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  RCLCPP_INFO_STREAM(
      rclcpp::get_logger("rclcpp"),
      "\nFive color: \n   1. Yellow  2. Green  3. Blue  4. Orange  5. Red \n");
  rclcpp::spin(std::make_shared<MinimalSubscriber>());

  rclcpp::shutdown();
  return 0;
}
