#include"Point.h"
#include<iostream>
using namespace std;

Point::Point()	//Constructor sets values of x and y to 0
{
	x = 0;
	y = 0;
}
Point::Point(int num1, int num2)	//x and y values change according to num1 and num2
{
	x = num1;
	y = num2;
}

void Point:: setX(int a)	//set value of x to a
{
	 x = a;
}

void Point::setY(int b)		//set value of y to b
{
	y = b;
}

const int Point::getX()		//return new x
{
	return x;
}

const int Point::getY()		//return new y
{
	return y;
}

void Point::displayXY()		//cout x and y
{
	cout << "X = " << x << endl;
	cout << "Y = " << y << endl;

}

const double Point::distance(Point point2)		//distance betweem 2 points
{
	double distance = sqrt(pow(x - point2.x, 2) + pow(y - point2.y, 2));
	return distance;
}
