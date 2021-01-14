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

			//ɾ��������־
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

//���ͱ���
using PEndlFunction = Loger& (*)(Loger&);

// ��ʽ��������������� << ,ע��,���ο���������void,��Ϊ���û�˻��õ�Loger������
Loger& operator << (Loger& loger, PEndlFunction pfunc)
{
	pfunc(loger);  // ��·:���������� pfunc����loger Ϊ���
	return loger;  // Ҳ����·�����׻�C++�ϲᣨC++���Ի�����OO��
}


//Ŀ��,��Ϊ�˱�����߳�,cout�����д�ӡ���Ƕ����,һ���Ե�flush,��ʵ�о����Ǻܱ�Ҫ
//��Ϊ,ԭ����û�������뵽�ļ���,��������������ļ�,��ô��������Ӧ��ֻ��һ��Logerʵ����,�������ܱ�֤��ĳlog.txt��ռ
Loger& Endl(Loger& loger)
{
	loger.flush_buf(); 
	return loger;
}

/*
ע��,���һ�� << Endl;�ǵ���Loger& operator << (Loger& loger, PEndlFunction pfunc)����
�ڴ�֮ǰ�ǵĶ�����Loger�ĳ�Ա����
template<typename T>
Loger& operator<< (const T& t)
*/



