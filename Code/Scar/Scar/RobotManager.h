///********************************************************************
//    ����ʱ��: 2011-11-7   14:07
//    �ļ���:   RobotManager.h
//    ����:     ���� Cedric Porter [ Stupid ET ]	
//    ˵��:     AI�����˹�����
//
//*********************************************************************/
//
//#ifndef RobotManager_h__
//#define RobotManager_h__
//
//#include "IRobot.h"
//#include <list>
//
//class RobotManager
//{
//public:
//	void AddRobot( boost::shared_ptr<IRobot> robot )
//	{
//		Robots.push_back( robot	 );
//	}
//
//	void RemoveRobot( boost::shared_ptr<IRobot> robot )
//	{
//		Robots.remove( robot );
//	}
//
//	void Update()
//	{
//		for ( auto iter = Robots.begin(); iter != Robots.end(); ++iter )
//		{
//			(*iter)->Update();
//		}
//	}
//
//private:
//	std::list<boost::shared_ptr<IRobot> > Robots;
//};
//
//
//#endif // RobotManager_h__