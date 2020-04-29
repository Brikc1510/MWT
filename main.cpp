#include <iostream>
#include "Mwt.h"
#include "vector"
#include "Carte.h"
#include <windows.h>
#include "graphics.h"
#include <bits/stdc++.h>

using namespace std;

//Permet de tracer une arete
void segement(const Point& p1, const Point& p2)
{
    line(p1.getX(),p1.getY(),p2.getX(),p2.getY());
}
//Permet de tracer tous la carte(triangulation)
void trace(Carte c)
{
    for(int i(0);i<c.getBrins().size();i+=2)
    {
            Brin* tmp = c.getBrins()[i];
             setcolor(WHITE);
            segement(tmp->getSommet()->m_p, tmp->getAlpha()->getSommet()->m_p);

    }
}
//Ordonner les points selon leurs abscisses
bool comparePoint(Point p1, Point p2)
{
    return ((p1.getX() < p2.getX()) || ((p1.getX()== p2.getX()) && (p1.getY()<p2.getY())));
}
int main()
{
    Point p9(500,60),p1(20,60),p3(130,300),p2(100,500),p4(170,600),p5(200,20),p6(220,400),p7(240,200),p8(400,350);
    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    points.push_back(p7);
    points.push_back(p8);
    points.push_back(p9);


//    int n=50;
//    for(int i(0);i<n;i++)
//    {
//        Point p((rand()% 600)+50,(rand()% 600)+50);
//        points.push_back(p);
//
//    }

    //trier les points selon leurs abscisses
    sort(points.begin(),points.end(),comparePoint);
    //ouvrir un praghe pour visualiser les differents triagulations trouvée
    opengraphsize(1200 ,1200);

    Mwt mwt;
    //Instanciation des différents parametres de l'algorithme
    //@param L'ensemble des points de S, Nombre de cycle, Nombre de fourmi, Le taux de pheromone initial, Le paramatre p (pour l'évaporation)
    mwt.Initialize(points,30,5,0.2,0.1);
    Carte c;
    srand(time(NULL));
    for(int k=0;k<mwt.m_C;k++)
    {
        //Affichage des taux de pheromone de chaque arete
        cout << "Le taux de pheromone sur l'arete dont ses deux extremite sont les deux points :" << endl;
        for(int i=0;i<mwt.getAllEdge().getBrins().size();i+=2)
        {
            cout << "(" << mwt.getAllEdge().getBrins()[i]->getSommet()->m_p.getX() <<","<<mwt.getAllEdge().getBrins()[i]->getSommet()->m_p.getY() <<") et ("
            << mwt.getAllEdge().getBrins()[i]->getAlpha()->getSommet()->m_p.getX() <<","<<mwt.getAllEdge().getBrins()[i]->getAlpha()->getSommet()->m_p.getY() << ") "
            << "est egale a: " << mwt.getAllEdge().getBrins()[i]->getMar() << endl;
        }

        //Construction des k-solutions et leurs evaluations
        for(int j=0;j<mwt.m_K;j++)
        {

            c=mwt.BuildSolutionSk(points);
            mwt.EvaluateSolution(c);
        }

        //Affichage des differentes k-solutions construites par les fourmis
        for(int i=0;i<mwt.getSolutions().size();i++)
        {
            c = mwt.getSolutions()[i];
            cout << c.m_value << endl;
            trace(c);
            Sleep(2000);
            cleardevice();
        }
        //Garder la meilleur solution, qui sera utilisé dans la fonction UpdateTrails dans le cas ou on utilise la méthode elitiste
        mwt.SaveBestSolutionSoFar();
        //Permet de mettre a jour le niveau de pheromone sur tous les aretes
        //@param la methode utilise; 0-methode non-elitiste 1-methode elitiste
        mwt.UpdateTrails(1);

    }


    //Recuperer la meilleur solution
    Carte carte=mwt.getBestSolution();
    //Garder l'affichage de la meilleur triangulation ainsi que la somme des longueurs des aretes de cette triangulation
    trace(carte);
    cout << carte.m_value << endl;
    getch();
    closegraph();
    return 0;
}
