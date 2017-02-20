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

// структура данных, в которую различные потоки могут складывать информацию
class buff
{
private:
	
public:
	std::mutex buff_mutex;
	double * const data;

	buff(int);
	~buff();

	buff() = delete;
	// ¬ключение мьютекса
	void start();
	
};

const double* reading_matrix(const std::string &);

void write_matrix(int);