#pragma once
#include "matrix.h"

const std::string MATR_A_NAME = "matr_a.txt";
const std::string MATR_B_NAME = "matr_b.txt";
const std::string RESULT_MATR_NAME = "result_matr.txt";
const size_t MATR_SIZE = 200;
const size_t NUM_THREADS = 1;
const size_t NUM_BLOCKS = 5;

// уможает два блока матриц
void multiply_thread(thread_pool*);

// выводит в консоль параметры, с которой была запущено программа, и время её выполненя
void printing_params_and_time(const size_t&, const size_t&, const size_t&, const double&);

// записывает результирующую матрицу в файл
void writing_result_matrix(const std::string &, const size_t&, cpc_elm);

// умножение матриц с делением на блоки и потоки
void multiplying_matr(const size_t&, const size_t&, const size_t&,
	cpc_elm, cpc_elm, mut_matr * const);

// тестирование матриц на идентичность
elm test(cpc_elm, cpc_elm, const size_t&);

//умножение двух матриц влоб
pc_elm simply_mupliply(cpc_elm, cpc_elm, const size_t&);