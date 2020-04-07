#ifndef MWT_H
#define MWT_H
#include "Point.h"
#include <Carte.h>
#include <vector>

class Mwt
{
    public:
        Mwt();
        virtual ~Mwt();
        std::vector<Point> FeasiblePoints(Point i,Carte c);
        bool aGauche(Point p1, Point p2, Point newPt);
        std::vector<Point> getPoints() const;
        void setPoints(std::vector<Point> p);



    protected:

    private:

        std::vector<Point> points;
};

#endif // MWT_H
