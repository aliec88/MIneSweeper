#pragma once
struct SPoint
{
	double x,y;
	SPoint(){x=0;y=0;}
	SPoint(double a,double b){x=a;y=b;}
};
struct SVector2D
{
	double x,y;
	SVector2D(){x=0;y=0;}
	SVector2D(double a,double b){x=a;y=b;}
	SVector2D& operator-(const SVector2D& right)
	{
		SVector2D temp;
		temp.x=this->x-right.x;
		temp.y=this->y-right.y;
		return temp;
		
	}
	SVector2D& operator*(const double right)
	{
		SVector2D temp;
		temp.x=x*right;
		temp.y=y*right;
		return temp;		
	}
	SVector2D& operator+=(const SVector2D& right)
	{
		x+=right.x;
		y+=right.y;
		return *this;		
	}
	double Getlength()
	{
		return sqrt(x*x+y*y);
	}
	double Getdistance(SVector2D & right)
	{
		return sqrt((right.x-x)*(right.x-x)+(right.y-y)*(right.y-y));
	}
	SVector2D& Normalize()
	{
		/*double l=Getlength();
		SVector2D temp;
		temp.x=x/l;
		temp.y=y/l;
		return temp;*/
		double l=Getlength();
		x/=l;
		y/=l;
		return *this;
	}
	double Dot(SVector2D& right)
	{
		return x*right.x+y*right.y;
	}
	int sign(SVector2D& right)
	{
		if (y*right.x>x*right.y)
		{
			return 1;
		}else
		{
			return -1;
		}
	}
};