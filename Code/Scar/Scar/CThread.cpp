#include "CThread.h"

CThread::CThread() 
   : threadRun(false) 
{
   thread = nullptr;
}

CThread::~CThread() 
{
   stop();
}

bool CThread::start()
{   
   if(threadRun)
      return false;

   if(thread)
      stop();

   threadRun = true;
   
   thread = new boost::thread(&CThread::run, this); 

   if(!thread)
      threadRun = false;

   return threadRun;
}

bool CThread::stop()
{
   if(!thread) 
      return false;

   threadRun = false; //thread loop ende

   thread->join(); //warten bis thread ende

   //hier keine 2 threads mehr
   
   return true;
}