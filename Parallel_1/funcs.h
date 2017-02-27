#pragma once
#include "matrix.h"

const std::string MATR_A_NAME = "matr_a.txt";
const std::string MATR_B_NAME = "matr_b.txt";
const std::string RESULT_MATR_NAME = "result_matr.txt";
const size_t MATR_SIZE = 200;
const size_t NUM_THREADS = 1;
const size_t NUM_BLOCKS = 5;

// уможает две матрицы квадратные матрицы и помещает результат в new_b
void multiply_thread(thread_pool*);

void printing_params_and_time(const size_t&, const size_t&, const size_t&, const double&);

void writing_result_matrix(const std::string &, const size_t&, cpc_elm);

void killing_threads(std::vector<std::thread*> &);

void multiplying_matr(const size_t&, const size_t&, const size_t&,
	cpc_elm, cpc_elm, buff * const);