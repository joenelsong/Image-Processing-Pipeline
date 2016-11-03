#include "filters.h"
#include <logging.h>

using namespace std;

void Shrinker::Execute()
{

// Exception Handling
if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}



int w = mImgPtr1->GetWidth()/2;
int h = mImgPtr1->GetHeight()/2;
mImg.ResetSize(w, h);
//fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());


Pixel* tmpOut = mImg.GetDataBufferReference();
Pixel* tmpIn = mImgPtr1->GetDataBufferReference();

//fprintf(stderr, "size of buffer: %d\n", sizeof(output.GetDataBufferReference()));
for (int j=0; j <mImg.GetWidth(); j++) {
    for (int i=0; i <mImg.GetHeight(); i++) {
           tmpOut[i*mImg.GetWidth() + j].SetR(tmpIn[i*2*mImgPtr1->GetWidth() + j*2].GetR());
	   tmpOut[i*mImg.GetWidth() + j].SetG(tmpIn[i*2*mImgPtr1->GetWidth() + j*2].GetG());
	   tmpOut[i*mImg.GetWidth() + j].SetB(tmpIn[i*2*mImgPtr1->GetWidth() + j*2].GetB());
        }
    }
}

void LRConcat::Execute()
{
if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
if (mImgPtr2==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 2: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
// <Exception Screening>
if ( mImgPtr1->GetHeight() != mImgPtr2->GetHeight() ) {
	char msg[1024];
	sprintf(msg, "%s: heights must match: %d, %d", SinkName(), mImgPtr1->GetHeight() , mImgPtr2->GetHeight() );
	DataFlowException e(SinkName(), msg);
	throw e;
}




/*****************************************************************************************************
** Takes two images as arguments and places the second image directly to the right of the first image
*****************************************************************************************************/
    int w = mImgPtr1->GetWidth() + mImgPtr2->GetWidth();
    int h = (mImgPtr1->GetHeight() >= mImgPtr2->GetHeight()) ? (mImgPtr1->GetHeight()) : (mImgPtr2->GetHeight());
    mImg.ResetSize(w, h);
    //fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());

    Pixel* tmpLeft = mImgPtr1->GetDataBufferReference();
    Pixel* tmpRight = mImgPtr2->GetDataBufferReference();
    Pixel* tmpOut = mImg.GetDataBufferReference();

// Populate left image //
for (int j = 0; j<mImgPtr1->GetWidth(); j++) {
    for (int i = 0; i < h; i++) {
	tmpOut[i*mImg.GetWidth() + j].SetR(tmpLeft[i*mImgPtr1->GetWidth() + j].GetR());
        tmpOut[i*mImg.GetWidth() + j].SetG(tmpLeft[i*mImgPtr1->GetWidth() + j].GetG());
        tmpOut[i*mImg.GetWidth() + j].SetB(tmpLeft[i*mImgPtr1->GetWidth() + j].GetB());
    }
}
// Populate right image //
for (int j = 0; j<mImgPtr2->GetWidth(); j++) {
    for (int i = 0; i < h; i++) {
	tmpOut[i*mImg.GetWidth() + mImgPtr1->GetWidth()+  j].SetR(tmpRight[i*mImgPtr2->GetWidth() + j].GetR());
        tmpOut[i*mImg.GetWidth() + mImgPtr1->GetWidth()+  j].SetG(tmpRight[i*mImgPtr2->GetWidth() + j].GetG());
        tmpOut[i*mImg.GetWidth() + mImgPtr1->GetWidth()+  j].SetB(tmpRight[i*mImgPtr2->GetWidth() + j].GetB());
    }
}

};

void TBConcat::Execute()
{
/*****************************************************************************************************
** Takes two images as arguments and places the second image directly below of the first image
*****************************************************************************************************/
if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
if (mImgPtr2==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 2: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}   

if ( mImgPtr1->GetWidth() != mImgPtr2->GetWidth() ) {
	char msg[1024];
	sprintf(msg, "%s: widths must match: %d, %d", SinkName(), mImgPtr1->GetWidth(), mImgPtr2->GetWidth());
	DataFlowException e(SinkName(), msg);
	throw e;
     }



    int w = (mImgPtr1->GetWidth() >= mImgPtr2->GetWidth()) ? (mImgPtr1->GetWidth()) : (mImgPtr2->GetWidth());
    int h = mImgPtr1->GetHeight() + mImgPtr2->GetHeight();
    mImg.ResetSize(w, h);
    //fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());

    Pixel* tmpTop= mImgPtr1->GetDataBufferReference();
    Pixel* tmpBottom = mImgPtr2->GetDataBufferReference();
    Pixel* tmpOut = mImg.GetDataBufferReference();


    for (int j = 0; j<w; j++) {
        for (int i = 0; i<mImgPtr1->GetHeight(); i++) {
            tmpOut[i*w+j].SetR(tmpTop[i*w+j].GetR());
            tmpOut[i*w+j].SetG(tmpTop[i*w+j].GetG());
            tmpOut[i*w+j].SetB(tmpTop[i*w+j].GetB());
        }
    }
    int offset = mImgPtr1->GetHeight()*w;
    for (int j = 0; j<w; j++) {
        for (int i = 0; i<mImgPtr2->GetHeight(); i++) {
            tmpOut[i*w+j+offset].SetR(tmpBottom[i*w+j].GetR());
            tmpOut[i*w+j+offset].SetG(tmpBottom[i*w+j].GetG());
            tmpOut[i*w+j+offset].SetB(tmpBottom[i*w+j].GetB());
        }
    }
}


Blender::Blender(float f)
{
    factor = f;
}
Blender::Blender()
{
}


void Blender::Execute()
/*****************************************************************************************************
** 
*****************************************************************************************************/
{

if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
if (mImgPtr2==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 2: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
if (factor>1 || factor<0) {
	char msg[1024];
	sprintf(msg, "%s: Factor must be between 0 and 1 ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}


    if (mImgPtr1->GetWidth() != mImgPtr2->GetWidth()) {
	fprintf(stderr, "Input Dimensions Mismatch! Exiting...");
	//exit(EXIT_FAILURE);
    }
    int w = mImgPtr1->GetWidth();
    int h = mImgPtr1->GetHeight();
    mImg.ResetSize(w, h);
    //fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());

    Pixel* tmpInput1 = mImgPtr1->GetDataBufferReference();
    Pixel* tmpInput2 = mImgPtr2->GetDataBufferReference();
    Pixel* tmpOut = mImg.GetDataBufferReference();

    for (int j = 0; j<w; j++) {
        for (int i = 0; i<h; i++) {
            tmpOut[i*w + j].SetR( tmpInput1[i*w+j].GetR()*factor + tmpInput2[i*w+j].GetR()*(1-factor)  );
            tmpOut[i*w + j].SetG( tmpInput1[i*w+j].GetG()*factor + tmpInput2[i*w+j].GetG()*(1-factor)  );
            tmpOut[i*w + j].SetB( tmpInput1[i*w+j].GetB()*factor + tmpInput2[i*w+j].GetB()*(1-factor)  );
        }
    }

}


void
Crop::Execute(void)
{
    if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}


    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= mImgPtr1->GetWidth() || Istop >= mImgPtr1->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= mImgPtr1->GetHeight() || Jstop >= mImgPtr1->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int heightL = Jstop-Jstart+1;
    int widthL  = Istop-Istart+1;
    int inputWidth = mImgPtr1->GetWidth();
    mImg.ResetSize(widthL, heightL);
    Pixel *buffer = mImg.GetDataBufferReference();
    Pixel *buffer1 = mImgPtr1->GetDataBufferReference();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*widthL+(i-Istart);
            buffer[idx].SetR(buffer1[idx1].GetR());
            buffer[idx].SetG(buffer1[idx1].GetG());
            buffer[idx].SetB(buffer1[idx1].GetB());
        }
}

void Transpose::Execute()
{

// Exception Handling
if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}

int w = mImgPtr1->GetHeight();
int h = mImgPtr1->GetWidth();
mImg.ResetSize(w, h);
//fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());


Pixel* tmpOut = mImg.GetDataBufferReference();
Pixel* tmpIn = mImgPtr1->GetDataBufferReference();

//fprintf(stderr, "size of buffer: %d\n", sizeof(output.GetDataBufferReference()));
for (int j=0; j <mImg.GetWidth(); j++) {
    for (int i=0; i <mImg.GetHeight(); i++) {
           tmpOut[i*mImg.GetWidth() + j].SetR(tmpIn[j*mImgPtr1->GetWidth() + i].GetR());
	   tmpOut[i*mImg.GetWidth() + j].SetG(tmpIn[j*mImgPtr1->GetWidth() + i].GetG());
	   tmpOut[i*mImg.GetWidth() + j].SetB(tmpIn[j*mImgPtr1->GetWidth() + i].GetB());
    }
}
}


void Invert::Execute()
{

// Exception Handling
if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}

int w = mImgPtr1->GetWidth();
int h = mImgPtr1->GetHeight();
mImg.ResetSize(w, h);
//fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());


Pixel* tmpOut = mImg.GetDataBufferReference();
Pixel* tmpIn = mImgPtr1->GetDataBufferReference();

//fprintf(stderr, "size of buffer: %d\n", sizeof(output.GetDataBufferReference()));
for (int j=0; j <mImg.GetWidth(); j++) {
    for (int i=0; i <mImg.GetHeight(); i++) {
           tmpOut[i*mImg.GetWidth() + j].SetR(255 - tmpIn[i*mImgPtr1->GetWidth() + j].GetR());
	   tmpOut[i*mImg.GetWidth() + j].SetG(255 - tmpIn[i*mImgPtr1->GetWidth() + j].GetG());
	   tmpOut[i*mImg.GetWidth() + j].SetB(255 - tmpIn[i*mImgPtr1->GetWidth() + j].GetB());
        } 
    }
}

