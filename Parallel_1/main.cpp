#include "matrix.h"

std::string MATR_A_NAME = "matr_a.txt";
std::string MATR_B_NAME = "matr_b.txt";
int MATR_SIZE = 200;
int NUM_THREADS = 1;
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
				int x = matr_a[k*n + j] * matr_b[i*n + k];
				new_b->data[el] += x;
			}
		}
	}
}

void printing_results(const int& size, const int& blocks, const int& threads, const double& time)
{
	std::cout << "Size of matrix: " << size << 'x' << size << "\n";
	std::cout << "Number of blocks: " << blocks * blocks << "\n";
	std::cout << "Number of threads: " << threads << "\n";
	std::cout << "Time: " << time << "\n";
}

void main(int argc, char **argv)
{
	if (argc == 4)
	{
		MATR_SIZE = std::atoi(argv[1]);
		NUM_THREADS = std::atoi(argv[2]);
		NUM_BLOCKS = std::atoi(argv[3]);
	}
	// генерация матриц
	write_matrix(MATR_SIZE);

	double const *matrix_a = reading_matrix(MATR_A_NAME);
	double const *matrix_b = reading_matrix(MATR_B_NAME);
	
	std::vector<std::thread*> matr_threads;

	// инициализация итоговой матрицы
	double * const result_matr = new double[MATR_SIZE*MATR_SIZE];
	for (int i = 0; i < MATR_SIZE*MATR_SIZE; ++i)
		result_matr[i] = 0;	

	std::clock_t start = std::clock();

	// dx - ширина блока.
	// шаг цикла - ширина блока.
	for (int i = 0, dx = int(MATR_SIZE / NUM_BLOCKS); i < MATR_SIZE; i += dx)
	{
		for (int j = 0; j < MATR_SIZE; j += dx)
		{
			buff * const b_buff = new buff(dx);
		
			for (int k = 0; k < MATR_SIZE; k += dx)
			{
				int  a_ind = i*MATR_SIZE + k;
				int  b_ind = k*MATR_SIZE + j;
				// если кол-во текущих потоков меньше максимального, то добавляем в вектор ещё один
				// иначе, ждём завершения всех потоков, очищаем вектор и заполняем его заново 
				if (NUM_THREADS > matr_threads.size())
					matr_threads.push_back(new std::thread(multiply_thread, &matrix_a[a_ind], &matrix_b[b_ind], dx, b_buff));
				else
				{
					for each (auto thread in matr_threads)
					{
						thread->join();
					}
					matr_threads.clear();
					matr_threads.push_back(new std::thread(multiply_thread, &matrix_a[a_ind], &matrix_b[b_ind], dx, b_buff));
				}
			}

			for each (auto thread in matr_threads)
			{
				thread->join();
			}
			matr_threads.clear();

			for (int ii = i; ii < i + dx; ++ii)
			{
				for (int jj = j, b = ii*MATR_SIZE; jj < j + dx; ++jj)
				{
					int x = b_buff->data[(ii - i)*dx + jj - j];
					result_matr[b + jj] = x;
				}
			}			

			delete b_buff;
		}
	}

	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	printing_results(MATR_SIZE, NUM_BLOCKS, NUM_THREADS, time);

	std::ofstream fout("result_matr.txt");
	for (int i = 0; i < MATR_SIZE; ++i)
	{
		for (int j = 0, b = i*MATR_SIZE; j < MATR_SIZE; ++j)
		{
			fout << result_matr[b + j] << ' ';
		}
		fout << '\n';
	}
}