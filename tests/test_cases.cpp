#include <cstdint>
#include <memory>
#include <thread>

#include "gtest/gtest.h"
#include "my_package/publisher.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"

using namespace std::chrono_literals;

class TestClass : public ::testing::Test {
 public:
  TestClass() {}
  void SetUp() override { rclcpp::init(0, nullptr); }
};

TEST_F(TestClass, testingTF) {
  auto publisher_ = std::make_shared<MinimalPublisher>();
  std::shared_ptr<rclcpp::Clock> clock_ =
      std::make_unique<rclcpp::Clock>(RCL_ROS_TIME);

  auto buffer_ = std::make_unique<tf2_ros::Buffer>(clock_);
  auto listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_);
  double time = 0;
  geometry_msgs::msg::TransformStamped transformStamped;

  auto init = clock_->now();

  while (time < 3) {
    time = (clock_->now() - init).seconds();
    rclcpp::spin_some(publisher_);
  }

  transformStamped =
      buffer_->lookupTransform("world", "talk", tf2::TimePointZero);

  EXPECT_FLOAT_EQ(publisher_->tf_talker.translation.x,
                  transformStamped.transform.translation.x);
  EXPECT_FLOAT_EQ(publisher_->tf_talker.translation.y,
                  transformStamped.transform.translation.y);
  EXPECT_FLOAT_EQ(publisher_->tf_talker.translation.z,
                  transformStamped.transform.translation.z);
}
