#include <QApplication>

#include <memory>

#include "myviz/myviz.hpp"
#include "rviz_common/ros_integration/ros_node_abstraction.hpp"

int main(int argc, char ** argv)
{
  QApplication app(argc, argv);
  rclcpp::init(argc, argv);

  auto ros_node_abs =
    std::make_shared<rviz_common::ros_integration::RosNodeAbstraction>("rviz_render_node");

  auto myviz = std::make_shared<MyViz>(&app, ros_node_abs);
  myviz->show();

  while (rclcpp::ok()) {
    app.processEvents();
  }

  return 0;
}
