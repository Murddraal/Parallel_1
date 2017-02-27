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
#include <queue>
#include <chrono>

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

	buff(size_t);
	~buff();

	buff() = delete;	
};

struct th_data
{
	cpc_elm matr_a;
	cpc_elm matr_b;
	const size_t n;
	const size_t matr_size;
	buff * const result;
	const size_t ri;
	const size_t rj;

	th_data(cpc_elm matr_a,	cpc_elm matr_b,
		const size_t n,	const size_t matr_size,
		buff * const result, const size_t ri, const size_t rj);
	th_data();
};

class thread_pool
{
private:
	std::queue<th_data*> data_queue;
	std::vector<std::thread*> multiply;

public:
	void push(th_data*);
	th_data* pop();
	bool is_empty();
	thread_pool(size_t);
	thread_pool() = delete;
	void killing_threads();
	std::mutex tp_mutex;

};

elm* reading_matrix(const std::string &);

void write_matrix(size_t);