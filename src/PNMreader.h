#ifndef PNMreader_H
#define PNMreader_H
#include <source.h>

class PNMreader :public Source {
public:
    PNMreader(char *filename);
    virtual ~PNMreader();

    virtual void Execute(void);
    virtual const char * SourceName() { return "PNM Reader"; };
    Image* GetOutput(void) { return &mImg; }; 
    void Update(void);

private:
    char* mFileName;
    //Image mImg;
};
#endif
