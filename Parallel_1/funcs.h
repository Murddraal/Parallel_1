#pragma once
#include "matrix.h"

const std::string MATR_A_NAME = "matr_a.txt";
const std::string MATR_B_NAME = "matr_b.txt";
const std::string RESULT_MATR_NAME = "result_matr.txt";
const int MATR_SIZE = 200;
const int NUM_THREADS = 1;
const int NUM_BLOCKS = 5;

// уможает две матрицы квадратные матрицы и помещает результат в new_b
void multiply_thread(const double *const, const double *const matr_b, const int &, buff * const);

void printing_params_and_time(const int&, const int&, const int&, const double&);

void writing_result_matrix(const std::string &, int, double * const);

void killing_threads(std::vector<std::thread*> &);

double* multiplying_matr(const int, const int, const int,
	const double * const, const double * const);