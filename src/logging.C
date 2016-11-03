#include<logging.h>
#include<stdio.h>

FILE * Logger::logger = NULL;

void Logger::LogEvent(const char *event){
   if (logger == NULL) {
   	logger = fopen ("RunLog.txt", "w+");
   }
    fprintf(logger, "%s \n", event);
}

void Logger::Finalize(){
  fclose(logger);
}

DataFlowException::DataFlowException(const char *type, const char *error)
{
char msg[128];
sprintf(msg, "Throwing Exception: (%s): %s", type, error);
Logger::LogEvent(msg);
}
