#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Mwt.h"
#include "Rng.h"
#include "Polygone.h"
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>
#include "graphics.h"

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
    std::cout << "Coucou" << std::endl;
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
    std::cout << "SelectionPoint  (" << selectedPoint.getX() <<","<<selectedPoint.getY() <<")" << std::endl;
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
        pijAll.insert ( std::pair<double,const Point>(pij,p[j]));
    }
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
            return it->second;
        }
        s=s-it->first;

    }

}

bool Mwt::UpdateFeasiblePoints(Carte c,std::vector<Point> p)
{
    int somme=0;
    for(int i=0;i<p.size();i++)
    {
        std::vector<Point> feasibles = FeasiblePoints(p[i],c);
        somme+=feasibles.size();
    }
    if(somme>0)
        return true;
    else
        return false;
}

int Mwt::CalculNumberOfEdge(Carte c)
{
    int somme=0;
    for(int i=0;i<c.getBrins().size();i+=2)
    {
        somme++;
    }
    return somme;
}


Carte Mwt::BuildSolutionSk(std::vector<Point> points)
{
    Rng rng;
    //Cr�ation du graphe de voisinage relative
    Carte c = rng.DrawRng(points);
    //S�l�ction du point initial al�atoirement,il sera colorier en vert
    Mwt mwt;
    mwt.setPoints(points);
    Point pInitial=mwt.SelectInitialPoint(points);
    std::cout << "SelectPointDepart (" << pInitial.getX() <<","<<pInitial.getY() <<")" << std::endl;
    Polygone p;
    p=p.enveloppe(points);
    std::cout << p.getNombreS() << std::endl;
    int numberOfEdge= mwt.CalculNumberOfEdge(c);
    //tester si S est triangul� avec la m�thode FeasiblesPoints
    //while(mwt.UpdateFeasiblePoints(c,points))
    //tester la si S est triangul� avec la formule 3n-n'-3
    while(3*points.size()-p.getNombreS()-3 != numberOfEdge)
    {

        std::vector<Point> feasible= mwt.FeasiblePoints(pInitial,c);
        if(feasible.size()==0)
        {
            //Si le point choisi n'a aucun point r�alisable alors on le change
            //Le troisi�me param�tre est le crit�re de choix
            //1 pour un choix al�atoire 2 pour choisir le point avec le plus de points r�alisables
            //3 pour choisir le point avec le moins de points r�alisables
            pInitial=mwt.SelectPoint(points,c,2);
            std::cout << "SelectPoint (" << pInitial.getX() <<","<<pInitial.getY() <<")" << std::endl;
            feasible= mwt.FeasiblePoints(pInitial,c);

        }

        Point pSelected= mwt.SelectPointProb(feasible,pInitial);
        std::cout << "SelectPointProb (" << pSelected.getX() <<","<<pSelected.getY() <<")" << std::endl;
        c.creeArete(pInitial,pSelected);
        pInitial=pSelected;
        //trace(c);
        numberOfEdge=mwt.CalculNumberOfEdge(c);

    }
    return c;
}
