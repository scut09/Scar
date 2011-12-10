#include "CLoadCallback.h"
#include "CLoadManager.h"

class CMyApp : CLoadCallback
{
public:
	CMyApp(scene::ISceneManager* smgr) : loadManager(this, smgr)
	{}

	void doSomething()
	{
		loadManager.addMesh("ship.3ds", 0);  
		//do other staff while loading     
	}

	virtual void loadEvent(const SLoadEvent& event) 
	{
		switch(event.eventType)
		{
		case ELET_MESH:
			switch(event.id)
			{   
			case 0:
				//mesh is loaded get it with smgr->getMesh(event.filename);
				return;
			default:
				printf("Mesh loaded '%s' (ID: %d).\n", event.filename, event.id);
				return;
			}
		case ELET_TEXTURE:
			switch(event.id)
			{   
			default:
				printf("Texture loaded '%s' (ID: %d).\n", event.filename, event.id);
				return;
			}
		case ELET_ERROR:
			printf("Failed to load '%s' (ID: %s)\n", event.filename, event.id);
			return;
		}
	}

private:
	CLoadManager loadManager;
};