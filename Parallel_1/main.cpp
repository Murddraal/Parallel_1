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

	// Выводим время и параметры программы на экран
	printing_params_and_time(matr_size, num_blocks, num_threads, time);

	// Запись результирующей матрицы в файл
	writing_result_matrix(RESULT_MATR_NAME, matr_size, result_matr);

	
}

