#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>

using std::cout;
using std::endl;

time_t GetTimeStamp()
{
	time_t t = time(NULL);		//时间戳
	return t;
}

std::string GetTimeStr()
{	
#ifdef _CRT_SECURE_NO_WARNINGS
	time_t t = time(NULL);
	tm* ptm = localtime(&t);	
#else
	tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);
	tm* ptm = &t;		
#endif
	std::string time = std::to_string(ptm->tm_year + 1900) + "-" + std::to_string(ptm->tm_mon + 1) + "-" + std::to_string(ptm->tm_mday) \
		+ "-" + std::to_string(ptm->tm_hour) + "-" + std::to_string(ptm->tm_min) + "-" + std::to_string(ptm->tm_sec);
	return time;

}

std::string GetTimeStr_Hour()
{
#ifdef _CRT_SECURE_NO_WARNINGS
	time_t t = time(NULL);
	tm* ptm = localtime(&t);
#else
	tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);
	tm* ptm = &t;
#endif
	std::string time = std::to_string(ptm->tm_year + 1900) + "-" + std::to_string(ptm->tm_mon + 1) + "-" + std::to_string(ptm->tm_mday) \
		+ "-" + std::to_string(ptm->tm_hour);
	return time;
}


std::string GetTimeStr_Day()
{
#ifdef _CRT_SECURE_NO_WARNINGS
	time_t t = time(NULL);
	tm* ptm = localtime(&t);	
#else
	tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);
	tm* ptm = &t;
#endif
	std::string time = std::to_string(ptm->tm_year + 1900) + "-" + std::to_string(ptm->tm_mon + 1) + "-" + std::to_string(ptm->tm_mday);
	return time;
}

uint64_t file_timestamp(std::string _file)
{	
	struct _stat buf;
	int result = _stat(_file.c_str(), &buf);
	if (0 == result)
		return buf.st_mtime;	
	return 0;
}

int del_overdue_file(string file_path, uint64_t interval)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(file_path.c_str())) == NULL)
	{
		perror("open dir error");
		return -1;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] == '.')// 跳过目录('.', '..')
			continue;
		string  temp = dirp->d_name;
		temp.insert(0, file_path);
		uint64_t timestamp = (uint64_t)file_timestamp(dirp->d_name);
		if (0 == file_timestamp)
			return -1;
		if (interval < (GetTimeStamp() - timestamp))
		{			
			int flag = remove(temp.c_str());
			if (0 != flag)
				perror("remove log failed ");
		}
	}
	closedir(dp);
	return 0;
}