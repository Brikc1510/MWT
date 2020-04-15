#ifndef POLYGONE_H
#define POLYGONE_H
#include "Point.h"
#include "Sommet.h"
#include <vector>

class Polygone
{
    public:
        Polygone();
        Polygone(const Point& p);
        ~Polygone();
        Sommet* ajoutSommet(const Point& p, Sommet* s) const;
        void suppSommet(Sommet* s);
        Sommet* getFirst();
        bool aGauche(Point p1, Point p2, Point newPt);
        Polygone enveloppe(std::vector <Point> T);
        int getNombreS();
    private:
        Sommet* m_premier;

};

#endif // POLYGONE_H

