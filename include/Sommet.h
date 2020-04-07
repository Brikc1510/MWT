#ifndef SOMMET_H
#define SOMMET_H
#include "Point.h"

class Sommet
{
    public:
        Sommet(Point const& p);
        Point m_p;
        Sommet* m_suiv;
        Sommet* m_prec;
};

#endif // SOMMET_H

