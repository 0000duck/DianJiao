# Install script for directory: /home/carson/chess_ws/src/chess_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/carson/chess_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/msg" TYPE FILE FILES
    "/home/carson/chess_ws/src/chess_msgs/msg/Operation.msg"
    "/home/carson/chess_ws/src/chess_msgs/msg/Move.msg"
    "/home/carson/chess_ws/src/chess_msgs/msg/Result.msg"
    "/home/carson/chess_ws/src/chess_msgs/msg/Zpose.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/srv" TYPE FILE FILES
    "/home/carson/chess_ws/src/chess_msgs/srv/Play.srv"
    "/home/carson/chess_ws/src/chess_msgs/srv/Point.srv"
    "/home/carson/chess_ws/src/chess_msgs/srv/Mode.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/action" TYPE FILE FILES "/home/carson/chess_ws/src/chess_msgs/action/Step.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/msg" TYPE FILE FILES
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepAction.msg"
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepActionGoal.msg"
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepActionResult.msg"
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepActionFeedback.msg"
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepGoal.msg"
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepResult.msg"
    "/home/carson/chess_ws/devel/share/chess_msgs/msg/StepFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/cmake" TYPE FILE FILES "/home/carson/chess_ws/build/chess_msgs/catkin_generated/installspace/chess_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/carson/chess_ws/devel/include/chess_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/carson/chess_ws/devel/share/roseus/ros/chess_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/carson/chess_ws/devel/share/common-lisp/ros/chess_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/carson/chess_ws/devel/share/gennodejs/ros/chess_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/carson/chess_ws/devel/lib/python2.7/dist-packages/chess_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/carson/chess_ws/devel/lib/python2.7/dist-packages/chess_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/carson/chess_ws/build/chess_msgs/catkin_generated/installspace/chess_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/cmake" TYPE FILE FILES "/home/carson/chess_ws/build/chess_msgs/catkin_generated/installspace/chess_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs/cmake" TYPE FILE FILES
    "/home/carson/chess_ws/build/chess_msgs/catkin_generated/installspace/chess_msgsConfig.cmake"
    "/home/carson/chess_ws/build/chess_msgs/catkin_generated/installspace/chess_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/chess_msgs" TYPE FILE FILES "/home/carson/chess_ws/src/chess_msgs/package.xml")
endif()

