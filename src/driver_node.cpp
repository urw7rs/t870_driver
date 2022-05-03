#include <ros/ros.h>

#include <geometry_msgs/Twist.h>

extern "C"
{
#include "motor.h"
}

class Motor
{
  private:
    int file;
    ros::Subscriber sub;

  public:
    Motor(ros::NodeHandle *nh)
    {
      file = init();
      if (file == -1)
        ROS_ERROR("cannot open i2c device");

      sub = nh->subscribe("/cmd_vel", 10, &Motor::twistCallback, this);
    }

    void twistCallback(const geometry_msgs::Twist& msg)
    {
      float w = msg.angular.z;
      float v_y = msg.linear.y;

      int res = set_twist(file, w, v_x, v_y);
    }

    void stop()
    {
      int res = set_motor_speed(file, 0.0, 0.0);
    }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "driver");
  ros::NodeHandle nh;

  ros::AsyncSpinner spinner(4);
  spinner.start();

  Motor motor(&nh, pwm_freq);
  ROS_INFO("Motor driver connected");

  ros::waitForShutdown();
  motor.stop();
}
