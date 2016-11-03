#include "sink.h"
#ifndef PNMWriter_H
#define PNMWriter_H


class PNMwriter : public Sink
{
public:
    PNMwriter();
    void Write(char* filename);
    virtual const char * SinkName() { return "PNM Writer"; };

};


#endif

