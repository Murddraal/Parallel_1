#include "funcs.h"

void multiply_thread(thread_pool* tp)
{
	while (true)
	{
		auto data = new th_data();

		{
			std::unique_lock<std::mutex> lock(tp->tp_mutex);
			while (tp->is_empty())
			{
				tp->cond_var.wait(lock);
			}
			data = tp->pop();
		}		

		if (data->matr_size == 0)
			return;

		// умножение блоков
		auto b = new elm[(*data).n*(*data).n];
		for (size_t i = 0; i < (*data).n*(*data).n; ++i)
			b[i] = 0;

		for (size_t i = 0; i < (*data).n; ++i)
		{
			for (size_t j = 0; j < (*data).n; ++j)
			{
				for (size_t k = 0, el = i*(*data).n + j; k < (*data).n; ++k)
				{
					b[el] += (*data).matr_a[i*(*data).matr_size + k] * (*data).matr_b[k*(*data).matr_size + j];
				}
			}
		}

		// блокирование результирующей матрицы
		std::lock_guard<std::mutex> l((*data).result->mtx);
		for (size_t i = 0, ii = (*data).ri; i < (*data).n; ++i, ++ii)
			for (size_t j = 0, jj = (*data).rj; j < (*data).n; ++j, ++jj)
				(*data).result->data[ii*(*data).matr_size + jj] += b[i*(*data).n + j];

		delete[] b;
	}
}

void printing_params_and_time(const size_t& size, const size_t& blocks, const size_t& threads, const double& time)
{
	std::cout << "Size of matrix: " << size << 'x' << size << "\n";
	std::cout << "Number of blocks: " << blocks << 'x' << blocks << "\n";
	std::cout << "Number of threads: " << threads << "\n";
	std::cout << "Time: " << time << "\n";
}

void writing_result_matrix(const std::string & fname, const size_t& matr_size, cpc_elm matrix)
{
	std::ofstream fout(fname);
	for (size_t i = 0; i < matr_size; ++i)
	{
		for (size_t j = 0, b = i*matr_size; j < matr_size; ++j)
		{
			fout << matrix[b + j] << ' ';
		}
		fout << '\n';
	}
}

void multiplying_matr(const size_t& matr_size, const size_t& num_blocks, const size_t& num_threads,
	cpc_elm matr_a, cpc_elm matr_b, mut_matr * const result_matr)
{
	std::vector<std::thread*> matr_threads;

	const size_t block_width = size_t(matr_size / num_blocks);

	std::clock_t start = std::clock();

	thread_pool pool(num_threads);

	// шаг цикла - ширина блока.
	for (size_t i = 0, ib = 0; i < matr_size; i += block_width, ++ib)
	{
		for (size_t j = 0, jb = 0; j < matr_size; j += block_width, ++jb)
		{
			for (size_t k = 0; k < matr_size; k += block_width)
			{
				size_t  a_ind = i * matr_size + k;
				size_t  b_ind = k * matr_size + j;
				// добавление данных в очередь
				pool.push(new th_data(&matr_a[a_ind], &matr_b[b_ind], block_width, matr_size, result_matr, i, j));
			}
		}
	}

	pool.killing_threads();
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
}

pc_elm simply_mupliply(cpc_elm matr_a, cpc_elm matr_b, const size_t& matr_size)
{
	pc_elm test_matr = new elm[matr_size*matr_size];
	for (size_t i = 0; i < matr_size*matr_size; ++i)
		test_matr[i] = 0;

	for (size_t i = 0; i < matr_size; ++i)
	{
		for (size_t j = 0; j < matr_size; ++j)
		{
			for (size_t k = 0, el = i*matr_size + j; k < matr_size; ++k)
			{
				test_matr[el] += matr_a[i*matr_size + k] * matr_b[k*matr_size + j];
			}
		}
	}
	return test_matr;
}

elm test(cpc_elm matr_a, cpc_elm matr_b, const size_t& matr_size)
{
	elm summ = 0;
	for (size_t i = 0; i < matr_size * matr_size; ++i)
		summ += matr_a[i] - matr_b[i];

	return summ;
}

