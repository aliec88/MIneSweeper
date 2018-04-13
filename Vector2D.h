#pragma once
struct SPoint
{
	double x,y;
	SPoint(double a,double b)
	{
		x=a;
		y=b;
	}
	SPoint()
	{
		x=0;
		y=0;
	}
};
struct SVector2D
{
	double x,y;
	SVector2D(double a,double b)
	{
		x=a;
		y=b;
	}
	SVector2D()
	{
		x=0;
		y=0;
	}
	SVector2D& operator+=(const SVector2D& right)
	{
		this->x+=right.x;
		this->y+=right.y;
		return *this;
	}
	SVector2D& operator-=(const SVector2D& right)
	{
		this->x-=right.x;
		this->y-=right.y;
		return *this;
	}
	SVector2D& operator-(const SVector2D& right)
	{
		SVector2D temp;
		temp.x=this->x-right.x;
		temp.y=this->y-right.y;
		return temp;
	}
	SVector2D& operator*(double n)
	{
		this->x*n;
		this->y*n;
		return *this;
	}
	double Vec2DLenght()
	{
		return sqrt(x*x+y*y);
	}
	SVector2D& Normalize()
	{
		double l=this->Vec2DLenght();
		this->x=this->x/l;
		this->y=this->y/l;
		return *this;
	}

};