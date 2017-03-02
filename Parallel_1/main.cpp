#include "matrix.h"
#include "funcs.h"

void main(int argc, char **argv)
{
	elm matr_size = 0;
	elm num_threads = 0;
	elm num_blocks = 0;
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
	pc_elm matr_a = reading_matrix(MATR_A_NAME);
	pc_elm matr_b = reading_matrix(MATR_B_NAME);

	std::clock_t start = std::clock();

	// Умножаем матрицы
	auto result_matr = new mut_matr(matr_size);
	multiplying_matr(matr_size, num_blocks, num_threads, matr_a, matr_b, result_matr);

	// Вычисляем затраченное время
	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	// Выводим время и параметры программы на экран
	printing_params_and_time(matr_size, num_blocks, num_threads, time);

	// Запись результирующей матрицы в файл
	writing_result_matrix(RESULT_MATR_NAME, matr_size, result_matr->data);

	// Тестирование умножения
	pc_elm test_matr = simply_mupliply(matr_a, matr_b, matr_size);

	auto summ = test(test_matr, result_matr->data, matr_size);

	std::cout << "Test: " << summ << '\n';


	delete[] test_matr;
	delete[] matr_a;
	delete[] matr_b;
	
}

