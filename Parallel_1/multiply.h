#pragma once
#include "funcs.h"
#include "thread_pool.h"
#include "task.h"

void multiplying_matr(const size_t& matr_size, const size_t& num_blocks, const size_t& num_threads,
	cpc_elm matr_a, cpc_elm matr_b, mut_matr * const result_matr);

pc_elm simply_mupliply(cpc_elm matr_a, cpc_elm matr_b, const size_t& matr_size);

elm test(cpc_elm matr_a, cpc_elm matr_b, const size_t& matr_size);