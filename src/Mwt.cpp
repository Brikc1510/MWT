#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Mwt.h"
#include "Rng.h"
#include "Polygone.h"
#include <algorithm>
#include <vector>
#include <limits>
#include <map>
#include <iterator>
#include "graphics.h"

using namespace std;
Mwt::Mwt()
{
    //ctor
}

Mwt::~Mwt()
{
    //dtor
}

vector<Point> Mwt::getPoints() const
{
    return points;
}
void Mwt::setPoints(vector<Point> p)
{
    points=p;
}
//fonction qui Calcule la distance entre deux point
double Mwt::Distance(Point p,Point p1)
{
    double distance = sqrt((p1.getX()-p.getX())*(p1.getX()-p.getX())+(p1.getY()-p.getY())*((p1.getY()-p.getY())));
    return distance;
}
//Fonction utilisé pour déterminer si un point est agauche/adroite/alignee par rapport a un deux autres point (intersection)
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
//Recuperer une carte qui represente le RNG d'un ensemble de points S
Carte Mwt::getRng()
{
    return m_Rng;
}
void Mwt::setRng(Carte c)
{
    m_Rng=c;
}
//Recuperer une carte qui represente tous les aretes possibles pour un ensemble de points S
Carte Mwt::getAllEdge()
{
    return m_AllEdge;
}
//Ajouter une nouvelle arete à une carte
void Mwt::setEdge(Point p,Point p1)
{
    m_AllEdge.creeArete(p,p1);
}
void Mwt::setEdge(Carte c)
{
    m_AllEdge=c;
}

void Mwt::Initialize(vector<Point> points,int c,int k,double t,double p)
{
    m_K=k;
    m_C=c;
    m_P=p;
    Rng rng;
    //Création du graphe de voisinage relative RNG
    setRng(rng.DrawRng(points));
    setEdge(rng.DrawRng(points));
    setPoints(points);
    for(int i=0;i<points.size();i++)
    {
        vector<Point> feasible=FeasiblePoints(points[i],getRng());
        for(int j=0;j<feasible.size();j++)
        {
            setEdge(points[i],feasible[j]);
        }
    }
    //Instancier toutes les aretes avec un taux de pheromone
    vector<Brin*> brins=getAllEdge().getBrins();
    for(int j=0;j<brins.size();j++)
    {
        brins[j]->setMar(t);
    }
}
//Sélectionner un point aléatoirement d'un ensemble de points S
Point Mwt::SelectInitialPoint(vector<Point> p)
{
    int r =rand() % p.size();
    return p[r];
}

//Retourner les points réalisables pour un certain point choisi
vector<Point> Mwt::FeasiblePoints(Point i,Carte c)
{
    vector<Point> feasible;
    for(int k=0;k<points.size();k++)
    {

        if(i.getX()!= points[k].getX() && i.getY()!=points[k].getY())
        {


        bool b=true;
        vector<Brin*> brins =c.getBrins();
        int j=0;
        while(j<brins.size() && b)
        {

            Brin* br =brins[j];

                bool t = ((aGauche(i,points[k],br->getSommet()->m_p) == 1) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==1)) || ((aGauche(i,points[k],br->getSommet()->m_p)==-1) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==-1));
                bool t1 = ((aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,i)==1) && (aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,points[k])==1)) || ((aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,i)==-1) && (aGauche(br->getSommet()->m_p,br->getAlpha()->getSommet()->m_p,points[k])==-1));
                bool t2 = ((aGauche(i,points[k],br->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==1)) || ((aGauche(i,points[k],br->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==-1));
                bool t3 = ((aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getSommet()->m_p)==-1)) || ((aGauche(i,points[k],br->getAlpha()->getSommet()->m_p)==0) && (aGauche(i,points[k],br->getSommet()->m_p)==1));



                if(!t&!t1&!t2&!t3 || GetEdgeValue(i,points[k])==0)
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
/*Sélectionner un point aléatoirement d'un ensemble de points S selon des critère
 1 pour un choix aléatoire
 2 pour choisir le point avec le plus de points réalisables
 3 pour choisir le point avec le moins de points réalisables
*/
Point Mwt::SelectPoint(vector<Point> p,Carte c,int i)
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
    return selectedPoint;

}
//Récupérer la taux de phéromone sur une arete dont ses deux extrimétes sont les deux points passés en paramètre
double Mwt::GetEdgeValue(Point p,Point p1)
{
    vector<Brin*> brins = getAllEdge().getBrins();
    for(int i=0;i<brins.size();i++)
    {
        if((brins[i]->getSommet()->m_p == p && brins[i]->getAlpha()->getSommet()->m_p == p1) || (brins[i]->getSommet()->m_p == p1 && brins[i]->getAlpha()->getSommet()->m_p == p))
        {
            return brins[i]->getMar();
        }
    }
}
//Choisir le point avec le quel on va créer une nouvel arete de la triangulation
Point Mwt::SelectPointProb(vector<Point> p,Point i)
{
    map<double,const Point> pijAll;
    double pij,somme=0;
    for(int k=0;k<p.size();k++)
    {
        somme+=pow(GetEdgeValue(i,p[k]),1)*pow(1/Distance(i,p[k]),5);
    }
    //Calculer le pij de chaque point réalisable
    for(int j=0;j<p.size();j++)
    {
        /*On obtient ce cas quand le taux de phéromone est égale à 0
          C'est un cas d'erreur, on doit choisir un autre point
        */
        if(somme == 0)
        {
            return Point(-1,-1);
        }
        else
        {
             pij =(pow(GetEdgeValue(i,p[j]),1)*pow(1/Distance(i,p[j]),5))/somme;
            pijAll.insert (pair<double,const Point>(pij,p[j]));
        }

    }
    //Affichage des probalité de chaque point réalisable ainsi que les coordonées de ce point
    map<double,const Point>::iterator it;
    for(it=pijAll.begin();it!=pijAll.end() ; ++it)
    {
        Point p1= it->second ;
        cout << it->first <<" ("<<p1.getX() <<" "<<p1.getY()<<")" <<endl;
    }
    cout << "----------"<< endl;

    //On tire un nombre aléatoire
    double r = (double) rand()/RAND_MAX;
    cout << "random "<< r << endl;

    //on choisit le point à utiliser selon le nombre aléatoire tiré
    double s=1;
    for(it=pijAll.begin();it!=pijAll.end() ;++it)
    {
        cout << s << ">" << r << ">" << s-it->first << endl;
        if(s>r && r>s-it->first)
        {
            Point pSelected= it->second;
            return it->second;
        }
        s=s-it->first;

    }
}

