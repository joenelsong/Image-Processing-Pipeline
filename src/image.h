#ifndef IMAGE_H
#define IMAGE_H
#include <stdio.h>

class Source;

class Pixel
{
private:	
	unsigned char r; // red
	unsigned char g; // green
	unsigned char b; // blue
public:
    void SetR(unsigned char c) { r = c; };
    void SetG(unsigned char c) { g = c; };
    void SetB(unsigned char c) { b = c; };
    unsigned char GetR(void) { return r; };
    unsigned char GetG(void) { return g; };
    unsigned char GetB(void) { return b; };
};

class Image
{
public:
   // Constructors
   Image();
   ~Image();
   Image(int w, int h);
   Image(Image &obj); 
	int GetHeight(void) const;
	int GetWidth(void) const;
    Pixel * GetDataBufferReference(void) const;
    int SetHeight(int h);
    int SetWidth(int w);
    int ResetSize(int w, int h);
    void Update(void) const;
    void SetSource(Source* s);
    Source * src;
private:
	int height;
	int width;
	Pixel * buffer; // buffer       
	
};



#endif
