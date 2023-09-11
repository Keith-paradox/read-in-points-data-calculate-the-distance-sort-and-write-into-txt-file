#ifndef POINT2D_H
#define POINT2D_H

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <typeinfo>

using namespace std;

class Point2D
{
	protected:
		int x;
		int y;
		double distFrOrigin;
		void setDistFrOrigin();
	public:
		Point2D();
		Point2D(int x, int y);
		int getX();
		int getY();
		double getScalarValue();
		void setX(int x);
		void setY(int y);
		friend ostream& operator<<(ostream &out, const Point2D &pt2d);
		string getEqual(Point2D p2d_a);
};
#endif
