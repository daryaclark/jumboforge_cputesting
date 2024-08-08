#include "rclcpp/rclcpp.hpp"
#include "tf2_msgs/msg/tf_message.hpp"

class TFSubscriber : public rclcpp::Node
{
public:
    TFSubscriber() : Node("tf_subscriber")
    {
        subscription_ = this->create_subscription<tf2_msgs::msg::TFMessage>(
            "/tf", 10,
            std::bind(&TFSubscriber::tfCallback, this, std::placeholders::_1));
    }

private:
    void tfCallback(const tf2_msgs::msg::TFMessage::SharedPtr msg)
    {
        // Iterate through each transform in the TFMessage
        for (const auto& transform : msg->transforms) {
            RCLCPP_INFO(this->get_logger(), "Received TF transform: frame_id=%s, child_frame_id=%s, translation=(%f, %f, %f), rotation=(%f, %f, %f, %f)",
                        transform.header.frame_id.c_str(), transform.child_frame_id.c_str(),
                        transform.transform.translation.x, transform.transform.translation.y, transform.transform.translation.z,
                        transform.transform.rotation.x, transform.transform.rotation.y, transform.transform.rotation.z, transform.transform.rotation.w);
        }
    }

    rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TFSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}