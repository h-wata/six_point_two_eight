#pragma once

#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <thread>

#include <geometry_msgs/Twist.h>

namespace six_point_two_eight {
		// geometry_msgs/Twistメッセージを生成します。
		inline auto createTwistMsg(double linear_x, double angular_z) {
				geometry_msgs::Twist msg;
				msg.linear.x = linear_x;
				msg.angular.z = angular_z;

				return msg;
		}

		class MakeWorldModels : public nodelet::Nodelet {
				private:
						ros::Publisher velocity_publisher_;
						std::thread working_thread_;
				public:
						void onInit() {
								// Publisherを生成します。
								velocity_publisher_ = getNodeHandle().advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1);
								// onInitの中でループするとNodeletManagerの処理が止まってしまうので、別スレッドで実行します。
								working_thread_ = std::thread(
									[&]() {
										ros::Rate rate(10);  // 周波数は10Hz（1秒に10回ループします）。
										while (ros::ok()) {  // ROSがシャットダウンされるまで、無限ループします。
											velocity_publisher_.publish(createTwistMsg(0.1, 0.0));  // メッセージを生成して、publishします。
											rate.sleep();  // 適切な周波数になるようにスリープ。
								   		}
								   	 });
						}
		};
}
