#include "ros/ros.h"
#include "std_msgs/String.h"

extern "C" {
	int xfei_login();
	void xfei_logout();
	int xfei_talk(const char * text);
	void xfei_talker(const char * who);

	void xfei_listen_on();
	void xfei_listen_off();
	int xfei_listen_status();
	char* xfei_listen_result();
}

/* 订阅消息的回调函数 */
void messageCallback(const std_msgs::String::ConstPtr& msg) {
	const char * text = msg->data.c_str();
	if ( strstr(text, "talk ") == text ) {
		//int status = xfei_listen_status();
		//if ( status )
		//	xfei_listen_off();
		xfei_talk(text + strlen("talk "));		// 说话，注：需要关闭监听
		//if ( status )
		//	xfei_listen_on();
	} else if ( strstr(text, "talker ") == text ) {
		printf("*** 改变了说话人 ***\n");
		xfei_talker(text + strlen("talker "));	// 说话人
	} else if ( strstr(text, "listen on") == text ) {
		printf("+++ 打开语音命令识别 +++\n");
		xfei_listen_on();
	} else if ( strstr(text, "listen off") == text ) {
		printf("--- 关闭语音命令识别 ---\n");
		xfei_listen_off();
	}
}

/* 发布一条消息 */
void publishMessage(ros::Publisher pub, std_msgs::String msg, char* text) {
	msg.data = text;
	pub.publish(msg);
	printf("\n语音识别结果：\n%s\n", text);	//???
}

int main(int argc, char **argv) {
	if ( xfei_login() != 0 )
		return -1;

	ros::init(argc, argv, "speech_node");		// 节点名字

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("speech_command", 100, messageCallback);
	ros::Publisher pub = n.advertise<std_msgs::String>("speech_recognize", 1);	// 最多缓冲一条语音识别结果，保证最后一句有效
	std_msgs::String msg;	// 注：如果是频繁发送，则此变量不能复用

	printf("当前语音命令识别状态：%s\n", xfei_listen_status() ? "打开" : "关闭");
	xfei_talk("开始工作，等待命令 ...");

	ros::Rate loop_rate(10);	// 每秒10次
	while ( ros::ok() ) {
		char* text = xfei_listen_result();
		if ( text != NULL )
			publishMessage(pub, msg, text);
		ros::spinOnce();		// 执行ros调度，以便订阅的消息到来的时候，回调函数能够被调用
		loop_rate.sleep();		// 休息1/10秒
	}

	xfei_logout();
	return 0;
}

