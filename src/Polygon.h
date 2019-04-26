#ifndef TRIANGULATION_POLYGON_H
#define TRIANGULATION_POLYGON_H

#include "primitives.h"
#include <vector>

using namespace std;
class Polygon {
public:
    vector <Point> pointList;//!< Stores the points in polygon in CCW order
    /**
     * Default constructor of the class.
     */
    Polygon ();
    /**
     * Parameterised constructor. Takes the list of points and sorts them in CCW order to make the polygon.
     * @param f : True if we have to sort, else false.
     */
    Polygon (vector<Point>& , bool f= false);
    /**
     * Tells if a particular point is inside the polygon or not.
     * @param mid The point to check
     * @return True if point is inside the polygon
     */
    bool pointInside(Point mid);
    /**
     * Tells if a particular line is inside this polygon or not.
     * @param p1 First end point of line
     * @param p2 Second end point of line
     * @return True if line is inside the Polygon
     */
    bool LineInside(Point p1, Point p2);

    // TODO operator=

};


#endif //TRIANGULATION_POLYGON_H

