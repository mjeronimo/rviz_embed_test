
#pragma once

#include <QWidget>
#include <QMainWindow>
#include <rclcpp/rclcpp.hpp>

#include "rviz_common/window_manager_interface.hpp"
#include "rviz_common/ros_integration/ros_node_abstraction.hpp"


namespace rviz_common
{

class Display;
class RenderPanel;
class VisualizationManager;

}

class MyViz: public QMainWindow, public rviz_common::WindowManagerInterface
{
Q_OBJECT
public:
  MyViz(rviz_common::ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node, QWidget * parent = 0);

  QWidget * getParentWindow() override {
    return this;
  }    

  rviz_common::PanelDockWidget * addPane(const QString & name, QWidget * pane, Qt::DockWidgetArea area, bool floating)  override {
    return nullptr; 
  }

  void setStatus(const QString & message) override {}

private:
  rviz_common::VisualizationManager* manager_;
  rviz_common::RenderPanel* render_panel_;
  rviz_common::Display* grid_;

  QWidget * parent_;
};
