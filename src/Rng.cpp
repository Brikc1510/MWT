#include <iostream>
#include "Rng.h"
#include "Carte.h"
#include "graphics.h"
using namespace std;
Rng::Rng()
{

}

Rng::~Rng()
{
    //dtor
}

double Rng::Distance(Point p,Point p1)
{
    double distance;
    distance = sqrt((p1.getX()-p.getX())*(p1.getX()-p.getX())+(p1.getY()-p.getY())*((p1.getY()-p.getY())));
    return distance;
}
//Créer le graphe de voisinage relative
Carte Rng::DrawRng(std::vector<Point> sommets)
{
    bool b;
    Carte c;
    for(int i =0;i<sommets.size();i++)
    {
        Brin* br = nullptr;
        for(int j =i+1;j<sommets.size();j++)
        {
            b =true;
            for(int k =0;k<sommets.size();k++)
            {
                double dis = fmax(Distance(sommets[i],sommets[k]),Distance(sommets[j],sommets[k]));

                if(!(Distance(sommets[i],sommets[j])<= dis) && b)
                {
                    b=false;
                }
            }
            if(b)
            {
                if(br == nullptr)
                {
                    br=c.creeArete(sommets[i],sommets[j]);
                }
                else
                {
                    c.creeArete(br,sommets[j]);
                }

            }

        }
    }
    return c;
}
