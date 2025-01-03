#include "Utils.h"


IfcSerializer::IfcSerializer(std::string filename) : filename_(filename) 
{

}


IfcVector::IfcVector(double x, double y, double z) : x_(x), y_(y), z_(z) 
{

}

// Getters
double IfcVector::getX() const { return x_; }
double IfcVector::getY() const { return y_; }
double IfcVector::getZ() const { return z_; }

// Setters
void IfcVector::setX(double xVal) { x_ = xVal; }
void IfcVector::setY(double yVal) { y_ = yVal; }
void IfcVector::setZ(double zVal) { z_ = zVal; }

double IfcVector::getXAngle() const 
{
	return 0;
}

IfcVector IfcVector::operator+(const IfcVector& other) const {
    return IfcVector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

IfcVector IfcVector::operator-(const IfcVector& other) const {
    return IfcVector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

IfcVector IfcVector::RotateXY(double angle) const {
    
}

