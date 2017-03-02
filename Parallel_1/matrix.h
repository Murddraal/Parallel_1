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

// ��������� ������, � ������� ��������� ������ ����� ���������� ����������
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

// �������� ������, ����������� ��� ��������� ���� ���������� ������ ����� �����
struct th_data
{
	// ��������� �� ������ ������ � �������� �/�
	cpc_elm matr_a;
	cpc_elm matr_b;
	//������ ����� � �������
	const size_t n;
	const size_t matr_size;
	// ���������, ���� ������������ ��������� ���������
	mut_matr * const result;
	// ������� �������� ����� �������������� �������
	const size_t ri;
	const size_t rj;

	th_data(cpc_elm matr_a,	cpc_elm matr_b,
		const size_t n,	const size_t matr_size,
		mut_matr * const result, const size_t ri, const size_t rj);
	th_data();
};

// ������ ������� �� �����
elm* reading_matrix(const std::string &);

// ������ ������� � ����
void write_matrix(size_t);

void printing_params_and_time(const size_t& size, const size_t& blocks, const size_t& threads, const double& time);

void writing_result_matrix(const std::string & fname, const size_t& matr_size, cpc_elm matrix);