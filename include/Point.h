#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point(int x,int y);
        Point(const Point& p);
        int getX() const;
        int getY() const;

    private:
        int Member;
        int m_x;
        int m_y;
};

#endif

