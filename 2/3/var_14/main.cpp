//2 семестр МиКн,семестровое по окн,номер 2,вариан 14.Окрасить изображение в серый сохраняя яркость
#include <iostream>
#include "ReadImage.h"
#include <cmath>

using namespace std;

unsigned char *b, *g, *r;
int w,h;


int main()
{
    GetSize("input2.bmp",&w,&h);
    int bb,gg,rr;
    b = new unsigned char [h*w];
    g = new unsigned char [h*w];
    r = new unsigned char [h*w];

    ReadImage("input2.bmp",b,g,r);

    for (int i = 0; i<h;i++)
    {
        for (int j = 0; j<w;j++)
        {
        	bb=b[i*w+j];
        	gg =g[i*w+j];
        	rr=r[i*w+j];
           if(bb>gg&& bb>rr){
            g[i*w+j]= bb;
            r[i*w+j]= bb;
        }
        if(gg>bb&& gg>rr){
            b[i*w+j]=gg;
            r[i*w+j]= gg;
        }
        if(rr>bb&& rr>gg){
            b[i*w+j]=rr;
            g[i*w+j]= rr;
        }
            
            
        };
        WriteImage("input2.bmp",b,g,r);
    };
    return 0;
}
