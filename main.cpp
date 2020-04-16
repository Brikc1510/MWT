#include <iostream>
#include "Mwt.h"
#include "vector"
#include "Carte.h"
#include <windows.h>
#include "graphics.h"
#include <bits/stdc++.h>

using namespace std;

void segement(const Point& p1, const Point& p2)
{
    line(p1.getX(),p1.getY(),p2.getX(),p2.getY());
}

void trace(Carte c)
{
    for(int i(0);i<c.getBrins().size();i+=2)
    {
            Brin* tmp = c.getBrins()[i];
             setcolor(WHITE);
            segement(tmp->getSommet()->m_p, tmp->getAlpha()->getSommet()->m_p);

    }
}

bool comparePoint(Point p1, Point p2)
{
    return ((p1.getX() < p2.getX()) || ((p1.getX()== p2.getX()) && (p1.getY()<p2.getY())));
}
int main()
{
    //Point p1(400,400),p2(450,430),p3(600,400),p4(550,350),p5(546,20),p6(220,400),p7(240,200),p8(400,350),p9(500,60);
    Point p9(500,60),p1(20,60),p3(130,300),p2(100,500),p4(170,600),p5(200,20),p6(220,400),p7(240,200),p8(400,350);
    vector<Point> points;
//    points.push_back(p1);
//    points.push_back(p2);
//    points.push_back(p3);
//    points.push_back(p4);
//    points.push_back(p5);
//    points.push_back(p6);
//    points.push_back(p7);
//    points.push_back(p8);
//    points.push_back(p9);


    int n=50;
    for(int i(0);i<n;i++)
    {
        Point p((rand()% 600)+50,(rand()% 600)+50);
        points.push_back(p);

    }
    sort(points.begin(),points.end(),comparePoint);
    opengraphsize(1200 ,1200);

    Mwt mwt;
    mwt.Initialize(points,5,20,0.5);
    Carte c;
    srand(time(NULL));
    for(int j=0;j<mwt.m_K;j++)
    {

       c=mwt.BuildSolutionSk(points);
        mwt.EvaluateSolution(c);
    }

    for(int i=0;i<mwt.getCartes().size();i++)
    {

        c = mwt.getCartes()[i];
        cout << c.m_value << endl;
        trace(c);
        Sleep(2000);
        cleardevice();


    }


    getch();
    closegraph();
    return 0;
}
