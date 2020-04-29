
#include "Polygone.h"
Polygone::Polygone()
{

}
Polygone::Polygone(const Point& p)
{
    m_premier = new Sommet(p);
    m_premier->m_prec = m_premier;
    m_premier->m_suiv = m_premier;

}

Polygone::~Polygone()
{
}
//la fonction qui retourne l'envloppe convexe d'un ensemble de point S
Polygone Polygone::enveloppe(std::vector <Point> T)
{
    Polygone P(T[0]);
    Sommet *p0=P.getFirst();
    Sommet *p1=P.ajoutSommet(T[1],P.getFirst());

    if(aGauche(p0->m_p,p1->m_p,T[2]))
    {
        p0=p1;
        p1=P.ajoutSommet(T[2],p1);

    }
    else
    {

         p1=P.ajoutSommet(T[2],P.getFirst());


    }

    for(int i(3);i < T.size();i++)
    {
        if((T[i].getX()!=T[i-1].getX()) && (T[i].getY()!=T[i-1].getY()))

        while(!aGauche(p1->m_p,p1->m_suiv->m_p,T[i]))
        {

            p1=p1->m_suiv;
        }
        Sommet *haut=p1;
        p1=p0->m_suiv;
        while(!aGauche(p1->m_prec->m_p,p1->m_p,T[i]))
        {

            p1=p1->m_prec;
        }
        p0=p1;
       Sommet *bas=p1->m_suiv;
        while(bas!=haut)
        {
            bas=bas->m_suiv;
            P.suppSommet(bas->m_prec);
        }
        p1=P.ajoutSommet(T[i],p0);

    }




    return P;
}

//Calcule le nombre de sommet de l'enveloppe convexe
int Polygone::getNombreS()
{
    int somme=0;
    if(!this->getFirst()) return 0;
    Sommet* tmp = this->getFirst();
    do
    {
        somme++;
        tmp = tmp->m_suiv;
    } while(tmp != this->getFirst());
    return somme;

}

Sommet* Polygone::ajoutSommet(const Point& p, Sommet* s) const
{
    Sommet* tmp = new Sommet(p);
    tmp->m_suiv = s->m_suiv;
    tmp->m_prec = s;
    s->m_suiv = tmp;
    tmp->m_suiv->m_prec = tmp;
    return tmp;
}

void Polygone::suppSommet(Sommet* s)
{
    if(s->m_suiv == s) return;
    if(s == m_premier) m_premier = s->m_suiv;
    s->m_suiv->m_prec = s->m_prec;
    s->m_prec->m_suiv = s->m_suiv;
    delete s;
}

Sommet* Polygone::getFirst()
{
    return m_premier;
}

bool Polygone::aGauche(Point p1, Point p2, Point newPt)
{
    if((((p2.getX()-p1.getX())*(newPt.getY()-p1.getY()))-((p2.getY()-p1.getY())*(newPt.getX()-p1.getX())))>0)
        return 1;
    else
        return 0;

}



