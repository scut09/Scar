///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/14 20:06
//description:	��Ϸ��������ṹ
///////////////////////////////////////////////////////

#ifndef CMDStruct_h
#define CMDStruct_h

#define MyNameLength 20

enum CMD					//SCMD��ʾ��������Ϣ CCMD��ʾ�ͻ�����Ϣ CMD��ʾͨ����Ϣ
{
	CMD_Heartbeat,			//����������

	SCMD_CreatHost,			//��������			������������(char name[MyNameLength])
	SCMD_CancelHost,		//ȡ������			none
	SCMD_HostCurrentNum,	//������ǰ����		����������(int count)
	SCMD_HostMember,		//������Ա

	CCMD_QueryHost,			//��ѯ����			none
	SCMD_RQueryHost,		//�ظ�������ѯ		������������(char name[MyNameLength])

	CCMD_RequestJion,		//�����������
	SCMD_OKRequestJion,		//�ظ������������	����ɹ�	���������䵽������(int index)
	SCMD_ERRORRequestJion,	//�ظ������������	����ʧ��	none

	SCMD_BeignGame,			//��Ϸ��ʼ	none

	CCMD_ExitHost,			//�˳�����		����������(int index)
	CCMD_ExitGame,			//�˳���Ϸ		����������(int index)
	
	CMD_GlobeChat,			//����Ƶ����������Ϣ
	CMD_GameChat,			//��Ϸ�е�������Ϣ

	CMD_GameCMD,			//��Ϸ����

	CMD_HreoMove,			//�ƶ�
	CMD_HreoTrun,			//��ת
	CMD_bulletAttack,		//�ӵ�����
	CMD_Squat,				//����
	CMD_Reset,				//���� ������ ����:index
	CMD_Winner,				//��ʤ ����:bool[4]
	

};

//---------------------------------------
//des:���������Ĳ���
//---------------------------------------
struct CreateHostStruct
{
	char name[MyNameLength];	//�û���
	char mapName[30];			//��ͼ����
};

struct OKRequestJion
{
	int index;				//���䵽������
	char mapName[30];		//��ͼ����
};

//---------------------------------------
//des:������������Ĳ���
//---------------------------------------
struct RequestJion
{
	char name[MyNameLength];	//�û���
};

//------------------------------
//Desc:�ظ�������ѯ
//------------------------------
struct RQueryHost
{
	char name[MyNameLength];	//������
};

//---------------------------------------
//des:������Ա
//---------------------------------------
struct HostMember
{
	int index;
	char name[MyNameLength];
};

//---------------------------------------
//des:����Ƶ����������Ϣ�Ĳ���
//---------------------------------------
struct GlobeChat
{
	char name[MyNameLength];	//�û����20�ֽ�
	char msg[30];	//��Ϣ�30�ֽ�
};

//---------------------------------------
//des:��Ϸ�е�������Ϣ�Ĳ���
//---------------------------------------
struct GameChat
{
	int	index;		//�û������
	char msg[80];	//��Ϣ�200�ֽ�
};

struct HreoMove
{
	int index;		//Ӣ�۱��
	int x;			//�ƶ�����
	int y;			//�ƶ�����
	int z;			//�ƶ�����
};

struct HreoTrun
{
	int index;		//Ӣ�۱��	
	float y;
};

struct bulletAttack
{
	int ownindex;	//ӵ���ߵ�ID
	int killIndex;	//���е�Ŀ��
	float x;		//�ӵ���λ��
	float y;
	float z;

};

struct Squat
{
	int index;
	bool issquat;
};
#endif