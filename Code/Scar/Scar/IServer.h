/********************************************************************
	����ʱ��: 2011-9-27   15:00
	�ļ���:   IServer.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#ifndef _ISERVER_H
#define _ISERVER_H


/*
** ���֣�IServer
** ˵�����������ӿ�
**
*/
class IServer
{
public:

	virtual int CreateGameRoom( 
		int maxPlayerNumber, 
		const std::string& gameRoomName 
		) = 0;

	//************************************
	// ������:  IServer::Start
	// ����ֵ:  int
	// ��������:
	// ������   
	//************************************
	virtual int Start() = 0;

	//************************************
	// ������:  IServer::Stop
	// ����ֵ:  int
	// ��������:
	// ������   
	//************************************
	virtual int Stop() = 0;

};



#endif