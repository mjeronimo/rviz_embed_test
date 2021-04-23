cmake_minimum_required(VERSION 3.5)
project(rviz_embed_test)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(rviz_rendering REQUIRED)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)
#find_package(Qt5Core REQUIRED)
#find_package(Qt5Quick REQUIRED)
#find_package(Qt5Widgets REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp
  rclcpp_components
  rviz_common
  rviz_default_plugins
  rviz_ogre_vendor
  rviz_rendering
)

include_directories(
  ${rclcpp_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
  #${Qt5Quick_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(headers_to_moc
  src/myviz.h
)

foreach(header "${headers_to_moc}")
  qt5_wrap_cpp(moc_files "${header}")
endforeach()

set(SRC_FILES
  src/myviz.cpp
  src/main.cpp
  ${moc_files}
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
ament_target_dependencies(${PROJECT_NAME} ${THIS_PACKAGE_INCLUDE_DEPENDS})

target_link_libraries(${PROJECT_NAME}
  Qt5::Core
  #Qt5::Quick
  Qt5::Widgets
  #rviz_common::rviz_common
  #-L/home/michael/src/ros2/install/rviz_common/lib
  rviz_common::rviz_common
  rviz_rendering::rviz_rendering
  rviz_ogre_vendor::OgreMain
  rviz_ogre_vendor::OgreOverlay
)

## Install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION lib/${PROJECT_NAME})

ament_package()