//Permet de vérifier si S est totalement triangulé
bool Mwt::UpdateFeasiblePoints(Carte c,vector<Point> p)
{
    int somme=0;
    for(int i=0;i<p.size();i++)
    {
        vector<Point> feasibles = FeasiblePoints(p[i],c);
        somme+=feasibles.size();
    }
    if(somme>0)
        return true;
    else
        return false;
}

//Calculer le nombre d'aretes déjà crées
int Mwt::CalculNumberOfEdge(Carte c)
{
    int somme=0;
    for(int i=0;i<c.getBrins().size();i+=2)
    {
        somme++;
    }
    return somme;
}

//C'est l'algorithme 2 de notre article
Carte Mwt::BuildSolutionSk(vector<Point> points)
{

    //Récupération du graphe de voisinage relative
    Carte c = getRng();
    //Séléction du point initial aléatoirement,il sera colorier en vert
    Point pInitial=SelectInitialPoint(points);
    cout << "SelectPointDepart (" << pInitial.getX() <<","<<pInitial.getY() <<")" << endl;
    //Calucler le nombre de sommet de l'enveloppe convexe
    Polygone p;
    p=p.enveloppe(points);
    int numberOfEdge= CalculNumberOfEdge(c);

    //Tester si S est triangulé avec la méthode FeasiblesPoints
    //while(UpdateFeasiblePoints(c,points))
    //tester la si S est triangulé avec la formule 3n-n'-3
    while(3*points.size()-p.getNombreS()-3 != numberOfEdge)
    {
        vector<Point> feasible= FeasiblePoints(pInitial,c);
        cout << feasible.size() << endl;
        if(feasible.size()==0)
        {
            //Si le point choisi n'a aucun point réalisable alors on le change
            //Le troisième paramètre est le critère de choix
            //1 pour un choix aléatoire 2 pour choisir le point avec le plus de points réalisables
            //3 pour choisir le point avec le moins de points réalisables
            pInitial=SelectPoint(points,c,2);
            cout << "SelectPoint (" << pInitial.getX() <<","<<pInitial.getY() <<")" << endl;
            feasible= FeasiblePoints(pInitial,c);

        }

        Point pSelected= SelectPointProb(feasible,pInitial);
        cout << "SelectPointProb (" << pSelected.getX() <<","<<pSelected.getY() <<")" << endl;
        if(pSelected.getX()==-1 && pSelected.getY() ==-1)
        {
           do
            {
                pInitial=SelectPoint(getPoints(),c,1);
                cout << pInitial.getX() << " , " << pInitial.getY() << endl;
                feasible= FeasiblePoints(pInitial,c);

            }while(feasible.size() == 0);
            pSelected=SelectPointProb(feasible,pInitial);
        }
        c.creeArete(pInitial,pSelected);
        pInitial=pSelected;
        numberOfEdge=CalculNumberOfEdge(c);

    }
    cout << "==========================" << endl;
    return c;
}
//Permet de récupérer les k-solution construites par les fourmis dans un cycle
vector<Carte> Mwt::getSolutions() const
{
    return m_Solutions;
}
void Mwt::setSolution(Carte c)
{
        m_Solutions.push_back(c);
}
void Mwt::DeleteSolutions()
{
    m_Solutions.clear();
}
//Calculer la longueur des aretes d'une triangulation
double Mwt::EvaluateSolution(Carte c)
{

    double somme=0;
    for(int i=0;i<c.getBrins().size();i+=2)
    {
        somme+=Distance(c.getBrins()[i]->getSommet()->m_p,c.getBrins()[i]->getAlpha()->getSommet()->m_p);
    }
    c.m_value=somme;
    setSolution(c);
    return somme;
}
//Récupérer la meilleur solution
Carte Mwt::getBestSolution()
{
    return m_BestSolution;
}
void Mwt::setBestSolution(Carte c)
{
    m_BestSolution=c;
}
//Sauvgarder la meilleur solution
void Mwt::SaveBestSolutionSoFar()
{

    Carte c=getBestSolution();
    double value=c.m_value;
    for(int i=0;i<getSolutions().size();i++)
    {
        if(getSolutions()[i].m_value<value)
        {
            value=getSolutions()[i].m_value;
            c=getSolutions()[i];
        }
    }
    c.m_value=value;
    setBestSolution(c);
}
/*Mettre à jour le niveau de phéromone
@param la méthode à choisir 0- méthode non-élitiste 1-méthode élitiste
*/
void Mwt::UpdateTrails(int i)
{
     vector<Brin*> brinsAllEdge= getAllEdge().getBrins();
     vector<Brin*> brinsSolution;
     double somme;
     switch(i)
     {
        case 0:
            for(int i=0;i<brinsAllEdge.size();i+=2)
             {
                 if(brinsAllEdge[i]->getMar() < 0.05)
                 {
                     brinsAllEdge[i]->setMar(0);
                 }
                 else
                 {
                     somme=0;
                     for(int j=0;j<m_Solutions.size();j++)
                     {
                        brinsSolution=m_Solutions[j].getBrins();
                        for(int k=0;k<brinsSolution.size();k+=2)
                        {
                            if((brinsSolution[k]->getSommet()->m_p == brinsAllEdge[i]->getSommet()->m_p && brinsSolution[k]->getAlpha()->getSommet()->m_p == brinsAllEdge[i]->getAlpha()->getSommet()->m_p) || (brinsSolution[k]->getSommet()->m_p == brinsAllEdge[i]->getAlpha()->getSommet()->m_p && brinsSolution[k]->getAlpha()->getSommet()->m_p == brinsAllEdge[i]->getSommet()->m_p))
                            {
                                somme+=100/m_Solutions[j].m_value; //Q/Lk
                                cout <<"somme :"<<m_Solutions[j].m_value<<" "<< somme << endl;
                            }
                        }

                     }
                    double s=(1-m_P)*brinsAllEdge[i]->getMar()+somme;
                    cout <<"to :"<<brinsAllEdge[i]->getMar()<<" "<< s << endl;
                    brinsAllEdge[i]->setMar(s);
                 }
             }

             DeleteSolutions();
            break;
        case 1:

             for(int i=0;i<brinsAllEdge.size();i+=2)
             {
                 if(brinsAllEdge[i]->getMar() < 0.05)
                 {
                     brinsAllEdge[i]->setMar(0);
                 }
                 else
                 {

                     somme=0;
                        brinsSolution=getBestSolution().getBrins();
                        for(int k=0;k<brinsSolution.size();k+=2)
                        {
                            if((brinsSolution[k]->getSommet()->m_p == brinsAllEdge[i]->getSommet()->m_p && brinsSolution[k]->getAlpha()->getSommet()->m_p == brinsAllEdge[i]->getAlpha()->getSommet()->m_p) || (brinsSolution[k]->getSommet()->m_p == brinsAllEdge[i]->getAlpha()->getSommet()->m_p && brinsSolution[k]->getAlpha()->getSommet()->m_p == brinsAllEdge[i]->getSommet()->m_p))
                            {
                                somme+=500/getBestSolution().m_value; //Q/Lk
                                cout <<"somme :"<<getBestSolution().m_value<<" "<< somme << endl;
                            }
                        }

                    double s=(1-m_P)*brinsAllEdge[i]->getMar()+somme;
                    cout <<"to :"<<brinsAllEdge[i]->getMar()<<" "<< s << endl;
                    brinsAllEdge[i]->setMar(s);
                 }
             }

             DeleteSolutions();
            break;

     }

}
