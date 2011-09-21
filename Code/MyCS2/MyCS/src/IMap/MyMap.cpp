#include "MyMap.h"

namespace MyMap
{
	IrrlichtDevice*		CMyMap::g_device = NULL;
	IGUIEnvironment*	CMyMap::g_guienv = NULL;		//设备对象
	IVideoDriver*		CMyMap::g_driver = NULL;
	ISceneManager*		CMyMap::g_smgr	 = NULL;		//场景管理器

	CMyMap*				CMyMap::g_obj = NULL;			//单例对象

	//////////////////////////////
	///	@brief	创建一个IMap指针	
	///	@return void
	//////////////////////////////
	extern "C" IMAP_API IMap* CreateMap()		//单例对象
	{
		if(NULL ==CMyMap::g_obj)
		{
			CMyMap::g_obj = new CMyMap();
		}
		return CMyMap::g_obj;		
	}
	int GetKillNum(lua_State* L)
	{
		/* 获得参数 */ 
		int index = lua_tonumber(L, 1); 
		if (NULL == CMyMap::g_obj->m_playerList[index])
		{
			/* 返回值 */ 
			lua_pushnumber(L, 0); 
			return 1;
		}
		int killcount = CMyMap::g_obj->m_playerList[index]->m_killCount; 

		/* 返回值 */ 
		lua_pushnumber(L, killcount); 
		return 1;
	}

	CMyMap::CMyMap(void)
	{
		
	}

	CMyMap::~CMyMap(void)
	{
		
	}

	void CMyMap::LoadMap( const char* mapname )
	{
		m_Lua = lua_open(); 

		std::string str = "model/map/";
		str += mapname;
		str += ".lua";
		luaL_dofile(m_Lua, str.c_str());

		LoadPosition();

		luaopen_base(m_Lua); 
		/* 注册函数 */ 
		lua_register(m_Lua, "GetKillNum", GetKillNum);
		
		

		str = "model/map/";
		str += mapname;
		str+=".3DS";
		m_node = g_smgr->addMeshSceneNode(g_smgr->getMesh(str.c_str()));
		m_node->setMaterialFlag(video::EMF_LIGHTING, false);


		str = "model/map/";
		str += mapname;
		str+= ".jpg";

		video::ITexture* texture = g_driver->getTexture(str.c_str());
		if (NULL != texture)
		{
			m_node->setMaterialTexture(0,texture);
		}

		scene::ITriangleSelector* selector = 0;
		selector = g_smgr->createTriangleSelector(m_node->getMesh(), m_node);
		m_node->setTriangleSelector(selector);
		selector->drop();
	}

	void CMyMap::Release()
	{
		m_node->removeAll();
		m_node->remove();
		lua_close(m_Lua);
	}

	bool CMyMap::IsWin( bool* winner )
	{
		lua_getglobal(m_Lua, "IsWin");
		lua_call(m_Lua, 0, 5);		
		bool rueslt = lua_tointeger(m_Lua, -5);
		for (int i = 0; i < 4; i++)
		{			
			winner[i] = lua_tointeger(m_Lua, i - 4); 
		}
		lua_pop(m_Lua, 5);
		return rueslt;
	}

	void CMyMap::SetPlayerList( void** playerlist )
	{
		m_playerList =(IHreo**) playerlist;
	}

	core::vector3df CMyMap::GetStartPostion( int index )
	{
		return m_Postion[index];
	}

	void CMyMap::SetDevice( IrrlichtDevice* device )
	{
		g_device = device;
		g_smgr = g_device->getSceneManager();
		g_driver = g_device->getVideoDriver();
		g_guienv = g_device->getGUIEnvironment();
	}

	void CMyMap::LoadPosition()
	{
		int x,y,z;
		for(int i = 0; i < 4; i++)		//在lua中加载位置信息
		{
			lua_getglobal(m_Lua, "getPosition");
			lua_pushnumber(m_Lua, i); 
			lua_call(m_Lua, 1, 3);
			x = lua_tointeger(m_Lua, 1); 
			y = lua_tointeger(m_Lua, 0); 
			z = lua_tointeger(m_Lua, -1);
			m_Postion[i] = core::vector3df(x,y,z);
			lua_pop(m_Lua, 3);
		}
	}

	int CMyMap::CharCpy( char* des, const char* src , int offset)
	{
		int len = 0;
		while (src[len] != '\0')
		{			
			des[offset+len] = src[len];
			len++;
		}
		des[offset+len] = '\0';
		return len;
	}
}