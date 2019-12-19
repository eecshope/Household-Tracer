#include "ros/ros.h"
#include "std_msgs/String.h"
#include "math.h" // 不知道ros支不支持 
 
/**
 * 这里我就用中文注释了，不美观但是不碍事
 * 架构：这是一个subscriber，依赖于三项输入，首先是是否找到人用整数（0，1）表示
 * 第二个参数应该是人的房间号，我用它来进行简单的统计建模（还没有更厉害的学习模型） 
 * 第3、4个参数应该是人的位置x、y，我不太清楚是浮点还是整形，都先按照浮点处理
 * 第5、6个参数是机器人的当前位置，x1和y1，浮点型 
 * 预计的输入是字符串形式，如："1 4 144.23 353.2 100.04 88.54" 或 "0 -1 0 0 100.04 88.54" 
 */
 
 // TODO: 1、实现运动控制move() 2、实现旋转搜索rotateSearch() 3、记录每个房间中点位置middleX()和middleY()
 // 注意：目前的rotate和move是原子的，判断rotate是否完成的地方需要改进 

/**
 * 你可能注意到下面对行为模式的判断是非常简单的统计形式的，这一部分可以修改 
 */
long long modelCnt[6] = {0};
long long overallCnt = 0;
int searched[6] = {0}; // 代表已经搜索过的房间 
int lastRoom = 0; // 最后观测到人的房间，或者是目标房间 
int lastX = 0; // 最后观测到人的坐标，或者是目标坐标 
int lastY = 0;
bool rotate = 0; // rotate参数记录机器人是否已经环视搜寻过。环视搜寻应该向人消失的方向开始转。
 
/** 
 * 下面的回调是对收到信息的处理，我预计有规律的收到位置信息 
 */
void positionCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("receive position info: [%s]", msg->data.c_str()); // debug string
  
  std::stringstream ss;
  ss << msg->data.c_str();
  int state, room;
  double x, y, x1, y1;
  ss >> state >> room >> x >> y >> x1 >> y1;
  
  if (state == 1)
  {
  	overallCnt++;
  	modelCnt[room]++;
  	for(int i = 0; i < 6; ++i)
	  searched[i] = 0;
	lastRoom = room;
	lastX = x;
	lastY = y;
	rotate = 0;
  	// 如果找到了人，那么在这个分支里直接往人的方向走
	moveTo(room, x, y, x1, y1); // 需要完善一下这个函数，进行机器人运动控制 
  }
  else
  {
  	if (fabs(x1 - lastX) > 1 || fabs(y - lastY) > 1) // 还没到达 
  		moveTo(lastRoom, lastX, lastY, x1, y1);
  	else if (rotate == 0)
  	{
	  rotateSearch(); // 环视搜寻 
	  rotate = 1; // 需要改进，具体最好是正好转了一圈的时候记为1，而非rotateSearch调用马上记1，因为可能rotateSearch一次调用不足以转一圈 
    }
  	else if (rotate == 1)
  	{
  	  searched[lastRoom] == 1; // 到达了最后看到人的位置，而且转了一圈还没看到人，则标记已经找过这里 
      // 视野中没有出现人，首先去人消失的房间找
      int mostFrequent = -1;
      int frequency = 0;
      for (int i = 0; i < 6; ++i)
      {
        if (searched[i] == 1)
          continue;
		if (modelCnt[i] > frequency)
		{
		  mostFrequent = i;
		  frequency = modelCnt[i];
		}
	  }
	  if (mostFrequnt = -1)
	  {
	  	for(int i = 0; i < 6; ++i)
	      searched[i] = 0;
	    int mostFrequent = -1;
        int frequency = 0;
        for (int i = 0; i < 6; ++i)
        {
          if (searched[i] == 1)
            continue;
		  if (modelCnt[i] > frequency)
		  {
		    mostFrequent = i;
		    frequency = modelCnt[i];
		  }
	    }
	  }
	  // 上述过程应该找到了一个还没搜索过的去的最频繁的地方 
	  lastRoom = mostFrequent;
	  lastX = middleX(mostFrequent);
	  lastY = middleY(mostFrequent);
	  moveTo(lastRoom, lastX, lastY, x1, y1); // 没有具体坐标时，预计middleX和Y返回房间中间地址 
    }
  }
}
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "move");
 
  ros::NodeHandle n;
  
  // 如你所见，应该有一个叫做position的topic 
  ros::Subscriber sub = n.subscribe("position", 1000, positionCallback);
 
  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();
 
  return 0;
}
