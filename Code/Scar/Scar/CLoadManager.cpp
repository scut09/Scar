
#include "CLoadManager.h"

CLoadManager::CLoadManager(CLoadCallback* cb, scene::ISceneManager* smgr)
   : cb(cb), smgr(smgr)
{
}

CLoadManager::~CLoadManager()
{
   loadList.clear();
}

void CLoadManager::addMesh(const io::path& filename, const s32 id)
{
   add(filename, id, ELET_MESH);
}

void CLoadManager::addTexture(const io::path& filename, const s32 id)
{
   add(filename, id, ELET_TEXTURE);
}

void CLoadManager::add(const io::path& filename, const s32 id, const E_LOAD_EVENT_TYPE type)
{
   SLoadEvent load;
   load.id = id;
   load.eventType = type;
   load.filename = filename;

   loadList.push_back(load);

   if(!threadRun)
      start();
}

void CLoadManager::run()
{
   while(!loadList.empty())
   {
      core::list<SLoadEvent>::Iterator it = loadList.begin();

      switch(it->eventType)
      {
      case ELET_MESH:
         if(!smgr->getMesh(it->filename))
            it->eventType = ELET_ERROR;
         break;
      case ELET_TEXTURE:
         if(!smgr->getVideoDriver()->getTexture(it->filename))
            it->eventType = ELET_ERROR;
         break;
      }

      cb->loadEvent(*it);

      loadList.erase(it);
   }
   threadRun = false;
}