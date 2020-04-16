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
        bool UpdateFeasiblePoints(Carte c,std::vector<Point> p);
        int CalculNumberOfEdge(Carte c);
        Carte BuildSolutionSk(std::vector<Point> points);

        double EvaluateSolution(Carte c);
        std::vector<Carte> getCartes() const;
        void setCarte(Carte c);

        void Initialize(std::vector<Point> points,int c,int k,double t);
        Carte getAllEdge();
        void setEdge(Point p,Point p1);
        void setEdge(Carte c);
        Carte getRng();
        void setRng(Carte c);
        int m_K,m_C;

    protected:

    private:
        Carte m_Rng;
        Carte m_AllEdge;
        std::vector<Carte> cartes;
        std::vector<Point> points;
};

#endif // MWT_H
