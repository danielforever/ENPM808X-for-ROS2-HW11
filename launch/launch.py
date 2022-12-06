import sys

from launch.actions import ExecuteProcess
from launch.conditions import IfCondition, UnlessCondition
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    count_arg = LaunchConfiguration('count', default='50')
    bag_record = LaunchConfiguration('record', default='false')

    return LaunchDescription([
        ExecuteProcess(
            cmd=['ros2', 'bag', 'record', '-a'],
            output='screen',
            condition=IfCondition(bag_record)
        ),
        Node(
            package="my_package",
            executable="talker",
            name="publisher",
            output="screen",
            emulate_tty=True,
            parameters=[{'count': count_arg}]
        ),
        Node(
            package="my_package",
            executable="listener",
            name="subscriber",
            output="screen",
            emulate_tty=True,
            condition=UnlessCondition(bag_record)
        )
    ])
