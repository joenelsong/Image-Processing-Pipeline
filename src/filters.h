#ifndef FILTERS_H
#define FILTERS_H
#include <filter.h>
#include <source.h>

class Shrinker : public Filter
{
    public:
	virtual void  Execute();
        const char * SourceName(void) { return "Shrinker: "; };
        const char * SinkName(void) { return "Shrinker: "; };
	const char * FilterName(void) { return "Shrinker: "; };

	//void SetInput(Image* img);
	//Image GetOutput(void);
   protected:
	//static char * mFilterName = "Shrinker";
};

class LRConcat : public Filter
{
    public:
	virtual void  Execute();
        virtual const char * SourceName(void) { return "LRConcat: "; };
        virtual const char * SinkName(void) { return "LRConcat: "; };
	virtual const char * FilterName(void) { return "LRConcat: "; };
   protected:
	//static char * mFilterName = "LRConcat";
};

class TBConcat : public Filter
{
    public:
	virtual void  Execute();
        virtual const char * SourceName(void) { return "TBConcat: "; };
        virtual const char * SinkName(void) { return "TBConcat: "; };
	virtual const char * FilterName(void) { return "TBConcat: "; };
   protected:
	//static char * mFilterName = "TBConcat";
};

class Blender : public Filter
{
    public:
	virtual void  Execute();
        const char * SourceName(void) { return "Blender: "; };
        const char * SinkName(void) { return "Blender: "; };
	const char * FilterName(void) { return "Blender: "; };
	Blender(float f);
	Blender();
	void SetFactor(float f){ factor = f; };
    protected:
	float factor;
	//static char * mFilterName = "Blender";

};

class Color : public Source
{
	public:
		Color(int height, int width, int r, int g, int b);  
	protected:
	        virtual void Update(void);
		virtual void  Execute();
		const char * SourceName(void) { return "Color: "; };
};



class Crop : public Filter
{
  public:
                   Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName() { return "Crop"; };
    virtual const char *SourceName() { return "Crop"; };
    virtual const char *SinkName() { return "Crop"; };
    virtual void   Execute(void);
    void           SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }
  private:
    int Istart, Istop, Jstart, Jstop;
};


class Transpose : public Filter
{
    public:
	void Execute();
	virtual const char *FilterName() { return "Tranpose"; };
	virtual const char *SourceName() { return "Tranpose"; };
	virtual const char *SinkName() { return "Tranpose"; };

    private:
};

class Invert : public Filter
{
    public:
	void Execute();
	virtual const char *FilterName() { return "Invert"; };
	virtual const char *SourceName() { return "Invert"; };
	virtual const char *SinkName() { return "Invert"; };
    private:
};

class Checkerboard : public Filter
{
    public:
	void Execute();
	virtual const char *FilterName() { return "Checkerboard"; };
	virtual const char *SourceName() { return "Checkerboard"; };
	virtual const char *SinkName() { return "Checkerboard"; };

    private:
};

class CheckSum : public Sink
{
    public:
	virtual const char *SinkName() { return "CheckSum"; };
        CheckSum();
	void OutputCheckSum(char*);
	char* name = NULL;
	unsigned char redSum =0;
	unsigned char greenSum=0;
	unsigned char blueSum=0;
};
#endif
