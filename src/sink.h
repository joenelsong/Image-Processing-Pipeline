#ifndef SINK_H
#define SINK_H
#include "image.h"
class Sink
{
protected:
    const Image *mImgPtr1 = NULL;
    const Image *mImgPtr2 = NULL;       

public:
    Sink();
    ~Sink(); 
    void SetInput(Image* img) { mImgPtr1 = img; };
    void SetInput2(Image* img) { mImgPtr2 = img; };
    virtual const char * SinkName(void) = 0;
};

#endif
