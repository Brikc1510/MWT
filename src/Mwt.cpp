#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Mwt.h"
#include <vector>

Mwt::Mwt()
{
    //ctor
}

Mwt::~Mwt()
{
    //dtor
}
std::vector<Point> Mwt::getPoints() const
{
    return points;
}
void Mwt::setPoints(std::vector<Point> p)
{
    points=p;
}

int Mwt::aGauche(Point p1, Point p2, Point newPt)
{
    if((((p2.getX()-p1.getX())*(newPt.getY()-p1.getY()))-((p2.getY()-p1.getY())*(newPt.getX()-p1.getX())))>0)
        return 1;
    else
    {
        if((((p2.getX()-p1.getX())*(newPt.getY()-p1.getY()))-((p2.getY()-p1.getY())*(newPt.getX()-p1.getX())))<0)
            return -1;
        else
            return 0;
    }


}
Point Mwt::SelectInitialPoint(std::vector<Point> p)
{
    srand(time(NULL));
    int r =rand() % p.size();
    return p[r];
}


std::vector<Point> Mwt::FeasiblePoints(Point i,Carte c)
{
    std::vector<Point> feasible;
    for(int k=0;k<points.size();k++)
    {

        if(i.getX()!= points[k].getX() && i.getY()!=points[k].getY())
        {


        bool b=true;
        std::vector<Brin*> brins =c.getBrins();
        int j=0;
        while(j<brins.size() && b)
        {

            Brin* br =brins[j];

                bool t = ((aGauche(i,points[k],br->getSommet()->m_p) == 1) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==1)) || ((aGauche(i,points[k],br->getSommet()->m_p)==-1) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==-1));
                bool t1 = ((aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,i)==1) && (aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,points[k])==1)) || ((aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,i)==-1) && (aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,points[k])==-1));
                bool t2 = ((aGauche(i,points[k],br->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==1)) || ((aGauche(i,points[k],br->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==-1));
               bool t3 = ((aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getSommet()->m_p)==-1)) || ((aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getSommet()->m_p)==1));



                if(!t&!t1&!t2&!t3)
                {
                  b=false;
                }

           j+=2;

        }
        if(b)
        feasible.push_back(points[k]);
        }
    }
    return feasible;

}

Point Mwt::SelectPoint(std::vector<Point> p,Carte c,int i)
{
    Point selectedPoint;
    int s;
    switch(i)
    {
        case 1:
            do
            {
                srand(time(NULL));
                 s=rand() % p.size();
            }while(FeasiblePoints(p[s],c).size()==0);
            selectedPoint=p[s];
            break;
        case 2:
            s=0;
            for(int j =0;j<p.size();j++)
            {
                if(FeasiblePoints(p[j],c).size()>s)
                {
                    s=FeasiblePoints(p[j],c).size();
                    selectedPoint=p[j];
                }
            }
            break;
        case 3:

            s=100;
            for(int j =0;j<p.size();j++)
            {
                if(FeasiblePoints(p[j],c).size()<s && FeasiblePoints(p[j],c).size()!=0)
                {
                    s=FeasiblePoints(p[j],c).size();
                    selectedPoint=p[j];
                }
            }
            break;

    }
    return selectedPoint;


}

