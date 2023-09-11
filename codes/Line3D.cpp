#include "Line3D.h"
Line3D::Line3D()
{
	
};
Line3D::Line3D(Point3D pt1, Point3D pt2) : Line2D(pt1, pt2)
{
	setPt1(pt1);
	setPt2(pt2);
	setLength();
};
void Line3D::setLength(){
	double l = sqrt(pow(pt1.getX()-pt2.getX(),2)+pow(pt1.getY() - pt2.getY(), 2)+pow(pt1.getZ()-pt2.getZ(),2));
	this->length = l;
}
Point3D Line3D::getPt1(){
	return pt1;
}
Point3D Line3D::getPt2(){
	return pt2;
}
void Line3D::setPt1(Point3D pt1){
	this->pt1 = pt1;
}
void Line3D::setPt2(Point3D pt2){
	this->pt2 = pt2;
}
ostream& operator<<(ostream &out, Line3D &l3d){
	out << "( [" << l3d.pt1.getX() << ", " << l3d.pt1.getY() << ", " << l3d.pt1.getZ() << "]" << ", distFrOrigin : " << l3d.pt1.getScalarValue() << " to " << "[" << l3d.pt2.getX() << ", " << l3d.pt2.getY() << ", " << l3d.pt2.getZ() << "]" << ", distFrOrigin : " << l3d.pt2.getScalarValue() << " ), length : " << setprecision(3) << fixed << l3d.length << endl;
	return out;
}
string getEqual(Line3D l3d_a){
	string e = to_string(l3d_a.getPt1().getX()) + "," + to_string(l3d_a.getPt1().getY()) + "," + to_string(l3d_a.getPt1().getZ()) + "." + to_string(l3d_a.getPt2().getX()) + "," + to_string(l3d_a.getPt2().getY()) + "," + to_string(l3d_a.getPt2().getZ());
	return e;
}
