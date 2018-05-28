
#include <iostream>
#include <windows.h>
#include <stdlib.h>


using namespace std;

BITMAPFILEHEADER bmpfh;
BITMAPINFOHEADER bmpih;

void GetSize(char* file_name, int* pw, int* ph)
{
    FILE* in = fopen(file_name, "rb");
    fread(&bmpfh, sizeof(bmpfh), 1, in);
    fread(&bmpih, sizeof(bmpih), 1, in);

    *pw = bmpih.biWidth;
    *ph = bmpih.biHeight;
    fclose(in);

};

void ReadImage(char* file_name, unsigned char* b, unsigned char* g, unsigned char* r)
{
    FILE* f = fopen(file_name,"rb");
    fread(&bmpfh, sizeof(bmpfh), 1, f);
    fread(&bmpih, sizeof(bmpih), 1, f);
    for (int i = 0; i < bmpih.biHeight;i++)
    {
        unsigned char p[3];
        for (int j =0; j< bmpih.biWidth;j++)
        {
            fread (&p,3,1,f);
            b[i*bmpih.biWidth + j] = p[0];
            g[i*bmpih.biWidth + j] = p[1];
            r[i*bmpih.biWidth + j] = p[2];
        };
        if (bmpih.biWidth%4)
        {
            fread(&p,4-3*bmpih.biWidth%4,1,f);
        }
    };
    fclose(f);
};

void WriteImage(char* file_name, unsigned char* b, unsigned char* g, unsigned char* r)
{
    FILE* f = fopen(file_name,"wb");
    fwrite(&bmpfh, sizeof(bmpfh), 1, f);
    fwrite(&bmpih, sizeof(bmpih), 1, f);
    for (int i = 0; i < bmpih.biHeight;i++)
    {
        unsigned char p[3];
        for (int j =0; j< bmpih.biWidth;j++)
        {
            fwrite(&p,3,1,f);
            p[0]= b[i*bmpih.biWidth + j];
            p[1]= g[i*bmpih.biWidth + j];
            p[2]= r[i*bmpih.biWidth + j];
        };
        if (bmpih.biWidth%4)
        {
            fwrite(&p,4-3*bmpih.biWidth%4,1,f);
        }
    };
    fclose(f);

};