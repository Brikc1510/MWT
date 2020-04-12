#ifndef MWT_H
#define MWT_H
#include "Point.h"
#include <Carte.h>
#include <vector>
#include <math.h>


class Mwt
{
    public:
        Mwt();
        virtual ~Mwt();
        std::vector<Point> FeasiblePoints(Point i,Carte c);
        int aGauche(Point p1, Point p2, Point newPt);
        double Distance(Point p,Point p1);
        std::vector<Point> getPoints() const;
        void setPoints(std::vector<Point> p);
        Point SelectInitialPoint(std::vector<Point> p);
        Point SelectPoint(std::vector<Point> p,Carte c,int i);
        Point SelectPointProb(std::vector<Point> p,Point i);
        bool CompareDistance(double a,double b);



    protected:

    private:

        std::vector<Point> points;
};

#endif // MWT_H
