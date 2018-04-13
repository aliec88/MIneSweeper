#pragma once
inline double RandFloat()
{
	return rand()/(RAND_MAX+1.0);
}
inline double RandomClamped()
{
	return RandFloat()-RandFloat();
}
inline int RandInt(int a,int b)
{
	return rand()%(b-a)+a;
}
inline double Clamp(double number,double maxnumber)
{
	if (number>maxnumber)
	{
		return maxnumber;
	}
	if (number<-maxnumber)
	{
		return -maxnumber;
	}
	return number;
}
inline wstring ftos(double f)
{
	wstringstream s;
	s<<f;
	return s.str();	
}
