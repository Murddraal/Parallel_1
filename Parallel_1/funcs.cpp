#include "funcs.h"

void multiply_thread(const double *const matr_a, const double *const matr_b, const int &n, buff * const new_b)
{
	// блокирование мьютекса
	new_b->start();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0, el = i*n + j; k < n; ++k)
			{
				int x = matr_a[k*n + j] * matr_b[i*n + k];
				new_b->data[el] += x;
			}
		}
	}
}

void printing_params_and_time(const int& size, const int& blocks, const int& threads, const double& time)
{
	std::cout << "Size of matrix: " << size << 'x' << size << "\n";
	std::cout << "Number of blocks: " << blocks * blocks << "\n";
	std::cout << "Number of threads: " << threads << "\n";
	std::cout << "Time: " << time << "\n";
}

void writing_result_matrix(const std::string & fname, int matr_size, double * const matrix)
{
	std::ofstream fout(fname);
	for (int i = 0; i < matr_size; ++i)
	{
		for (int j = 0, b = i*matr_size; j < matr_size; ++j)
		{
			fout << matrix[b + j] << ' ';
		}
		fout << '\n';
	}
}

void killing_threads(std::vector<std::thread*> &threads)
{
	for each (auto thread in threads)
	{
		thread->join();
	}
	threads.clear();
}

double* multiplying_matr(const int matr_size, const int num_blocks, const int num_threads,
	const double * const matr_a, const double * const matr_b)
{
	std::vector<std::thread*> matr_threads;

	// инициализация итоговой матрицы
	double * const result_matr = new double[matr_size*matr_size];
	for (int i = 0; i < matr_size*matr_size; ++i)
		result_matr[i] = 0;

	const int block_width = int(matr_size / num_blocks);

	// шаг цикла - ширина блока.
	for (int i = 0; i < matr_size; i += block_width)
	{
		for (int j = 0; j < matr_size; j += block_width)
		{
			buff * const b_buff = new buff(block_width);

			for (int k = 0; k < matr_size; k += block_width)
			{
				int  a_ind = i * matr_size + k;
				int  b_ind = k * matr_size + j;
				// если кол-во текущих потоков меньше максимального, то добавляем в вектор ещё один
				// иначе, ждём завершения всех потоков, очищаем вектор и заполняем его заново 
				if (num_threads > matr_threads.size())
					matr_threads.push_back(new std::thread(multiply_thread, &matr_a[a_ind], &matr_b[b_ind], block_width, b_buff));
				else
				{
					killing_threads(matr_threads);
					matr_threads.push_back(new std::thread(multiply_thread, &matr_a[a_ind], &matr_b[b_ind], block_width, b_buff));
				}
			}

			killing_threads(matr_threads);
			// запись вычисленного блока из буфера
			// в нужное место результирующей матрицы
			for (int ii = i; ii < i + block_width; ++ii)
			{
				for (int jj = j, b = ii*matr_size; jj < j + block_width; ++jj)
				{
					result_matr[b + jj] = b_buff->data[(ii - i) * block_width + (jj - j)];
				}
			}

			delete b_buff;
		}
	}

	return result_matr;
}