#include "Line2D.h"

Line2D::Line2D()
{
	
};

Line2D::Line2D(Point2D pt1, Point2D pt2)
{
	setPt1(pt1);
	setPt2(pt2);
	setLength();
};
void Line2D::setLength(){
	double l = sqrt(pow(pt1.getX()-pt2.getX(),2)+pow(pt1.getY() - pt2.getY(), 2));
	this->length = l;
}
Point2D Line2D::getPt1(){
	return pt1;
}
Point2D Line2D::getPt2(){
	return pt2;
}
double Line2D::getScalarValue(){
	return length;
}
void Line2D::setPt1(Point2D pt1){
	this->pt1 = pt1;
}
void Line2D::setPt2(Point2D pt2){
	this->pt2 = pt2;
}
ostream& operator<<(ostream &out, Line2D &l2d){
	out << "( [" << l2d.pt1.getX() << ", " << l2d.pt1.getY() << "]" << ", distFrOrigin : " << l2d.pt1.getScalarValue() << " to [" << l2d.pt2.getX() << ", " << l2d.pt2.getY() << "]" << ", distFrOrigin : " << l2d.pt2.getScalarValue() << " ), length : " << setprecision(3) << fixed << l2d.length << endl;
	return out;
}
string getEqual(Line2D l2d_a){
	string e = to_string(l2d_a.getPt1().getX()) + "," + to_string(l2d_a.getPt1().getY()) + "." + to_string(l2d_a.getPt2().getX()) + "," + to_string(l2d_a.getPt2().getY());
	return e;
}
