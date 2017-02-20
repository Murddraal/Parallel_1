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

// ��������� ������, � ������� ��������� ������ ����� ���������� ����������
class buff
{
private:
	
public:
	std::mutex buff_mutex;
	double * const data;

	buff(int);
	~buff();

	buff() = delete;
	// ��������� ��������
	void start();
	
};

const double* reading_matrix(const std::string &);

void write_matrix(int);