#ifndef TOOLS_H
#define TOOLS_H
#include <cmath>
#include <GL/glu.h>


using namespace std;

#include <gpoint3d.h>

class TrackBall
{

public:
    TrackBall();
        // 向量的点积
    double dotMult(GPoint3d v1, GPoint3d v2);
    // 向量的叉积
    GPoint3d crossMult(GPoint3d v1, GPoint3d v2);
        // 将鼠标二维点映射为球面向量(用于鼠标追踪球)
    GPoint3d gMousePtToSphereVec(int x, int y, int w, int h);
    void makeRolate();

    void MouseMove(int x, int y,int w ,int h);
    void resize()
    {
        glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);  // 返回当前模型矩阵
    }
    void setXY(int x, int y){OldX = x;OldY = y;}
    void setP(double *v)//{x1,y1,z1,  x2,y2,z2,  x3,y3,z3}
    {
        GPoint3d v1,v2,v3;
        v1.setX(v[3]-v[0]);
        v1.setY(v[4]-v[1]);
        v1.setZ(v[5]-v[2]);

        v2.setX(v[6]-v[0]);
        v2.setY(v[7]-v[1]);
        v2.setZ(v[8]-v[2]);

        v3=crossMult(v1,v2);

        glNormal3f(v3.x(),v3.y(),v3.z());
    }
    int OldX;
    int OldY;
    double mMatrix[16];
};


#endif // TOOLS_H
