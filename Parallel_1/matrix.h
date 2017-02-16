#pragma once
#include <ctime>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string>
// говнокод: 
// структура данных, в которую различные потоки могут складывать информацию
// без использования start всё сломается
class buff
{
private:
	std::mutex buff_mutex;
public:
	buff(int n) : data(new double[n*n])
	{
		for (int i = 0; i < n*n; ++i)
			data[i] = 0;
	}

	buff() = delete;

	double * const data;

	void start()
	{
		std::lock_guard<std::mutex> l(buff_mutex);
	}
};

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
