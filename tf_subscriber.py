import rclpy
from rclpy.node import Node
from tf2_msgs.msg import TFMessage

class TFSubscriber(Node):

    def __init__(self):
        super().__init__('tf_subscriber')
        self.subscription = self.create_subscription(
            TFMessage,
            '/tf',
            self.tf_callback,
            10)

    def tf_callback(self, msg):
        for transform in msg.transforms:
            self.get_logger().info(
                f"Received TF transform: frame_id={transform.header.frame_id}, child_frame_id={transform.child_frame_id}, "
                f"translation=({transform.transform.translation.x}, {transform.transform.translation.y}, {transform.transform.translation.z}), "
                f"rotation=({transform.transform.rotation.x}, {transform.transform.rotation.y}, {transform.transform.rotation.z}, {transform.transform.rotation.w})"
            )

def main(args=None):
    rclpy.init(args=args)
    tf_subscriber = TFSubscriber()
    rclpy.spin(tf_subscriber)
    rclpy.shutdown()

if __name__ == '__main__':
    main()