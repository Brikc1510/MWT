#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point(int x,int y);
        Point(const Point& p);
        int getX() const;
        int getY() const;
        bool operator == (const Point &Ref) const
        {
            return(this->Member == Ref.GetMember());
        }
        bool operator != (const Point &Ref) const
        {
            return(this->Member != Ref.GetMember());
        }

        const int GetMember() const
        {
            return(this->Member);
        }
    private:
        int Member;
        int m_x;
        int m_y;
};

#endif

