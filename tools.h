#pragma once
#include <sstream>
inline int RandInt(int a,int b)
{
	return rand()%(b-a+1)+a;
}
inline double RandFloat()
{
	return rand()/(RAND_MAX+1.0);
}
inline double RanddomClamped()
{
	return RandFloat()-RandFloat();
}
inline void Clamp(double& arg,double min,double max)
{
	if (arg<min)
	{
		arg=min;
	}
	if (arg>max)
	{
		arg=max;
	}

}
inline double Sigmoid(double activation,double response)
{
	return 1/(1+exp(-activation/response));
}
inline wstring ftos(double num)
{
	wstringstream s;
	s<<num;
	return s.str();
}
inline wstring itos(int num)
{
	wstringstream s;
	s<<num;
	return s.str();
}
	 
