#pragma once

#include <nodelet/nodelet.h>
#include <ros/ros.h>

namespace six_point_two_eight {
  class MakeWorldModels : public nodelet::Nodelet {
  public:
    void onInit() {
      ROS_INFO_STREAM("Hello, world!");
    }
  };
}
