#include <vector>
#include <algorithm>
#include "Polygon.h"
#include "primitives.h"


Polygon::Polygon() {
    // Does nothing
}

Polygon::Polygon(vector<Point> &points) {
    // To Fill in points in counter clockwise order



    vector<PolarPoint> polarPts;

    coordinate x= 0, y= 0;
    for (auto p : points){
        //    polarPts.push_back(PolarPoint(p));
        x += p.x;
        y += p.y;
    }
    x /= points.size();
    y /= points.size();

    Point ref = Point(x,y);

    for (auto p : points){
        polarPts.push_back(PolarPoint(p,ref));
    }

    sort(polarPts.begin(),polarPts.end());

    for (auto pp : polarPts){
        pointList.push_back( Point(pp.x,pp.y) );
    }

    // this->pointList = points;

}
long double isLeft( Point P0, Point P1, Point P2 )
{
    return ( (P1.x - P0.x) * (P2.y - P0.y) - (P2.x -  P0.x) * (P1.y - P0.y) );
}
bool Polygon:: pointInside(Point P)
{
    int    wn = 0;    // the  winding number counter

    // loop through all edges of the polygon
    vector<Point>V=pointList;
//    cout<<"pointList.size()="<<pointList.size()<<" checking for point "<<P<<endl;
//    cout<<"Points : ";for(auto i:pointList)cout<<i<<" ";cout<<endl;
    int n=pointList.size();
    for (int i=0; i<pointList.size(); i++) {   // edge from V[i] to  V[i+1]
        //cout<<i<<" "<<V[i]<<" "<<V[(i+1)%n]<<" ";
        if (V[i].y <= P.y) {          // start y <= P.y
            if (V[(i+1)%n].y  > P.y)      // an upward crossing
                if (isLeft( V[i], V[(i+1)%n], P) > 0)  // P left of  edge
                    ++wn;            // have  a valid up intersect
        }
        else {                        // start y > P.y (no test needed)
            if (V[(i+1)%n].y  <= P.y)     // a downward crossing
                if (isLeft( V[i], V[(i+1)%n], P) < 0)  // P right of  edge
                    --wn;            // have  a valid down intersect
        }
        //cout<<"wn="<<wn<<" cross="<<isLeft(V[i], V[(i+1)%n], P)<<endl;
    }
    return wn!=0;
}
bool Polygon:: LineInside(Point p1, Point p2)
{
    LineSegment l1= LineSegment(p1,p2);
    for(int i=0;i<pointList.size();i++)
    {
        LineSegment l2=LineSegment(pointList[i],pointList[(i+1)%pointList.size()]);
        //cout<<"Checking int b/w "<<l1 << " and "<<l2<<endl;
        //cout<<l1.intersects_at(l2)<<" is point of int. "<<endl;
        Point p=l1.intersects_at(l2);
        if(p.is_nan() or p==l1.start_pt() or p==l1.end_pt() or p==l2.start_pt() or p==l2.end_pt())continue;
        return false;
    }
    return true;
}


