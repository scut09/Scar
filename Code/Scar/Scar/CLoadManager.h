
#ifndef CLOADMANAGER_H 
#define CLOADMANAGER_H 

#include <ISceneManager.h>
#include <IVideoDriver.h>

#include "CLoadCallback.h"
#include "CThread.h"

using namespace irr;

class CLoadManager : CThread
{
public:
   CLoadManager(CLoadCallback* cb, scene::ISceneManager* smgr);
   ~CLoadManager();

   void addMesh(const io::path& filename, const s32 id = -1);
   void addTexture(const io::path& filename, const s32 id = -1);

   virtual void run();

private:
   void add(const io::path& filename, const s32 id, const E_LOAD_EVENT_TYPE type);

   core::list<SLoadEvent> loadList;

   scene::ISceneManager* smgr;

   CLoadCallback* cb;
};

#endif