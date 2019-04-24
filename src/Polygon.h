#ifndef TRIANGULATION_POLYGON_H
#define TRIANGULATION_POLYGON_H

#include "primitives.h"
#include <vector>

using namespace std;
class Polygon {
public:
    vector <Point> pointList;

    Polygon ();
    Polygon (vector<Point>& );
    bool pointInside(Point mid);
    bool LineInside(Point p1, Point p2);

    // TODO operator=

};


#endif //TRIANGULATION_POLYGON_H

