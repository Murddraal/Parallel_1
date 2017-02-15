#include "matrix.h"

std::string MATR_A_NAME = "matr_a.txt";
std::string MATR_B_NAME = "matr_b.txt";
int MATR_SIZE = 10;
int NUM_THREADS = 2;
int NUM_BLOCKS = 1;


void multiply_thread(const double *const matr_a, const double *const matr_b, const int &n, buff * const new_b)
{
	new_b->start();
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0, el = i*n + j; k < n; ++k)
			{
				new_b->data[el] += matr_a[k*n + j] * matr_b[i*n + k];
			}
		}
	}
}



void main(int argc, char **argv)
{
	/*if (argc < 3)
	{
		std::cout << "Write all arguments!\n";
		return;
	}*/
	write_matrix(MATR_SIZE);
	/*int num_threads = std::atoi(argv[1]);
	int num_blocks = std::atoi(argv[2]);*/


	double const *matrix_a = reading_matrix(MATR_A_NAME);
	double const *matrix_b = reading_matrix(MATR_B_NAME);
	
	std::vector<std::thread*> matr_threads;

	/*buff *new_b = new buff(MATR_SIZE);

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		matr_threads.push_back(new std::thread(multiply_thread, matrix_a, matrix_a, MATR_SIZE, new_b));		
	}

	for each (auto &thread in matr_threads)
	{
		thread->join();
	}*/

	double * const result_matr = new double[MATR_SIZE*MATR_SIZE];
	for (int i = 0; i < MATR_SIZE*MATR_SIZE; ++i)
		result_matr[i] = 0;

	

	for (int i = 0, dx = int(MATR_SIZE / NUM_BLOCKS); i < MATR_SIZE; i += dx)
	{
		for (int j = 0; j < MATR_SIZE; j += dx)
		{
			buff *b_buff = new buff(NUM_BLOCKS);
		
			for (int k = 0; k < MATR_SIZE; k += dx)
			{
				int  a_ind = i*MATR_SIZE + k;
				int  b_ind = k*MATR_SIZE + j;
				if (NUM_THREADS > matr_threads.size())
					matr_threads.push_back(new std::thread(multiply_thread, &matrix_a[a_ind], &matrix_b[b_ind], dx, b_buff));
				else
					for each (auto &thread in matr_threads)
					{
						thread->join();
					}
			}
			for each (auto &thread in matr_threads)
			{
				thread->join();
			}
			for (int ii = i; ii < i + dx; ++ii)
				for (int jj = j, b = ii*MATR_SIZE; jj < j + dx; ++jj)
					result_matr[b + jj] = b_buff->data[(ii-i)*dx + jj - j];

			delete b_buff;
		}
	}

	for (int i = 0; i < MATR_SIZE; ++i)
	{
		for (int j = 0, b = i*MATR_SIZE; j < MATR_SIZE; ++j)
		{
			std::cout << result_matr[b + j] << ' ';
		}
		std::cout << '\n';
	}
}