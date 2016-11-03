#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#include "image.h"
class Source
{
protected:
    Image mImg;

public:
    Source();
   // ~Source(){ delete mImg; };
    Image* GetOutput(void);
   virtual void Update(void) = 0;
   virtual const char* SourceName(void) = 0;
protected:
   bool hasOutput;

protected:
    virtual void Execute(void) = 0;
};

#endif
