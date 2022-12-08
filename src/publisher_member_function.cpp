// Copyright 2022 Po-Yu Huang
#include "my_package/publisher.hpp"

MinimalPublisher::MinimalPublisher() : Node("minimal_publisher"), count_(0) {

  this->declare_parameter("counting", count_, rcl_interfaces::msg::ParameterDescriptor{});

  count_ = this->get_parameter("counting").get_parameter_value().get<int>();

  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
  timer_ = this->create_wall_timer(
      1s, std::bind(&MinimalPublisher::timer_callback, this));

  get_count_service_ = this->create_service<my_package::srv::CountNumber>(
      "CountNumber",
      std::bind(&MinimalPublisher::number_callback, this, _1, _2));

  tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

  tf_timer_ = this->create_wall_timer(
      300ms, std::bind(&MinimalPublisher::tf_callback, this));
}

void MinimalPublisher::timer_callback() {
  auto message = std_msgs::msg::String();

  count_ = this->get_parameter("counting").get_parameter_value().get<int>();

  message.data = std::to_string(count_++);

  publisher_->publish(message);

  this->set_parameter(rclcpp::Parameter("counting", count_));
}

void MinimalPublisher::number_callback(
    const std::shared_ptr<my_package::srv::CountNumber::Request> request,
    std::shared_ptr<my_package::srv::CountNumber::Response> response) {
  (void)request;
  response->sum = count_;
}

void MinimalPublisher::tf_callback() {
  geometry_msgs::msg::TransformStamped t;

  t.header.stamp = this->get_clock()->now();
  t.header.frame_id = "world";
  t.child_frame_id = "talk";

  tf2::Quaternion q;

  q.setRPY(0, 0, 1);

  t.transform = tf_talker;
  tf_talker.translation.x = 1.0;
  tf_talker.translation.y = 2.0;
  tf_talker.translation.z = 3.0;
  tf_talker.rotation.x = q.x();
  tf_talker.rotation.y = q.y();
  tf_talker.rotation.z = q.z();
  tf_talker.rotation.w = q.w();
  tf_broadcaster_->sendTransform(t);
}
