#include "Brin.h"

Brin::Brin(Sommet* s):m_s(s),m_alpha(nullptr),m_sigma(this),m_sigmaM(this)
{}


Brin* Brin::getAlpha() const
{
    return m_alpha;
}
void Brin::setAlpha(Brin* b)
{
    m_alpha=b;
}
Brin* Brin::getSigma() const
{
    return m_sigma;
}
void Brin::setSigma(Brin* b)
{
    m_sigma=b;
}
Brin* Brin::getSigmaM() const
{
    return m_sigmaM;
}
void Brin::setSigmaM(Brin* b)
{
    m_sigmaM=b;
}
Sommet* Brin::getSommet() const
{
    return m_s;
}
int Brin::getNum() const
{
    return m_num;
}
void Brin::setNum(int i)
{
    m_num=i;
}
double Brin::getMar() const
{
    return m_mar;
}
void Brin::setMar(double i)
{
    m_mar=i;
}

