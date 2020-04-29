#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED
#include "Brin.h"
#include "Point.h"
#include <limits>
#include <vector>
class Carte
{
public:
    Carte();
    //La somme des longueurs des cotes de la carte
    double m_value=std::numeric_limits<double>::max();
    Brin* creeBrin(Brin* b, Brin* a);
    Brin* creeBrin(const Point& p, Brin* a);
    Brin* creeArete(Brin* a,Brin* b);
    Brin* creeArete(Brin* a,const Point& p);
    Brin* creeArete(const Point& p,Brin* a);
    Brin* creeArete(const Point& p,const Point& p1);
    std::vector<Brin*> getBrins();
    Brin* getDernier() const;
    void setDernier(Brin* b);
    std::vector<Brin*> getPile() const;
    void setPile(std::vector<Brin*> b);

private:
    std::vector<Brin*> brins;
    Brin* m_dernier;
    std::vector<Brin*> pile;
};

#endif // CARTE_H_INCLUDED
