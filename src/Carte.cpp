#include "Carte.h"
#include <iostream>
Carte::Carte()
{}

Brin* Carte::creeBrin(Brin* b,Brin* a)
{
    Sommet* s=b->getSommet();
    Brin* br=new Brin(s);
    br->setSigmaM(b);
    br->setSigma(b->getSigma());
    b->getSigma()->setSigmaM(br);
    b->setSigma(br);
    br->setNum(brins.size());
    br->setMar(0);
    br->setAlpha(a);
    if(a != nullptr)
    {
         a->setAlpha(br);
    }
    brins.push_back(br);
    return br;
}
Brin* Carte::creeBrin(const Point& p,Brin* a)
{
    Sommet* s=new Sommet(p);
    Brin* br=new Brin(s);
    br->setNum(brins.size());
    br->setMar(0);
    br->setAlpha(a);
    if(a != nullptr)
    {
         a->setAlpha(br);

    }
    brins.push_back(br);
    return br;

}
Brin* Carte::creeArete(Brin* a,Brin* b)
{
    Brin* br=creeBrin(a,nullptr);
    Brin* br1=creeBrin(b,br);

    return br;

}
Brin* Carte::creeArete(const Point& p,Brin* a)
{
    Brin* br=creeBrin(p,nullptr);
    Brin* br1=creeBrin(a,br);
    return br;

}
Brin* Carte::creeArete(Brin* a,const Point& p)
{
    Brin* br=creeBrin(a,nullptr);
    Brin* br1=creeBrin(p,br);
    return br;
}
Brin* Carte::creeArete(const Point& p,const Point& p1)
{
    Brin* br=creeBrin(p,nullptr);
    Brin* br1=creeBrin(p1,br);

    return br;
}
Brin* Carte::getDernier() const
{
    return m_dernier;
}
void Carte::setDernier(Brin* b)
{
    m_dernier=b;
}
std::vector<Brin*> Carte::getBrins()
{
    return brins;
}
std::vector<Brin*> Carte::getPile() const
{
    return pile;
}

void Carte::setPile(std::vector<Brin*> b)
{
    pile=b;
}
