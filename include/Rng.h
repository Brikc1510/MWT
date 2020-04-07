#ifndef RNG_H
#define RNG_H
#include <vector>
#include <Carte.h>
#include <Point.h>
#include <math.h>
class Rng
{
    public:
        Rng();
        virtual ~Rng();
        double Distance(Point p,Point p1);
        Carte DrawRng(std::vector<Point> sommets);

    protected:

    private:
};

#endif // RNG_H
