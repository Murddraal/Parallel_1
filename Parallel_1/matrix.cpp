#include "matrix.h"
#include "funcs.h"

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

th_data::th_data():matr_a(new elm), matr_b(new elm), n(0), matr_size(0), result(new mut_matr(0)), ri(0), rj(0)
{};