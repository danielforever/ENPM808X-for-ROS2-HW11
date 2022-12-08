# ENPM808X Assignment for ROS2 HW11
## This repository is for the ENPM808X Advanced Topics in Engineering; Software Development for Robotics Assignment

# Build

```
cd {ros2_ws}

rosdep install -i --from-path src --rosdistro humble –y 

colcon build --packages-select cpp_srvcli  

. install/setup.bash 
```

# Publisher and Subscriber

# Run the yaml file
```
os2 launch src/cpp_srvcli/launch/my_package_launch.yaml 
```
# Dependencies
###### ROS2
# Environment
###### Ubuntu 20.04
###### ROS2 Humble
