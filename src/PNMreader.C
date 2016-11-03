#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "PNMreader.h"
#include "image.h"
PNMreader::PNMreader(char *filename)
{
mFileName = filename;
}

PNMreader::~PNMreader()
{
   //delete mImg;
   //delete &mFileName;
}

void PNMreader::Update()
{
   Execute();
}

void PNMreader::Execute()
{    
    FILE *f_in = fopen(mFileName, "rb");
    char magicNum[128];
    int width, height, maxval;

    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    mImg.ResetSize(width, height);
    fread(mImg.GetDataBufferReference(), sizeof(Pixel),width*height, f_in);
}
