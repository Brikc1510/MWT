#include <iostream>
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

bool Mwt::aGauche(Point p1, Point p2, Point newPt)
{
    if((((p2.getX()-p1.getX())*(newPt.getY()-p1.getY()))-((p2.getY()-p1.getY())*(newPt.getX()-p1.getX())))>0)
        return 1;
    else
        return 0;

}
std::vector<Point> Mwt::FeasiblePoints(Point i,Carte c)
{
    std::vector<Point> feasible;
    for(int k=0;k<points.size();k++)
    {
        if(i!=points[k])
        {
            std::cout<<i.getX() << std::endl;
            std::cout<<points[k].getX() << std::endl;
            std::cout<<"hello" << std::endl;
        }
        if(i!=points[k])
        {


        bool b=true;
        std::vector<Brin*> brins =c.getBrins();
        int j=0;
        while(j<brins.size() && b)
        {

            Brin* br =brins[j];

//                bool t =(aGauche(i,points[k],br->getSommet()->m_p)) && (!aGauche(i,points[k],br->getAlpha()->getSommet()->m_p))&& (aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,points[k])) && (!aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,i));
//                bool t1 =(!aGauche(i,points[k],br->getSommet()->m_p)) && (!aGauche(i,points[k],br->getAlpha()->getSommet()->m_p))&& (aGauche(br->getAlpha()->getSommet()->m_p,br->getSommet()->m_p,i)) && (!aGauche(br->getAlpha()->getSommet()->m_p,br->getSommet()->m_p,points[k]));
//                bool t11=aGauche(i,points[k],br->getSommet()->m_p);
//                bool t12=!aGauche(i,points[k],br->getAlpha()->getSommet()->m_p);
//                bool t13=aGauche(br->getAlpha()->getSommet()->m_p,br->getSommet()->m_p,i);
//                bool t14=!aGauche(br->getAlpha()->getSommet()->m_p,br->getSommet()->m_p,points[k]);
//                bool t4 =(aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)) && (!aGauche(i,points[k],br->getSommet()->m_p))&& (aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,i)) && (!aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,points[k]));
//                bool t5 =(aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)) && (!aGauche(i,points[k],br->getSommet()->m_p))&& (aGauche(br->getAlpha()->getSommet()->m_p,br->getSommet()->m_p,points[k])) && (!aGauche(br->getAlpha()->getSommet()->m_p,br->getSommet()->m_p,i));

                bool t = (aGauche(i,points[k],br->getSommet()->m_p)) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p));
                bool t1 = (!aGauche(i,points[k],br->getSommet()->m_p)) && (!aGauche(i,points[k],br->getAlpha()->getSommet()->m_p));
                //bool t11=(!aGauche(i,points[k],br->getAlpha()->getSommet()->m_p));
                std::cout << points[k].getX()<<","<<points[k].getY() <<" "<< br->getSommet()->m_p.getX()<<","<<br->getSommet()->m_p.getY()<<" "<< br->getAlpha()->getSommet()->m_p.getX()<<","<<br->getAlpha()->getSommet()->m_p.getY() << std::endl;
                std::cout << t << std::endl;
                std::cout << t1 << std::endl;

                std::cout << "---------"<< std::endl;

                if(!t && !t1)
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
