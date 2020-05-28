#include <iomanip>
#include <iostream>

using namespace std;

// width
#define w 8
// precision
#define p 4

void write_mas(double* m, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << setw(w) << setprecision(p) << m[i] << "| ";
	}
	cout << "\n";
}

void randomize(double* m, int size)
{
	for (int i = 0; i < size; i++)
	{
		m[i] = rand() % 5 / 1.;
	}
}

double** build_matrix(double* x, double* y, int size)
{
	double** matrix = new double*[size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new double[size]{0};

		for (int j = 0; j < i; j++)
		{
			double distance = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
			matrix[i][j] = distance;
			matrix[j][i] = distance;
		}
	}
	return matrix;
}

int* find_equals(double** matrix, int size, int& count)
{
	int* equals = new int[size];
	count = 0;
	for (int i = 1; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			for (int k = j + 1; k < size; k++)
			{
				if (j == k) continue;

				if (abs(matrix[i][j] - matrix[i][k]) < 0.00001)
				{
					//Это битовая магия
					//equals[count] = 0000000000000000kkkkkkkkjjjjjjjj
					equals[count++] = (i) + (j << 8);
					equals[count++] = (i) + (k << 8);
				}
			}
		}
	}
	return equals;
}

int main()
{
	setlocale(LC_ALL, "russian");
	srand(time(0));
	cout << "Автор: Никитина Дарья Сергеевна\n";

	double* x;
	double* y;

	int size;
	cout << "Введите количество точек: ";
	cin >> size;

	x = new double[size];
	randomize(x, size);
	y = new double[size];
	randomize(y, size);

	for (int i = 0; i < size; i++)
	{
		cout << setw(2) << i << "{ " << setw(w) << setprecision(p) << x[i] << "; " << setw(w) << setprecision(p) << y[i]
			<< " }\n";
	}

	double** matrix = build_matrix(x, y, size);
	for (int i = 0; i < size; ++i)
	{
		write_mas(matrix[i], size);
		for (int i = 0; i < size * (w + 2) - 1; i++)
		{
			cout << "-";
		}
		cout << "\n";
	}

	int count_equals;
	int* equals = find_equals(matrix, size, count_equals);

	cout << "Одинаковые расстояния между точками: \n";
	for (int i = 0; i < count_equals; i++)
	{
		//Это битовая магия
		//0xf - битовая маска 00000000000000000000000011111111
		//equals[i] & 0xf   = 000000000000000000000000jjjjjjjj
		//equals[i] >> 8    = 000000000000000000000000kkkkkkkk
		cout << "{ " << (equals[i] & 0xf) << "; " << (equals[i] >> 8) << " }\n";
	}

	system("pause");

	return 0;
}
