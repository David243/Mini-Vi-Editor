#ifndef POINT_
#define POINT_

class Point
{
public: 
	void setX(int);
	void setY(int);
	const int getX();
	const int getY();
	void displayXY();
	const double distance(Point );
	Point();
	Point(int, int);
private:
	int x;
	int y;
};

#endif