#include "funcs.h"

void multiply_thread(cpc_elm matr_a, cpc_elm matr_b, const int &n, const int &matr_size, buff * const result, const int ri, const int rj)
{
	int* b = new int[n*n];
	for (int i = 0; i < n*n; ++i)
		b[i] = 0;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0, el = i*n + j; k < n; ++k)
			{
				b[el] += matr_a[i*matr_size + k] * matr_b[k*matr_size + j];
			}
		}
	}
	// ������������ ��������
	std::lock_guard<std::mutex> l(result->buff_mutex);
	for (int i = 0, ii = ri; i < n; ++i, ++ii)
		for(int j = 0, jj = rj; j< n; ++j, ++jj)
		result->data[ii*matr_size + jj] += b[i*n +j];
	delete[] b;
}

void printing_params_and_time(const int& size, const int& blocks, const int& threads, const double& time)
{
	std::cout << "Size of matrix: " << size << 'x' << size << "\n";
	std::cout << "Number of blocks: " << blocks << 'x' << blocks << "\n";
	std::cout << "Number of threads: " << threads << "\n";
	std::cout << "Time: " << time << "\n";
}

void writing_result_matrix(const std::string & fname, const int& matr_size, cpc_elm matrix)
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
		if(thread->joinable())
			thread->join();
	}
	threads.clear();
}

void multiplying_matr(const int& matr_size, const int& num_blocks, const int& num_threads,
	cpc_elm matr_a, cpc_elm matr_b, buff * const result_matr)
{
	std::vector<std::thread*> matr_threads;

	const int block_width = int(matr_size / num_blocks);

	// ��� ����� - ������ �����.
	for (int i = 0, ib = 0; i < matr_size; i += block_width, ++ib)
	{
		for (int j = 0, jb = 0; j < matr_size; j += block_width, ++jb)
		{
			for (int k = 0; k < matr_size; k += block_width)
			{
				int  a_ind = i * matr_size + k;
				int  b_ind = k * matr_size + j;
				// ���� ���-�� ������� ������� ������ �������������, �� ��������� � ������ ��� ����
				// �����, ��� ���������� ���� �������, ������� ������ � ��������� ��� ������ 
				if (num_threads > matr_threads.size())
					matr_threads.push_back(new std::thread(multiply_thread, &matr_a[a_ind], &matr_b[b_ind], block_width, matr_size, result_matr, i, j));
				else
				{
					killing_threads(matr_threads);
					matr_threads.push_back(new std::thread(multiply_thread, &matr_a[a_ind], &matr_b[b_ind], block_width, matr_size, result_matr, i, j));
				}
			}
		}
	}

	killing_threads(matr_threads);
}