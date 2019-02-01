#ifndef GPOINT3D_H
#define GPOINT3D_H


struct GPoint3d{
    double mX, mY, mZ;
    double x() { return mX; }
    double y() { return mY; }
    double z() {return mZ; }
    void setX(double x)  { mX = x; }
    void setY(double y)  { mY = y; }
    void setZ(double z)     { mZ = z; }
    void set(double x, double y, double z) { mX = x; mY = y; mZ = z;}
};


#endif // GPOINT3D_H
