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


