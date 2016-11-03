#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    int length = 250;
    

     for (int i = length; i <= 1000; i*=2) {
	//printf("i = %d\n", i);
	     timeval tim;
             gettimeofday(&tim, NULL);
             double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
               
	Color color1(i, i, 255, 0, 0);
        Color color2(i, i, 0, 0, 255);
	Blender blender(0.5);

	blender.SetInput(color1.GetOutput());
	blender.SetInput2(color2.GetOutput());

	blender.GetOutput()->Update();

	     gettimeofday(&tim, NULL);
             double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
             printf("%.6lf seconds elapsed\n", t2-t1);     
    }
}
