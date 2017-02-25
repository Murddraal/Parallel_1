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

typedef int elm;
typedef const elm * const cpc_elm;
typedef elm * const pc_elm;

// структура данных, в которую различные потоки могут складывать информацию
class buff
{
private:
	
public:
	std::mutex buff_mutex;
	pc_elm data;

	buff(int);
	~buff();

	buff() = delete;	
};

elm* reading_matrix(const std::string &);

void write_matrix(int);