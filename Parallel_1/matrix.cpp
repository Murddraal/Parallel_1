#include "matrix.h"

const double* reading_matrix(const std::string &filename)
{
	std::ifstream fin(filename);

	std::string buf = "";
	std::getline(fin, buf);
	int size = std::stoi(buf);

	double *matrix = new double[size * size];
	int i = 0;
	while (fin >> matrix[i++])
		true;

	return matrix;
}

void write_matrix(int size)
{
	srand(time(NULL));
	std::ofstream fout_a("matr_a.txt");
	std::ofstream fout_b("matr_b.txt");

	fout_a << size << "\n";
	fout_b << size << "\n";

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			fout_a << 3 << " ";//rand() % 10 + 1 << " ";
			if (i == j)
				fout_b << 3 << " ";
			else
				fout_b << 0 << " ";
		}
		fout_a << "\n";
		fout_b << "\n";
	}

}

void buff::start()
{
	std::lock_guard<std::mutex> l(buff_mutex);
}

buff::buff(int n) : data(new double[n*n])
{
	for (int i = 0; i < n*n; ++i)
		data[i] = 0;
}