/* Author: Joey Nelson
** Date: 5/6/2015
*/
#ifndef IMAGE_C
#define IMAGE_C
#define DEBUGGING
#ifdef DEBUGGING 
#define MDS fprintf(stderr, "%s: %d\n",__FILE__,__LINE__);
#else
#define MDS
#endif
#include <image.h>
#include <stdlib.h>
#include <source.h>
#include <iostream>

int Image::SetHeight(int h) { height = h; };
int Image::SetWidth(int w) { width = w; };
int Image::ResetSize(int w, int h) { 
width = w; height = h; // set width and height
buffer = new Pixel[w*h]; // initialize empty buffer of size w*h Pixels
};

void Image::SetSource(Source * s){
    src = s;
}

int  Image::GetWidth(void) const {return width; };
int  Image::GetHeight(void) const {return height; };
Pixel* Image::GetDataBufferReference(void) const { return buffer; };


void PrintImage(Image &img){
printf("Image Width: %d\n Image Height: %d\n", img.GetWidth(), img.GetHeight());
}

Image::Image()
{
    width = height = 0;
    src = NULL;
    //SetSource(NULL);

}
Image::Image(int w, int h) // If initialized this way, do not call ResetSize()
{
    width = w; height = h;
    buffer = new Pixel[w*h];
}
Image::Image(Image &obj)
{
    width = obj.GetWidth();
    height = obj.GetWidth();
    buffer = new Pixel[width*height];
    buffer=obj.GetDataBufferReference(); 
}

Image::~Image()
{
 //  delete [] buffer;
}

void Image::Update() const
{
    
   //std::cerr << "...Updating Image1 \n";
   if (src != NULL) {
      //std::cerr << "...Updating Image2 \n";
      src->Update();
    }
}

/*int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Invalid Syntax must specify input and output files");
        exit(0);
    }
 //  Read an image, apply yellow diagonal to it, then write

Image img, img2;
char* fileName = argv[1];
ReadImage(fileName, img);
YellowDiagonal(img);
WriteImage(argv[2], img);	
return 0;
}
*/

#endif
