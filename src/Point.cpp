#include "Point.h"
Point::Point()
{

}

Point::Point(int x, int y) : m_x(x), m_y(y)
{}

Point::Point(const Point& p) : m_x(p.getX()), m_y(p.getY())
{}

int Point::getX() const
{
    return m_x;
}

int Point::getY() const
{
    return m_y;
}

bool Point::operator==(const Point p)
{
    return getX() == p.getX() && getY()==p.getY();
}

