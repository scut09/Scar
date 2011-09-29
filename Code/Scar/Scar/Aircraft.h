/********************************************************************
创建时间: 2011-9-27   15:51
文件名:   Aircraft.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     

*********************************************************************/

#ifndef Aircraft_h__
#define Aircraft_h__

#include "IAircraft.h"
#include <list>
#include <def.h>

using namespace irr;
using namespace scene;
using boost::shared_ptr;



/*
** 名字：Aircraft
** 说明：飞行器
**
*/
class Aircraft : public IAircraft
{
private:
	ISceneNode*		m_ptr;
	u32				m_HP;
	core::vector3df m_speed;
	std::function< LPVOID( LPVOID ) >		m_moveCallback;
	std::list< shared_ptr<IFlyBehavior> >	m_behaviorList;


public:
	virtual void SetHP( u32 hp )
	{
		m_HP = hp;
	}

	virtual u32 GetHP() 
	{
		return m_HP;
	}


	virtual void SetSpeed( const core::vector3df& speed )
	{
		m_speed = speed;
	}

	virtual core::vector3df GetSpeed() 
	{
		return m_speed;
	}

	virtual void AddFlyBehavior( shared_ptr<IFlyBehavior> pBehavior ) 
	{
		m_behaviorList.push_back( pBehavior );
	}

	virtual void RemoveFlyBehavior( shared_ptr<IFlyBehavior> pBehavior ) 
	{
		m_behaviorList.remove( pBehavior );
	}

	virtual int Move() 
	{
		std::for_each( m_behaviorList.begin(), m_behaviorList.end(), [ this ]( shared_ptr<IFlyBehavior> b ) { b->Fly( this ); } );
		m_moveCallback( reinterpret_cast<LPVOID>( m_ptr ) );

		return 0;
	}

	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func )
	{
		m_moveCallback = func;
	}

	virtual void LoadSceneNode( scene::ISceneNode* pNode )
	{
		m_ptr = pNode;
	}

	virtual scene::ISceneNode* GetSceneNode()
	{
		return m_ptr;
	}

	virtual void SetPostion( const core::vector3df& pos ) 
	{
		m_ptr->setPosition( pos );
	}

	virtual void SetRotation( const core::vector3df& rot ) 
	{
		m_ptr->setRotation( rot );
	}	

	virtual core::vector3df GetPosition() 
	{
		return m_ptr->getPosition();
	}	

	virtual void Drop() = 0;

};



#endif // Aircraft_h__