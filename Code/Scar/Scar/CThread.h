#ifndef CTHREAD_H 
#define CTHREAD_H 

#include <boost/thread/thread.hpp>

class CThread
{
public:
   CThread();
   virtual ~CThread();

   virtual void run() {};

   bool start();
   bool stop();

   volatile bool isRunning() { return threadRun; };

   // as a class member the mutex is used to ensure thread-safety 
   // while accessing any data in this class by another thread
   boost::mutex mutex; 

protected:
   volatile bool threadRun;
   boost::thread* thread;
};

#endif