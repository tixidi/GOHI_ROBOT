#include "tools.h"


TrackBall::TrackBall()
{

}


double TrackBall::dotMult(GPoint3d v1, GPoint3d v2)
{
    double angle;
    angle = v1.x()*v2.x()+v1.y()*v2.y()+v1.z()*v2.z();
    return angle;
}
GPoint3d TrackBall::crossMult(GPoint3d v1, GPoint3d v2)
{
    GPoint3d v;
    v.setX(v1.y()*v2.z()-v1.z()*v2.y());
    v.setY(v1.z()*v2.x()-v1.x()*v2.z());
    v.setZ(v1.x()*v2.y()-v1.y()*v2.x());
    return v;
}

        // 将鼠标二维点映射为球面向量(用于鼠标追踪球)
GPoint3d TrackBall::gMousePtToSphereVec(int x, int y, int w, int h)
{
    double x1,y1,z1,r,len;
    GPoint3d vec;
    x1 = (2.0*x - w) / w;
    y1 = (h - 2.0*y) / h;
    r=x1*x1+y1*y1;
    if(r > 1) r = 1;
    z1 = sqrt(1 - r);
    len = sqrt(x1*x1+y1*y1+z1*z1);
    vec.setX(x1/len);
    vec.setY(y1/len);
    vec.setZ(z1/len);
    return vec;
}
void TrackBall::makeRolate()
{
    glMultMatrixd(mMatrix);
}
void TrackBall::MouseMove(int x, int y,int w ,int h)
{
    if(x != OldX || y != OldY)
    {
        GPoint3d lastVec = gMousePtToSphereVec(OldX, OldY, w, h);
        GPoint3d currentVec = gMousePtToSphereVec(x, y, w, h);
        OldX = x;        OldY = y;
                // 求旋转角度
        double rotAngle = acos(dotMult(lastVec,currentVec))*57.29577958;
        // 求旋转向量轴
        GPoint3d axis = crossMult(lastVec,currentVec);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glRotated(rotAngle, axis.x(), axis.y(), axis.z()); // 旋转

        glMultMatrixd(mMatrix);
        glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);  // 返回当前模型矩阵

        glPopMatrix();
    }
}
