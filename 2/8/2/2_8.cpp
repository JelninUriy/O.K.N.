#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cmath>
#include <stdio.h>

using namespace std;
int answ=0;
double* Gays(int** matrix, double* f, const int size)
 {
	// первый индекс - строка, второй - столбец
	for (int i = 0; i < size - 1; ++i) 
	{
		// сперва найдем самый маленький по модули элемент в столбце, а остальные должны на него делиться
		int min = 0;
		int index = i;
		for (int k = i; k < size; ++k) 
		{
			if ((matrix[k][i] != 0) && ((min == 0) || (abs(matrix[k][i]) < min))) 
			{
				index = k;
				min = abs(matrix[k][i]);
			}
		}
		if (min == 0) 
		{
			// если дальше в столбце только нули
			continue;
		}
		// swap
		int* temp = matrix[i];
		matrix[i] = matrix[index];
		matrix[index] = temp;
		double tempF = f[i];
		f[i] = f[index];
		f[index] = tempF;

		for (int j = i + 1; j < size; ++j) 
		{
			if (matrix[j][i] % matrix[i][i] != 0) {
				
				// если не делится на цело
				for (int k = i; k < size; ++k) 
				{
					matrix[j][k] *= matrix[i][i];
				}
				f[j] *= matrix[i][i];
			}
			int count = matrix[j][i] / matrix[i][i];
			for (int k = i; k < size; ++k) 
			{
				matrix[j][k] -= (matrix[i][k] * count);
			}
			f[j] -= (f[i] * count);
		}
	}

	double* result = new double[size];
	// решене с треугольной матрицей
	for (int i = size - 1; i >= 0; --i) 
	{
		if ((matrix[i][i] == 0) && (f[i] != 0)) 
		{
			answ=1;
			return result;
		}
		for (int j = i - 1; j >= 0; --j) 
		{
			// зануляем весь столбец над [i][i]
			if (f[i] != 0) {
				f[j] -= (f[i] * ((double)matrix[j][i] / (double)matrix[i][i]));
			}
			matrix[j][i] = 0;
		}
	}
	for (int i = 0; i < size; ++i) 
	{
		if (matrix[i][i] != 0) 
		{
			result[i] = f[i] / matrix[i][i];
		}
		else {
			answ=2;
			result[i] = 0;
		}
	}
	return result;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	ifstream input;
	input.open("input.txt");
	// reading data from file
	// чтение из файда
	string tempWord;

	int size = 0;
	input >> tempWord;
	input >> tempWord;
	input >> tempWord;
	input >> tempWord;
	input >> size;

	input >> tempWord;
	// запись матрицы
	int** matrix = new int*[size];
	for (int i = 0; i < size; ++i) 
	{
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j) 
		{
			input >> matrix[i][j];
		}
	}

	input >> tempWord;
	// вектор правой части
	double* f = new double[size];
	for (int i = 0; i < size; ++i) 
	{
		input >> f[i];
	}
	input.close();

	double* answer = Gays(matrix, f, size);
	FILE *out = fopen("output.txt","w");
	if(answ==0||answ==2){
	fprintf(out,"Gays: \n\n\n");
	int raz2 = 0;	
	for (int i = 0; i < size; ++i)
	{
		fprintf(out,"\t x(%d) = %lf",i,answer[i]);raz2++;
		if(raz2==2 || raz2==4||raz2==6||raz2==8){
			fprintf(out,"\n");
		}
	}
	fprintf(out,"\n\n\n");
	
	fprintf(out,"\nНевязка:\n");
	
	int raz =1;
	for (int i = 0; i < size; ++i)
	{
		if(raz==1){
		
		fprintf(out,"f(%d): %lf\n",i,f[i] - matrix[i][i] * answer[i]);
		raz=2;
	}
	}
	if(answ==2)
	{
		fprintf(out,"Решений ,бесконечно много,вот одно из них");
	}
}
if(answ==1)
{
	fprintf(out,"Решений нет");
}


	return 0;
}
