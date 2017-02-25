#pragma once
#include "matrix.h"

const std::string MATR_A_NAME = "matr_a.txt";
const std::string MATR_B_NAME = "matr_b.txt";
const std::string RESULT_MATR_NAME = "result_matr.txt";
const int MATR_SIZE = 200;
const int NUM_THREADS = 1;
const int NUM_BLOCKS = 5;

// уможает две матрицы квадратные матрицы и помещает результат в new_b
void multiply_thread(cpc_elm, cpc_elm, const int &, const int &, buff * const, int, int);

void printing_params_and_time(const int&, const int&, const int&, const double&);

void writing_result_matrix(const std::string &, const int&, cpc_elm);

void killing_threads(std::vector<std::thread*> &);

void multiplying_matr(const int&, const int&, const int&,
	cpc_elm, cpc_elm, buff * const);