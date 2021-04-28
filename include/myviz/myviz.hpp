#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QToolButton>
#include <QWidget>
#include <QVBoxLayout>

#include "rclcpp/rclcpp.hpp"
#include "rviz_common/display.hpp"
#include <rviz_common/display_context.hpp>
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
  MyViz(QApplication *app, rviz_common::ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node, QWidget * parent = 0);

  QWidget * getParentWindow() override;
  rviz_common::PanelDockWidget * addPane(const QString & name, QWidget * pane, Qt::DockWidgetArea area, bool floating) override;
  void setStatus(const QString & message) override;

  void DisplayGrid();

private slots:
  void setThickness( int thickness_percent );
  void setCellSize( int cell_size_percent );
  void closeEvent(QCloseEvent *event);

private:
  void initializeRViz();

  QApplication * app_;
  QWidget * central_widget;
  QVBoxLayout * main_layout;

  rviz_common::RenderPanel * render_panel_;
  rviz_common::Display * grid_;
  rviz_common::VisualizationManager * manager_;

  rviz_common::ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node_;
};
