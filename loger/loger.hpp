#pragma once
#include <iostream>
#include <sstream>
#include "utils.h"
#include <fstream>

#define completed_prefix stream_buf << prefix << GetTimeStr() << " "
#define LOG_PATH "./log/"

struct Loger
{
public:
	Loger(std::string _prefix = "Log      ") { prefix = _prefix;}

	~Loger() 
	{
		if (out_file.is_open())
			out_file.close();
	}

	template<typename T>
	Loger& operator<< (const T& t)
	{
		if (stream_buf.str().empty()) 
			completed_prefix;
		check_touch_file();		
		stream_buf << t;		
		return *this;
	}

	void check_touch_file()
	{
		std::string current = GetTimeStr_Day();
		//std::string current = GetTimeStr_Hour();
		static std::string pre = "";
		if (pre != current)
		{
			if (out_file.is_open())
				out_file.close();
			std::string temp = current;			
			temp.append(".txt");
			temp.insert(0, string(LOG_PATH));
			out_file.open(temp, std::ios::app);
			pre = current;

			//删除超期日志
			static uint16_t count = 1;
			if (0 == count % 7)
				del_overdue_file(string(LOG_PATH), 60 * 60 * 24 * 7);
			count++;
		}
	}

	void flush_buf()
	{
		stream_buf << std::endl;
		std::cout << stream_buf.str();
		if (out_file.is_open())
			out_file << stream_buf.str();			
		stream_buf.str("");
		stream_buf.clear();
	}

public:
	std::string prefix = "Log      ";

private:
	static std::stringstream stream_buf;
	static std::ofstream out_file;
} loger;

std::stringstream Loger::stream_buf;
std::ofstream Loger::out_file;

//类型别名
using PEndlFunction = Loger& (*)(Loger&);

// 显式重载输出流操作符 << ,注意,出参可以声明成void,因为最后没人会用到Loger对象了
Loger& operator << (Loger& loger, PEndlFunction pfunc)
{
	pfunc(loger);  // 套路:反过来调用 pfunc，以loger 为入参
	return loger;  // 也是套路，见白话C++上册（C++语言基础与OO）
}


//目的,是为了避免多线程,cout过程中打印不是独享的,一次性地flush,其实感觉不是很必要
//因为,原意是没将流导入到文件中,后面升级输出到文件,那么整个工程应该只有一个Loger实例在,这样才能保证对某log.txt独占
Loger& Endl(Loger& loger)
{
	loger.flush_buf(); 
	return loger;
}

/*
注意,最后一句 << Endl;是调用Loger& operator << (Loger& loger, PEndlFunction pfunc)函数
在此之前那的都调用Loger的成员函数
template<typename T>
Loger& operator<< (const T& t)
*/



