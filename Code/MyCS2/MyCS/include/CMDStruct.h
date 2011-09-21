///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/14 20:06
//description:	游戏命令参数结构
///////////////////////////////////////////////////////

#ifndef CMDStruct_h
#define CMDStruct_h

#define MyNameLength 20

enum CMD					//SCMD表示服务器消息 CCMD表示客户端消息 CMD表示通用消息
{
	CMD_Heartbeat,			//心跳包命令

	SCMD_CreatHost,			//创建主机			参数：主机名(char name[MyNameLength])
	SCMD_CancelHost,		//取消主机			none
	SCMD_HostCurrentNum,	//主机当前人数		参数：人数(int count)
	SCMD_HostMember,		//主机成员

	CCMD_QueryHost,			//查询主机			none
	SCMD_RQueryHost,		//回复主机查询		参数：主机名(char name[MyNameLength])

	CCMD_RequestJion,		//请求加入主机
	SCMD_OKRequestJion,		//回复请求加入主机	加入成功	参数：分配到的索引(int index)
	SCMD_ERRORRequestJion,	//回复请求加入主机	加入失败	none

	SCMD_BeignGame,			//游戏开始	none

	CCMD_ExitHost,			//退出主机		参数：索引(int index)
	CCMD_ExitGame,			//退出游戏		参数：索引(int index)
	
	CMD_GlobeChat,			//公共频道的聊天消息
	CMD_GameChat,			//游戏中的聊天消息

	CMD_GameCMD,			//游戏命令

	CMD_HreoMove,			//移动
	CMD_HreoTrun,			//旋转
	CMD_bulletAttack,		//子弹攻击
	CMD_Squat,				//蹲下
	CMD_Reset,				//重置 即复活 参数:index
	CMD_Winner,				//获胜 参数:bool[4]
	

};

//---------------------------------------
//des:创建主机的参数
//---------------------------------------
struct CreateHostStruct
{
	char name[MyNameLength];	//用户名
	char mapName[30];			//地图名字
};

struct OKRequestJion
{
	int index;				//分配到的索引
	char mapName[30];		//地图名字
};

//---------------------------------------
//des:请求加入主机的参数
//---------------------------------------
struct RequestJion
{
	char name[MyNameLength];	//用户名
};

//------------------------------
//Desc:回复主机查询
//------------------------------
struct RQueryHost
{
	char name[MyNameLength];	//主机名
};

//---------------------------------------
//des:主机成员
//---------------------------------------
struct HostMember
{
	int index;
	char name[MyNameLength];
};

//---------------------------------------
//des:公共频道的聊天消息的参数
//---------------------------------------
struct GlobeChat
{
	char name[MyNameLength];	//用户名最长20字节
	char msg[30];	//消息最长30字节
};

//---------------------------------------
//des:游戏中的聊天消息的参数
//---------------------------------------
struct GameChat
{
	int	index;		//用户名编号
	char msg[80];	//消息最长200字节
};

struct HreoMove
{
	int index;		//英雄编号
	int x;			//移动方向
	int y;			//移动方向
	int z;			//移动方向
};

struct HreoTrun
{
	int index;		//英雄编号	
	float y;
};

struct bulletAttack
{
	int ownindex;	//拥有者的ID
	int killIndex;	//击中的目标
	float x;		//子弹的位置
	float y;
	float z;

};

struct Squat
{
	int index;
	bool issquat;
};
#endif