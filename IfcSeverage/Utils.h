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


#endif
