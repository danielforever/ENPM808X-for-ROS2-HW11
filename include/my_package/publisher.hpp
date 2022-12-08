// Copyright 2022 Po-Yu Huang
// Copyright 2021 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <rosbag2_storage/serialized_bag_message.hpp>
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"

#include "my_package/srv/count_number.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;


class MinimalPublisher : public rclcpp::Node {
 public:
  MinimalPublisher();
  
  geometry_msgs::msg::TransformStamped t;
  
 private:
  void get_num_callback();
  void timer_callback();
  void topic_callback(  const std::shared_ptr<my_package::srv::CountNumber::Request> request,
  std::shared_ptr<my_package::srv::CountNumber::Response> response);
  void broadcast_tf_callback();
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr timer_for_tf_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::Service<my_package::srv::CountNumber>::SharedPtr num_service_;
  size_t count_;
 };
  
