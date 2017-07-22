#ifndef kalman_class_H
#define kalman_class_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "matrix.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>


class bot_prediction
{
	ros::NodeHandle n;
	public:
		bot_prediction(float, float,float,int);
		void predict();
		void update();
		void disp();
		float** initialize(int row, int col);
		void publish_msg();
		void declare(float x_coordinate , float y_coordinate , float theta);
		void collide(bot_prediction other_bot);

		nav_msgs::Odometry msg1;
		float **F_mat, **H_mat , **P_mat , **R_mat , **Q_mat  , **X_mat , **S_mat, **Z_mat , **K_mat;
		matrix F, H, P, R, Q, X, S, Z, K;
		std::string topic;
		int bot_id;
		ros::Publisher chatter_pub ;
		float time , time1;

};

#endif