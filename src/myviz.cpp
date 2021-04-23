
#include "myviz.h"

#include <QToolButton>
#include <QHBoxLayout>

#include "rclcpp/clock.hpp"
#include "rviz_common/render_panel.hpp"
#include "rviz_common/ros_integration/ros_node_abstraction_iface.hpp"
#include "rviz_common/ros_integration/ros_node_abstraction.hpp"
#include "rviz_common/visualization_manager.hpp"
#include "rviz_rendering/render_window.hpp"

MyViz::MyViz(rviz_common::ros_integration::RosNodeAbstractionIface::WeakPtr rviz_ros_node, QWidget * parent)
: QMainWindow(parent), parent_(parent)
{
  QWidget * central_widget = new QWidget(this);
  QHBoxLayout * central_layout = new QHBoxLayout;
  central_layout->setSpacing(0);
  central_layout->setMargin(0);

  render_panel_ = new rviz_common::RenderPanel(central_widget);

  auto hide_left_dock_button_ = new QToolButton();
  hide_left_dock_button_->setContentsMargins(0, 0, 0, 0);
  hide_left_dock_button_->setArrowType(Qt::LeftArrow);
  hide_left_dock_button_->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
  hide_left_dock_button_->setFixedWidth(16);
  hide_left_dock_button_->setAutoRaise(true);
  hide_left_dock_button_->setCheckable(true);

  central_layout->addWidget(hide_left_dock_button_, 0);
  central_layout->addWidget(render_panel_, 1);

  central_widget->setLayout(central_layout);

  setCentralWidget(central_widget);

  render_panel_->getRenderWindow()->initialize();

  auto clock = rviz_ros_node.lock()->get_raw_node()->get_clock();
  manager_ = new rviz_common::VisualizationManager(render_panel_ , rviz_ros_node, this,  clock);

  render_panel_->initialize(manager_);

  manager_->initialize();
  manager_->startUpdate();
}
