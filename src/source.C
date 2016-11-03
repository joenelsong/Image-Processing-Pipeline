
#include "source.h"
#include "image.h"
#include <logging.h>

Source::Source(){
    mImg.SetSource(this);
    hasOutput = 0;
}

Image* Source::GetOutput(void){
return &mImg; 
}
