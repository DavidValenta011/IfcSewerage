// IfcSeverage.h : Include file for standard system include files,
// or project specific include files.

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>


class IfcSerializer {
public:
	IfcSerializer(std::string filename);
	~IfcSerializer();

	void doSomething() const;

private:
	std::string filename_;
};


class IfcVector {
private:
	double x_, y_, z_;
public:
	IfcVector(double x = 0, double y = 0, double z = 0);

	// Getters
	double getX() const;
	double getY() const;
	double getZ() const;

	// Setters
	void setX(double xVal);
	void setY(double yVal);
	void setZ(double zVal);

	double getXAngle() const;
	IfcVector operator+(const IfcVector& other) const;
	IfcVector operator-(const IfcVector& other) const;
	IfcVector RotateXY(double angle) const;
};



namespace MathOps {

};


#endif
