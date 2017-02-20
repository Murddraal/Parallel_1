#include "matrix.h"
#include "funcs.h"

void main(int argc, char **argv)
{
	int matr_size = 0;
	int num_threads = 0;
	int num_blocks = 0;
	if (argc == 4)
	{
		matr_size = std::atoi(argv[1]);
		num_threads = std::atoi(argv[2]);
		num_blocks = std::atoi(argv[3]);
	}
	else
	{
		matr_size = MATR_SIZE;
		num_threads = NUM_THREADS;
		num_blocks = NUM_BLOCKS;
	}
	// генерация матриц
	write_matrix(matr_size);

	// считывание матриц
	double const *matr_a = reading_matrix(MATR_A_NAME);
	double const *matr_b = reading_matrix(MATR_B_NAME);

	std::clock_t start = std::clock();

	// Умножаем матрицы
	double * const result_matr = multiplying_matr(matr_size, num_blocks, num_threads, matr_a, matr_b);

	// Вычисляем затраченное время
	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	int * const test_matr = new int[matr_size*matr_size];
	for (int i = 0; i < matr_size*matr_size; ++i)
		test_matr[i] = 0;

	for (int i = 0; i < matr_size; ++i)
	{
		for (int j = 0; j < matr_size; ++j)
		{
			for (int k = 0, el = i*matr_size + j; k < matr_size; ++k)
			{
				int x = matr_a[i*matr_size + k] * matr_b[k*matr_size + j];
				test_matr[el] += x;
			}
		}
	}

	int summ = 0;
	for (int i = 0; i < matr_size * matr_size; ++i)
	{
		summ += test_matr[i] - result_matr[i];
	}

	std::cout << summ << '\n';

	// Выводим время и параметры программы на экран
	printing_params_and_time(matr_size, num_blocks, num_threads, time);

	// Запись результирующей матрицы в файл
	writing_result_matrix(RESULT_MATR_NAME, matr_size, result_matr);

	delete[] test_matr;
	
}

