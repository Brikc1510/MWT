#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Mwt.h"
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>

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
double Mwt::Distance(Point p,Point p1)
{
    double distance = sqrt((p1.getX()-p.getX())*(p1.getX()-p.getX())+(p1.getY()-p.getY())*((p1.getY()-p.getY())));
    return distance;
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
bool CompareDistance(double a,double b)
{
    return a < b;
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

Point Mwt::SelectPointProb(std::vector<Point> p,Point i)
{
    std::map<double,const Point> pijAll;
    double pij,somme=0;
    for(int k=0;k<p.size();k++)
    {
        somme+=pow(0.5,1)*pow(1/Distance(i,p[k]),5);
    }
    for(int j=0;j<p.size();j++)
    {
        pij =(pow(0.5,1)*pow(1/Distance(i,p[j]),5))/somme;
        std::cout << pij<< std::endl;
        pijAll.insert ( std::pair<double,const Point>(pij,p[j]));
    }
    std::cout << "----------"<< std::endl;
    std::map<double,const Point>::iterator it;
    for(it=pijAll.begin();it!=pijAll.end() ; ++it)
    {
        Point p1= it->second ;
        std::cout << it->first <<" ("<<p1.getX() <<" "<<p1.getY()<<")" <<std::endl;
    }
    std::cout << "----------"<< std::endl;
    srand(time(NULL));
    double r = (double) rand()/RAND_MAX;
    std::cout << "random "<< r << std::endl;

    double s=1;
    for(it=pijAll.begin();it!=pijAll.end() ;++it)
    {
         std::cout << s << ">" << r << ">" << s-it->first << std::endl;
        if(s>r && r>s-it->first)
        {
            Point pSelected= it->second;
            std::cout << pSelected.getX() <<","<<pSelected.getY() << std::endl;
            return it->second;
        }
        s=1-it->first;

    }





}

