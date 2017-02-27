#include "matrix.h"
#include "funcs.h"

//��������� ���� ������ ����
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

// ������������ ������ �� ������������
elm test(cpc_elm matr_a, cpc_elm matr_b, const size_t& matr_size)
{
	elm summ = 0;
	for (size_t i = 0; i < matr_size * matr_size; ++i)
	{
		summ += matr_a[i] - matr_b[i];
	}
	return summ;
}

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
	// ��������� ������
	write_matrix(matr_size);

	// ���������� ������
	pc_elm matr_a = reading_matrix(MATR_A_NAME);
	pc_elm matr_b = reading_matrix(MATR_B_NAME);

	std::clock_t start = std::clock();

	// �������� �������
	auto result_matr = new mut_matr(matr_size);
	multiplying_matr(matr_size, num_blocks, num_threads, matr_a, matr_b, result_matr);

	// ��������� ����������� �����
	double time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	// ������� ����� � ��������� ��������� �� �����
	printing_params_and_time(matr_size, num_blocks, num_threads, time);

	// ������ �������������� ������� � ����
	writing_result_matrix(RESULT_MATR_NAME, matr_size, result_matr->data);

	// ������������ ���������
	pc_elm test_matr = simply_mupliply(matr_a, matr_b, matr_size);

	auto summ = test(test_matr, result_matr->data, matr_size);

	std::cout << "Test: " << summ << '\n';


	delete[] test_matr;
	delete matr_a;
	delete matr_b;
	
}

