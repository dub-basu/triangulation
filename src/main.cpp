#include <iostream>
#include <vector>

#include "primitives.h"
#include "DCEL.h"
#include "Status.tpp"
#include "Triangulator.cpp"


using namespace std;

int main() {
    vector<Point> polyPoints;

    polyPoints.push_back(Point(0,0));
    polyPoints.push_back(Point(3,0));
    polyPoints.push_back(Point(5,1));
    polyPoints.push_back(Point(6,3));
    polyPoints.push_back(Point(5,4));
    polyPoints.push_back(Point(3,3));
    polyPoints.push_back(Point(0,1));
    polyPoints.push_back(Point(1,4));

    DCEL dcel(polyPoints);
//    dcel.printDCEL();
//
//    cout << "====================\n";
//    dcel.addEdge(dcel.points[1],dcel.points[6]);
//    // cout << *dcel.points[1]->incidentEdge;
//    dcel.printDCEL();
//
//    cout << "====================\n";
//    dcel.addEdge(dcel.points[2],dcel.points[4]);
//    dcel.printDCEL();
//
//    cout << "====================\n";
//    dcel.addEdge(dcel.points[2],dcel.points[6]);
//    dcel.printDCEL();
//
//    cout << "====================\n";
//    dcel.addEdge(dcel.points[4],dcel.points[6]);
//    dcel.printDCEL();
//
//    cout << "=====================\n";

    Status<HalfEdge> st;
    HalfEdge::lastReference = *dcel.points[2];

    for (auto p : dcel.points){
        cout << *p << "\t";
    }
    cout << "\n";

    HalfEdge* left = dcel.points[3]->incidentEdge;
    HalfEdge* right = dcel.points[0]->incidentEdge;
    cout << (*left < *right) << "\n";

    Triangulator t= Triangulator(Polygon(polyPoints));
    t.makeMonotone();



    return 0;
}