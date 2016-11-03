#include "PNMwriter.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>


PNMwriter::PNMwriter()
{

}


void PNMwriter::Write(char* filename)
{
FILE *f = fopen(filename, "wb");
if (f == NULL)
{
    printf("Cannot open '%s' for writing!\n", filename);
    exit(EXIT_FAILURE);
}

fprintf(f, "P6\n");
fprintf(f, "%d %d\n", mImgPtr1->GetWidth(), mImgPtr1->GetHeight());
fprintf(f, "%d\n", 255);
Pixel* tmpbuf = new Pixel[mImgPtr1->GetWidth()*mImgPtr1->GetHeight()];

fwrite(mImgPtr1->GetDataBufferReference(), sizeof(Pixel), mImgPtr1->GetHeight() * mImgPtr1->GetWidth(), f);
fclose(f);
delete tmpbuf;
}
