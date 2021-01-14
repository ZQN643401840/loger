#pragma once
#include "loger.hpp"
 
struct Critical : public Loger
{
public:
	Critical(): Loger("Critical ") {}

}critical;


struct Debug : public Loger
{
public:
	Debug() : Loger("Debug ") {}

}debug;