void Checkerboard::Execute()
/*********************************************************************************************************
* Takes two input images of identical size and produces an output image of the same size. Pixel(i,j)     *
* of the output should be the same as the pixel (i,j) from the first input image if ((i/10+j/10)%2 == 0) *
* Else it should be pixel (i,j) from the second input image. (Note the i/10 and j/10 are integer arith   *
*********************************************************************************************************/
{

// Exception Handling //
////////////////////////

// NULL input checks
if (mImgPtr1==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 1: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
if (mImgPtr2==NULL) {
	char msg[1024];
	sprintf(msg, "%s: Missing Input 2: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
// Enforce same size input images
if (mImgPtr1->GetWidth()!=mImgPtr2->GetWidth()) {
	char msg[1024];
	sprintf(msg, "%s: Input Image Width Mismatch: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}
if (mImgPtr1->GetHeight()!=mImgPtr2->GetHeight()) {
	char msg[1024];
	sprintf(msg, "%s: Input Image Height Mismatch: ", SinkName());
	DataFlowException e(SinkName(), msg);
	throw e;
}


int w = mImgPtr1->GetWidth();
int h = mImgPtr1->GetHeight();
mImg.ResetSize(w, h);
//fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());


Pixel* tmpOut = mImg.GetDataBufferReference();
Pixel* tmpIn = mImgPtr1->GetDataBufferReference();
Pixel* tmpIn2 = mImgPtr2->GetDataBufferReference();

//fprintf(stderr, "size of buffer: %d\n", sizeof(output.GetDataBufferReference()));
for (int i=0; i < w; i++) {
    for (int j=0; j < h; j++) {
	   if ((i/10 + j/10) % 2 == 0) {
		   tmpOut[j*w + i].SetR(tmpIn[j*w + i].GetR());
		   tmpOut[j*w + i].SetG(tmpIn[j*w + i].GetG());
		   tmpOut[j*w + i].SetB(tmpIn[j*w + i].GetB());
	    }
	    else {
		   tmpOut[j*w + i].SetR(tmpIn2[j*w + i].GetR());
		   tmpOut[j*w + i].SetG(tmpIn2[j*w + i].GetG());
		   tmpOut[j*w + i].SetB(tmpIn2[j*w + i].GetB());
        } 
    }
}


}
Color::Color(int wi, int hi, int r, int g, int b)
{


// Exception Handling

mImg.ResetSize(wi, hi);
//fprintf(stderr, "output size: %d x %d\n", output.GetWidth(), output.GetHeight());

Pixel* tmpOut = mImg.GetDataBufferReference();

//fprintf(stderr, "size of buffer: %d\n", sizeof(output.GetDataBufferReference()));
for (int j=0; j <mImg.GetWidth(); j++) {
    for (int i=0; i <mImg.GetHeight(); i++) {
		   tmpOut[i*mImg.GetWidth() + j].SetR(r);
		   tmpOut[i*mImg.GetWidth() + j].SetG(g);
		   tmpOut[i*mImg.GetWidth() + j].SetB(b);
        } 
    }
}

void Color::Execute()
{}

void Color::Update()
{}

CheckSum::CheckSum()
{}
void CheckSum::OutputCheckSum(char* n)
{

redSum =0;
greenSum=0;
blueSum=0;
    this->name = n;

    int w = mImgPtr1->GetWidth();
    int h = mImgPtr1->GetHeight();

    Pixel* tmpIn = mImgPtr1->GetDataBufferReference();

for (int j=0; j <w; j++) {
    for (int i=0; i <h; i++) {
           this->redSum+=tmpIn[i*mImgPtr1->GetWidth() + j].GetR();
	   this->greenSum+=tmpIn[i*mImgPtr1->GetWidth() + j].GetG();
	   this->blueSum+=tmpIn[i*mImgPtr1->GetWidth() + j].GetB();
    }
}

// Write CheckSum Output
FILE * outputFile = NULL;
outputFile = fopen (this->name, "w+");

   fprintf(outputFile, "CHECKSUM: %d, %d, %d\n",redSum, greenSum, blueSum);

fclose(outputFile);


//printf("Red: %d Green: %d Blue: %d", redSum, greenSum, blueSum);
}


