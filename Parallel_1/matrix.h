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
class mut_matr
{
private:	
public:
	std::mutex mtx;
	pc_elm data;

	mut_matr(size_t);
	~mut_matr();

	mut_matr() = delete;	
};

// содержит данные, необходимые для умножения двух квадратных матриц между собой
struct th_data
{
	// указатели на начало блоков в матрицах а/б
	cpc_elm matr_a;
	cpc_elm matr_b;
	//размер блока и матрицы
	const size_t n;
	const size_t matr_size;
	// структура, куда записывается результат умножения
	mut_matr * const result;
	// индексы текущего блока результирующей матрицы
	const size_t ri;
	const size_t rj;

	th_data(cpc_elm matr_a,	cpc_elm matr_b,
		const size_t n,	const size_t matr_size,
		mut_matr * const result, const size_t ri, const size_t rj);
	th_data();
};

// пул потоков
class thread_pool
{
private:
	// очередь с данными, которые считывают потоки для умножения матриц(указатели на начала блоков и их размеры)
	std::queue<th_data*> data_queue;
	// вектор потоков
	std::vector<std::thread*> multiply;
	size_t threads_amount;
	bool is_done = false;

public:
	void push(th_data*);
	th_data* pop();
	bool is_empty();
	thread_pool(size_t);
	thread_pool() = delete;
	~thread_pool();
	void killing_threads();

	std::mutex tp_mutex;
	std::condition_variable cond_var;

};

// чтение матрицы из файла
elm* reading_matrix(const std::string &);

// запись матрицы в файл
void write_matrix(size_t);