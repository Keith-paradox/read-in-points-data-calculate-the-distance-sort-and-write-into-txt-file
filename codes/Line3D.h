#ifndef LINE3D_H
#define LINE3D_H

#include "Point3D.h"
#include "Line2D.h"

using namespace std;

class Line3D : public Line2D
{

	private:
		Point3D pt1;
		Point3D pt2;
	protected:
		void setLength();
	public:
		Line3D();
		Line3D(Point3D pt1, Point3D pt2);
		
		Point3D getPt1();
		Point3D getPt2();
		
		void setPt1(Point3D pt1);
		void setPt2(Point3D pt2);
		friend ostream& operator<<(ostream &out, Line3D &l3d);
		string getEqual(Line3D l3d_a);
};

#endif
