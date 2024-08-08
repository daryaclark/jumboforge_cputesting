#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;

class CmdVelPublisher : public rclcpp::Node
{
public:
    CmdVelPublisher()
    : Node("cmd_vel_publisher")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&CmdVelPublisher::publish_cmd_vel, this));
    }

private:
    void publish_cmd_vel()
    {
        auto msg = std::make_unique<geometry_msgs::msg::Twist>();
        // Set linear and angular velocities
        msg->linear.x = 0.5;  // Example linear velocity
        msg->angular.z = 0.2; // Example angular velocity
        publisher_->publish(std::move(msg));
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CmdVelPublisher>());
    rclcpp::shutdown();
    return 0;
}