#include "Graph2016.h"

#define n 10

double Ay(int k);
void vvod();
void on_console();
double modl(double x);
double find_root();
double sum(double masiv[]);

int p = 0;
double matrix[n][n],f[n],y[n],y_old[n],nevazka[100];
double eps;

main()
{
	vvod();
	
	int chek = 0;
	int asd = 0;
	double A = 0;
	
	FILE *out = fopen("out.txt","w");
	for(int i = 0; i < n; i++)
	{
		if(matrix[i][i] == 0)
		{
			fprintf(out,"Бесконечно много решений.");
			return 0;
		}
	}
	
	while(modl(find_root()) >= eps)
	{
		chek++;
	}
	ReadWindow("input.bmp", -5, 15,-5,7.515);
	xyLine(0,0,(double)chek,10);
	
	SetColor(125,150,175);
	SetPoint(0,nevazka[0]);
	for(int i = 1; i < chek; i++)
	{
		Line2(i,modl(nevazka[i]));
	}
	WriteImage("output.bmp",B,G,R);
	
	fprintf(out,"Корни:\n");
	for(int i = 0; i < n ;i++)
	{
		fprintf(out,"x[%i] = %lf\n", i,y[i],chek);
	}
	fprintf(out,"Количество итераций: %d\n",chek);
	
	return 0;
}

void vvod()
{
	FILE *in = fopen("in.txt","rt");
	
	char s[40];
	
	fscanf(in,"%s", s);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0 ; j < 10 ; j++)
		{
			fscanf(in,"%lf", &matrix[i][j]);
		}
	}
	
	fscanf(in,"%s", s);fscanf(in,"%s", s);
	
	for(int i = 0; i < 10 ; i++)
	{
		fscanf(in,"%s", s);fscanf(in,"%lf", &f[i]);//свободные ко-ты
	}
	
	fscanf(in,"%s", s);fscanf(in,"%lf", &eps);
	fscanf(in,"%s", s);fscanf(in,"%s", s);
	
	for(int i = 0; i < 10 ; i++)
	{
		fscanf(in,"%lf", &y[i]);//начальные значения
		y_old[i] = y[i];
	}
	
}

double modl(double x)
{
	return x < 0 ? -x : x;
}

void on_console()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 11; j++)
		{
			printf("%.2lf\t", matrix[i][j]);
		}
		printf("\n");
	}
}

double find_root()
{
	for(int i = 0; i < n ;i++)
	{
		double yq = 0;
		for(int j = 0; j < i;j++)
		{
			yq += matrix[i][j]*y[j];
		}
		for(int j = i+1; j < n; j++)
		{
			yq += matrix[i][j]*y_old[j];
		}
		
		y_old[i] = y[i];
		y[i] = (f[i] - yq)/matrix[i][i]; //создам пременную для этого элемента
	}
	
	double max = 0;
	for(int i = 0; i < n;i++) //проверка, отбор наибольшей невязки
	{
		if(modl(Ay(i) - f[i]) > max)  max = modl(Ay(i) - f[i]);
	}
	
	nevazka[p] = max;
	p++;
	return max;
}

double sum(double masiv[])
{
	double sum = 0;
	for(int i = 0; i < n; i++)
	{
		sum += masiv[i];
	}
	
	return sum;
}

double Ay(int k)
{
	double left = 0;
	
	for(int i = 0; i < n; i++)
	{
		left += y[i]*matrix[k][i];
	}
	
	return left;
}
