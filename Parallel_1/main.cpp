#include "matrix.h"

std::string MATR_A_NAME = "matr_a.txt";
std::string MATR_B_NAME = "matr_b.txt";
int MATR_SIZE = 5;


void multiply_thread(const double *const const matr_a, const double *const matr_b, const int &n, buff * const new_b)
{
	new_b->start();
	for (int i = 0; i < n*n; ++i)
		new_b->data[i] = 0;
	
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
	if (argc < 3)
	{
		std::cout << "Write all arguments!\n";
		return;
	}
	write_matrix(MATR_SIZE);
	int num_threads = std::atoi(argv[1]);
	int num_blocks = std::atoi(argv[2]);


	double const *matrix_a = reading_matrix(MATR_A_NAME);
	double const *matrix_b = reading_matrix(MATR_B_NAME);
	
	std::vector<std::thread*> matr_threads;

	buff *new_b = new buff(MATR_SIZE);

	for (int i = 0; i < 2; ++i)
	{
		matr_threads.push_back(new std::thread(multiply_thread, matrix_a, matrix_b, MATR_SIZE, new_b));
		
	}

	for each (auto &thread in matr_threads)
	{
		thread->join();
	}

	for (int i = 0; i < MATR_SIZE; ++i)
	{
		for (int j = 0, b = i*MATR_SIZE; j < MATR_SIZE; ++j)
		{
			std::cout << new_b->data[b + j] << ' ';
		}
		std::cout << '\n';
	}
}