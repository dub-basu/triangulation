#include <iostream>
#include <vector>

#include "primitives.h"
#include "DCEL.h"
#include "Status.tpp"
#include "Triangulator.h"


using namespace std;

int main() {
    vector<Point> polyPoints;

//    Test case 1.
    polyPoints.push_back(Point(0,0));
    polyPoints.push_back(Point(1,1));
    polyPoints.push_back(Point(5,-1));
    polyPoints.push_back(Point(4,3));
    polyPoints.push_back(Point(8,2));
    polyPoints.push_back(Point(9,8));
    polyPoints.push_back(Point(6,7));
    polyPoints.push_back(Point(5,10));
    polyPoints.push_back(Point(3,9));
    polyPoints.push_back(Point(1,10));
    polyPoints.push_back(Point(-2,8));
    polyPoints.push_back(Point(0,7));
    polyPoints.push_back(Point(-3,6));
    polyPoints.push_back(Point(-1,5));
    polyPoints.push_back(Point(-3,3));


//    Test case 2.
//    polyPoints.push_back(Point(0,0));
//    polyPoints.push_back(Point(0,1));
//    polyPoints.push_back(Point(3,0));
//    polyPoints.push_back(Point(5,1));
//    polyPoints.push_back(Point(6,3));
//    polyPoints.push_back(Point(5,4));
//    polyPoints.push_back(Point(3,3));
//    polyPoints.push_back(Point(1,4));


    Polygon poly = Polygon(polyPoints,false);

    DCEL dcel(poly);
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

//    Status<HalfEdge> st;
//    HalfEdge::lastReference = *dcel.points[2];
//
//    for (auto p : dcel.points){
//        cout << *p << "\t";
//    }
//    cout << "\n";
//
//    HalfEdge* left = dcel.points[3]->incidentEdge;
//    HalfEdge* right = dcel.points[0]->incidentEdge;
//    cout << (*left < *right) << "\n";

    cout << "Triangulating ";
    dcel.printDCEL();
    Triangulator t= Triangulator(poly);
    t.makeMonotone();




    return 0;
}