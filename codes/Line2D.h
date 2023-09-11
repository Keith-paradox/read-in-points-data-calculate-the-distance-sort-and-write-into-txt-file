#ifndef LINE2D_H
#define LINE2D_H

#include "Point2D.h"

using namespace std;

class Line2D
{

	private:
		Point2D pt1;
		Point2D pt2;
	protected:
		double length;
		void setLength();
	public:
		Line2D();
		Line2D(Point2D pt1, Point2D pt2);
		Point2D getPt1();
		Point2D getPt2();
		double getScalarValue();
		
		void setPt1(Point2D pt1);
		void setPt2(Point2D pt2);
		friend ostream& operator<<(ostream &out, Line2D &l2d);
		string getEqual(Line2D l2d_a);

};

#endif
