#pragma once
#include <string>
using std::string;

//precision seconds
time_t GetTimeStamp();

//precision seconds
std::string GetTimeStr();

//precision hour
std::string GetTimeStr_Hour();

//precision days
std::string GetTimeStr_Day();

//
uint64_t file_timestamp(string _file);

/*
  del some file in the specify directory which is overdue
  dir like this ./xx/
*/
int del_overdue_file(string file_path, uint64_t interval);

//singleton
template<typename T>
struct singleton
{
	T init(T _in = nullptr)
	{ 
		if (nullptr == _in)
			return p_instance;
		else
		{
			p_instance = &_in;
			return;
		}
		
	}
	static T* p_instance;
};

template<typename T>
T* singleton<T>::p_instance = nullptr;

//using 