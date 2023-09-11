#include "Point2D.h"

Point2D::Point2D(){
	setX(0);
	setY(0);
}
Point2D::Point2D(int x, int y){
	setX(x);
	setY(y);
	setDistFrOrigin();
};
int Point2D::getX(){
	return x;
}
int Point2D::getY(){
	return y;
}
double Point2D::getScalarValue(){
	return distFrOrigin;
}
void Point2D::setX(int x){
	this->x = x;
}
void Point2D::setY(int y){
	this->y = y;
}
void Point2D::setDistFrOrigin(){
	double d = sqrt((x*x) + (y*y));
	this->distFrOrigin = d;
}
ostream& operator<<(ostream &out, const Point2D &pt2d)
{
	out << "[" << pt2d.x << ", " << pt2d.y << "]" << ", distFrOrigin : " << setprecision(3) << fixed << pt2d.distFrOrigin << endl;
	return out;
}
string getEqual(Point2D p2d_a){
	string e = to_string(p2d_a.getX()) + "," + to_string(p2d_a.getY());
	return e;
}
