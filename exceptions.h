#pragma once
#include <exception>
using namespace std;

class StatNotFoundException : public exception
{
	virtual const char* what() const throw()
	{
		return "[SEVERE] The stat you requested for does not exist!";
	}
};

class ItemNotFoundException : public exception
{
	virtual const char* what() const throw()
	{
		return "[SEVERE] The item you requested for does not exist!";
	}
};
