#include "matrix.h"
#include "funcs.h"

elm* reading_matrix(const std::string &filename)
{
	std::ifstream fin(filename);

	std::string buf = "";
	std::getline(fin, buf);
	size_t size = std::stoi(buf);

	elm *matrix = new elm[size * size];
	size_t i = 0;
	while (fin >> matrix[i++])
		true;

	return matrix;
}

void write_matrix(size_t size)
{
	srand(time(NULL));
	std::ofstream fout_a("matr_a.txt");
	std::ofstream fout_b("matr_b.txt");

	fout_a << size << "\n";
	fout_b << size << "\n";

	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			fout_a << rand() % 10 + 1 << " ";
			fout_b << rand() % 10 + 1 << " ";
		}
		fout_a << "\n";
		fout_b << "\n";
	}

}

mut_matr::mut_matr(size_t n) : data(new elm[n*n])
{
	for (size_t i = 0; i < n*n; ++i)
		data[i] = 0;
}

mut_matr::~mut_matr()
{
	delete[] data;
}

th_data::th_data(cpc_elm matr_a_, cpc_elm matr_b_,
	const size_t n_, const size_t matr_size_,
	mut_matr * const result_,
	const size_t ri_,
	const size_t rj_) :matr_a(matr_a_), matr_b(matr_b_), n(n_), matr_size(matr_size_), result(result_), ri(ri_), rj(rj_)
{};

void thread_pool::push(th_data* data)
{
	data_queue.push(data);
	if(multiply.size() < threads_amount)
		multiply.push_back(new std::thread(multiply_thread, this));
}

th_data* thread_pool::pop()
{
	auto p = data_queue.front();
	data_queue.pop();
	return p;
}

bool thread_pool::is_empty()
{
	return data_queue.empty();
}

thread_pool::thread_pool(size_t num_threads)
{
	/*for (size_t i = 0; i < num_threads; ++i)
		multiply.push_back(new std::thread(multiply_thread, this));*/
	threads_amount = num_threads;
}

void thread_pool::killing_threads()
{
	for each (auto thread in multiply)
	{
		if (thread->joinable())
			thread->join();
	}
	multiply.clear();
}

th_data::th_data():matr_a(new elm), matr_b(new elm), n(0), matr_size(0), result(new mut_matr(0)), ri(0), rj(0)
{};