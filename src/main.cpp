#include <iostream>
#include <vector>
#include "primitives.h"
#include "DCEL.h"

using namespace std;

int main() {
    vector<Point> polyPoints;
    polyPoints.push_back(Point(0,0));
    polyPoints.push_back(Point(3,0));
    polyPoints.push_back(Point(5,1));
    polyPoints.push_back(Point(6,3));
    polyPoints.push_back(Point(5,4));
    polyPoints.push_back(Point(3,3));
    polyPoints.push_back(Point(1,4));
    polyPoints.push_back(Point(0,1));

    DCEL dcel(polyPoints);
    dcel.printDCEL();

    cout << "====================\n";
    dcel.addEdge(dcel.points[1],dcel.points[6]);
    dcel.printDCEL();

    cout << "====================\n";
    dcel.addEdge(dcel.points[2],dcel.points[4]);
    dcel.printDCEL();

    cout << "====================\n";
    dcel.addEdge(dcel.points[2],dcel.points[6]);
    dcel.printDCEL();

    cout << "====================\n";
    dcel.addEdge(dcel.points[4],dcel.points[6]);
    dcel.printDCEL();

    cout << "Hello, World!" << std::endl;
    return 0;
}