#ifndef BRIN_H_INCLUDED
#define BRIN_H_INCLUDED
#include "Sommet.h"
#include "Point.h"
class Brin
{
public:
    Brin(Sommet* s);
    Brin* getAlpha() const;
    Brin* getSigma() const;
    Brin* getSigmaM() const;
    Sommet* getSommet() const;
    int getNum() const;
    int getMar() const;
    void setSigma(Brin* b);
    void setAlpha(Brin* b);
    void setSigmaM(Brin* b);
    void setNum(int i);
    void setMar(int i);

private:
    Brin* m_alpha;
    Brin* m_sigma;
    Brin* m_sigmaM;
    Sommet* m_s;
    int m_num;
    int m_mar;
};



#endif // BRIN_H_INCLUDED
