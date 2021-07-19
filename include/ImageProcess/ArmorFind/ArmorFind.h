#ifndef ARMORFIND_H
#define ARMORFIND_H
#include "./include/ImageProcess/AngleSolver/AngleSolver.h"

class ArmorFind : public AngleSolver
{
public:
    ArmorFind(string path) : AngleSolver(path) {

    }

private:
    Mat srcimg;
};

#endif
