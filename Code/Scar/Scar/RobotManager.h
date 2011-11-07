/********************************************************************
    创建时间: 2011-11-7   14:07
    文件名:   RobotManager.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     AI机器人管理类

*********************************************************************/

#ifndef RobotManager_h__
#define RobotManager_h__

#include "IRobot.h"
#include <list>

class RobotManager
{
public:
	void AddRobot( std::shared_ptr<IRobot> robot )
	{
		Robots.push_back( robot	 );
	}

	void RemoveRobot( std::shared_ptr<IRobot> robot )
	{
		Robots.remove( robot );
	}

	void Update()
	{
		for ( auto iter = Robots.begin(); iter != Robots.end(); ++iter )
		{
			(*iter)->Update();
		}
	}

private:
	std::list<std::shared_ptr<IRobot> > Robots;
};


#endif // RobotManager_h__