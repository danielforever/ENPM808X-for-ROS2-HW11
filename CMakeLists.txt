cmake_minimum_required(VERSION 3.8)
project(my_package)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/CountNumber.srv"  
)

ament_export_dependencies(rosidl_default_runtime)

include_directories(
    include
)

add_library(pub_lib src/publisher_member_function.cpp)

ament_target_dependencies(
    pub_lib
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    rosbag2_cpp
    tf2_geometry_msgs
)

rosidl_get_typesupport_target(cpp_typesupport_target 
    ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(pub_lib
  "${cpp_typesupport_target}"
)

add_executable(talker src/talker.cpp)

target_link_libraries(talker
  pub_lib
)



add_library(sub_lib 
  src/subscriber_member_function.cpp
)

ament_target_dependencies(sub_lib rclcpp std_msgs)



add_executable(listener src/listener.cpp)



target_link_libraries(listener
  sub_lib
)


install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})
  

install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME})
  
install(
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION include
)

install(
  DIRECTORY result/rosbag
  DESTINATION share/${PROJECT_NAME}
)

# Install shared library
install(
  TARGETS pub_lib
  EXPORT pub_lib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  TARGETS sub_lib
  EXPORT sub_lib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the ffvollowing line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
  find_package(ament_cmake_gtest REQUIRED)
  add_subdirectory(tests)

  
endif()

ament_package()
