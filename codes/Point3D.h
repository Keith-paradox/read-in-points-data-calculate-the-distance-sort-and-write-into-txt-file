#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

using namespace std;

class Point3D : public Point2D
{
	protected:
		int z;
		void setDistFrOrigin();
	public:
		Point3D();
		Point3D(int x, int y, int z);
		int getZ();
		void setZ(int x);
		friend ostream& operator<<(ostream &out, const Point3D &pt3d);
		string getEqual(Point3D p3d_a);
};
#endif
