#ifndef GRIDS_H
#define GRIDS_H



#include <iostream>

#include <cmath>

using namespace std;

class Grids
{

public:
    Grids();
    Grids(int r, int c);
    Grids(int r, int c, double **m);
    ~Grids();
    void Mul_Mat(Grids* m1, Grids* m2, Grids* m3);
    void Inv_Mat(Grids* m1, Grids* m2);
    double** Surface_Fitting(Grids* m1, Grids* m2);

private:
    int row;
    int col;
    double **mat;
};



#endif // GRIDS_H
