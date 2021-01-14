//#include "test.hpp"
//int main(int argc, char* argv[])
//{	
//
//	//©иж╠╫с
//	cout << "Are you ok" << ok << "haode" << endl;
//	//cout << "Are you ok" << (ostream& (*)(ostream& os))ok << "haode";
//	return 0;
//}

#include "loger.hpp"
#include "./critical/critical.hpp"
#include <thread>
int main(int argc, char* argv[])
{
	while (1)
	{
		loger << "hello world." << Endl;
		critical << "hello kkkkkk." << Endl;
		critical << "hello jjjjjj." << Endl;
		critical << "hello ffffff." << Endl;
		loger << "hello world.111" << Endl;
		loger << "hello world.112" << Endl;
		loger << "hello world.333" << Endl;
		debug << "im debug 1" << Endl;
		debug << "im debug 2" << Endl;
		debug << "im debug 3" << Endl;
		std::this_thread::sleep_for(std::chrono::seconds(20));
	}	
	return 0;
}