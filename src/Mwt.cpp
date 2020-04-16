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

Carte Mwt::getRng()
{
    return m_Rng;
}
void Mwt::setRng(Carte c)
{
    m_Rng=c;
}
Carte Mwt::getAllEdge()
{
    return m_AllEdge;
}
void Mwt::setEdge(Point p,Point p1)
{
    m_AllEdge.creeArete(p,p1);
}
void Mwt::setEdge(Carte c)
{
    m_AllEdge=c;
}
void Mwt::Initialize(std::vector<Point> points,int c,int k,double t)
{
    m_K=k;
    m_C=c;
    Rng rng;
    //Création du graphe de voisinage relative
    setRng(rng.DrawRng(points));
    setEdge(rng.DrawRng(points));
    setPoints(points);
    for(int i=0;i<points.size();i++)
    {
        std::vector<Point> feasible=FeasiblePoints(points[i],getRng());
        for(int j=0;j<feasible.size();j++)
        {
            setEdge(points[i],feasible[j]);
        }
    }
     std::vector<Brin*> brins=getAllEdge().getBrins();
    for(int j=0;j<brins.size();j++)
    {
        brins[j]->setMar(t);
    }
}

Point Mwt::SelectInitialPoint(std::vector<Point> p)
{
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

    //Création du graphe de voisinage relative
    Carte c = getRng();
    //Séléction du point initial aléatoirement,il sera colorier en vert
    Point pInitial=SelectInitialPoint(points);
    std::cout << "SelectPointDepart (" << pInitial.getX() <<","<<pInitial.getY() <<")" << std::endl;
    //Calucler le nombre de sommet de l'enveloppe convexe
    Polygone p;
    p=p.enveloppe(points);
    int numberOfEdge= CalculNumberOfEdge(c);
    //tester si S est triangulé avec la méthode FeasiblesPoints
    //while(UpdateFeasiblePoints(c,points))
    //tester la si S est triangulé avec la formule 3n-n'-3
    while(3*points.size()-p.getNombreS()-3 != numberOfEdge)
    {

        std::vector<Point> feasible= FeasiblePoints(pInitial,c);
        if(feasible.size()==0)
        {
            //Si le point choisi n'a aucun point réalisable alors on le change
            //Le troisième paramètre est le critère de choix
            //1 pour un choix aléatoire 2 pour choisir le point avec le plus de points réalisables
            //3 pour choisir le point avec le moins de points réalisables
            pInitial=SelectPoint(points,c,2);
            std::cout << "SelectPoint (" << pInitial.getX() <<","<<pInitial.getY() <<")" << std::endl;
            feasible= FeasiblePoints(pInitial,c);

        }

        Point pSelected= SelectPointProb(feasible,pInitial);
        std::cout << "SelectPointProb (" << pSelected.getX() <<","<<pSelected.getY() <<")" << std::endl;
        c.creeArete(pInitial,pSelected);
        pInitial=pSelected;
        numberOfEdge=CalculNumberOfEdge(c);

    }
    return c;
}
std::vector<Carte> Mwt::getCartes() const
{
    return cartes;
}
void Mwt::setCarte(Carte c)
{
    cartes.push_back(c);
}

double Mwt::EvaluateSolution(Carte c)
{
    double somme=0;
    for(int i=0;i<c.getBrins().size();i+=2)
    {
        somme+=Distance(c.getBrins()[i]->getSommet()->m_p,c.getBrins()[i]->getAlpha()->getSommet()->m_p);
    }
    c.m_value=somme;
    setCarte(c);
    return somme;
}
