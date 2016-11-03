#include <filter.h>
#include <iostream>
#include <logging.h>


void Filter::Update()
{
   
   // Circle Update Dependency Check
   UpdateCallCount++;
   if (UpdateCallCount > 1000) {
	char msg[1024];
	sprintf(msg, "%s: Circle Update Calls : ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
    }
    fprintf(stderr, "Call Count for %s at %d\n", SinkName(), UpdateCallCount);

   //std::cerr << "Updating Filter \n" << std::endl;
   if (mImgPtr1 != NULL) {
        char msg[128];
        sprintf(msg, "%s: start updating input1", SourceName());
        Logger::LogEvent(msg);

        mImgPtr1->Update();
        
        sprintf(msg, "%s: finish updating input1", SourceName());
        Logger::LogEvent(msg);
   }
   else {
      /// throw exception
   }


   if (mImgPtr2 != NULL) {
       char msg[128];
       sprintf(msg, "%s: start updating input2", SourceName());
       Logger::LogEvent(msg);

       mImgPtr2->Update();

       sprintf(msg, "%s: finish updating input2", SourceName());
       Logger::LogEvent(msg);
   }

   char msg[128];
   timeval tim;
   gettimeofday(&tim, NULL);
   double startTime = tim.tv_sec+(tim.tv_usec/1000000.0);

   sprintf(msg, "%6lf %s: start executing filter",startTime, SourceName());
   Logger::LogEvent(msg);

   Execute();

   gettimeofday(&tim, NULL);

   double finishTime = tim.tv_sec+(tim.tv_usec/1000000.0);
   sprintf(msg, "%.6lf %s: finish executing filter",finishTime, SourceName());
   Logger::LogEvent(msg);

   sprintf(msg, "%s: execution elapsed time : %.6lf", SourceName(), finishTime-startTime);
   Logger::LogEvent(msg);

   hasOutput = 1;
}

