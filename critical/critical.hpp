#pragma once
#include "loger.hpp"
 
class Critical : public Loger
{
public:
	Critical(): Loger("Critical ") {}

};

Critical critical;

class Debug : public Loger
{
public:
	Debug() : Loger("Debug ") {}

};

Debug debug;