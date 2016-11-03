#ifndef FILTER_H
#define FILTER_H
#include "source.h"
#include "sink.h"

class Filter : public Source, public Sink
{
    protected:
        virtual void Update(void);
        //virtual const char * SourceName(void)=0;
        virtual const char * SinkName(void)=0;
	//virtual const char * FilterName(void)=0;

    public:
	int UpdateCallCount = 0;

};


#endif
