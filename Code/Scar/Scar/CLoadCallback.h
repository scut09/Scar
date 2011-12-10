
#ifndef CLOADCALLBACK_H 
#define CLOADCALLBACK_H 

#include <IAnimatedMesh.h>
#include <irrlicht.h>

using namespace irr;

enum E_LOAD_EVENT_TYPE
{
   ELET_TEXTURE,
   ELET_MESH,

   ELET_ERROR
};

struct SLoadEvent
{
   irr::s32 id;
   irr::io::path filename;

   E_LOAD_EVENT_TYPE eventType;
};

class CLoadCallback 
{
public:
   CLoadCallback() {};
   virtual ~CLoadCallback() {};

   virtual void loadEvent(const SLoadEvent& event) {};

private:
};

#endif