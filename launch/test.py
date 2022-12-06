from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([
        Node(
            package='my_package',
            executable='my_package_test',
            name='my_package_test_node',
            output='screen',
            emulate_tty=True,
        ),
    ])
