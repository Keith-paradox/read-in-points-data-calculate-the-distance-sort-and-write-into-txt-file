#ifndef MYTEMPLATE_H
#define MYTEMPLATE_H

#include "Point2D.cpp"
#include "Point3D.cpp"
#include "Line2D.cpp"
#include "Line3D.cpp"

using namespace std;
string getEqual(int a){
	return to_string(a);
}
string getEqual(double a){
	return to_string(a);
}
string getEqual(float a){
	return to_string(a);
}
template <typename T> double scalar_difference (T a, T b)
{
	double value = 0;
	if(a.getScalarValue() > b.getScalarValue()){
		value = a.getScalarValue() - b.getScalarValue();
	}
	else if(a.getScalarValue() < b.getScalarValue()){
		value = b.getScalarValue() - a.getScalarValue();
	}
	return value;
}
template <typename T> bool equals (T a, T b)
{
	bool equal_value = false;
	if(getEqual(a) == getEqual(b)){
			equal_value = true;
	}
	return equal_value;
	
}
#endif
