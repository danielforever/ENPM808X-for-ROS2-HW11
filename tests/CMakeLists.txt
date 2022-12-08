set(TESTCASES
    main.cpp
    test_cases.cpp
)

ament_add_gtest(${PROJECT_NAME}_test ${TESTCASES})
ament_target_dependencies(
    ${PROJECT_NAME}_test
    geometry_msgs
    tf2
    tf2_ros
    tf2_geometry_msgs
  )
target_link_libraries(${PROJECT_NAME}_test pub_lib)

  install(
    TARGETS ${PROJECT_NAME}_test
    DESTINATION ../lib/${PROJECT_NAME}
  )

