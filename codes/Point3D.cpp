#include "Point3D.h"

Point3D::Point3D(){
	setZ(0);
}
Point3D::Point3D(int x, int y, int z) : Point2D(x,y){
	setZ(z);
	setDistFrOrigin();
}
int Point3D::getZ(){
	return z;
}
void Point3D::setZ(int z){
	this->z = z;
}
void Point3D::setDistFrOrigin(){
	double d = sqrt((x*x) + (y*y) + (z*z));
	this->distFrOrigin = d;
}
ostream& operator<<(ostream &out, const Point3D &pt3d){
	out << "[" << pt3d.x << ", " << pt3d.y << ", " << pt3d.z << "]" << ", distFrOrigin : " << setprecision(3) << fixed << pt3d.distFrOrigin << endl;
	return out;
}
string getEqual(Point3D p3d_a){
	string e = to_string(p3d_a.getX()) + "," + to_string(p3d_a.getY()) + "," + to_string(p3d_a.getZ());
	return e;
}
