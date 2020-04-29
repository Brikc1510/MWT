#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(int x,int y);
        Point(const Point& p);
        int getX() const;
        int getY() const;
        bool operator==(const Point p);


    private:
        int Member;
        int m_x;
        int m_y;
};

#endif

