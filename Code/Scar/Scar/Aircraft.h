/********************************************************************
����ʱ��: 2011-9-27   15:51
�ļ���:   Aircraft.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     

*********************************************************************/

#ifndef Aircraft_h__
#define Aircraft_h__

#include "IAircraft.h"

using namespace irr;
using namespace scene;
/*
** ���֣�Aircraft
** ˵����������
**
*/
class Aircraft : public IAircraft
{
private:
	ISceneNode*		m_ptr;
	IFlyBehavior*	m_behavior;


public:
	virtual int Move() 
	{

	}

	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func )
	{

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

	virtual scene::ISceneNode* TestCollision() 
	{

	}

	virtual void Drop() = 0;

};



#endif // Aircraft_h__