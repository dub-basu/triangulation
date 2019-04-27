#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

#include "primitives.h"
#include "DCEL.h"
#include "Status.tpp"
#include "Triangulator.h"
#include "TriangulatorGraphix.h"

#define VISUALISE true
#define DEFAULT_FILENAME "../testcases/default_case.txt"

using namespace std;

void init_graphix_class(TriangulatorGraphix* x){
    x->loopie();
}

void get_points_from_file(string filename, vector<Point>& points){
    points.clear();
    ifstream fin;
    fin.open(filename, ios::in);
    string pt_str;
    string comma = ",";
    while(fin >> pt_str){
        pt_str = pt_str.substr(1, pt_str.size() - 2);
        string p1_x = pt_str.substr(0,pt_str.find(comma));
        string p1_y = pt_str.substr(pt_str.find(comma) + 1, pt_str.size());
        Point pt(stold(p1_x), stold(p1_y));
        points.push_back(pt);
    }
    fin.close();
}

int main(int argc, char** argv) {

    std::mutex mtx;
    TriangulatorGraphix* gfx_ptr;
    thread* gfx_thread;
    if(VISUALISE){
        gfx_ptr = new TriangulatorGraphix(mtx);
        gfx_thread = new thread(init_graphix_class, gfx_ptr);
    } else {
        gfx_ptr = NULL;
    }

    vector<Point> polyPoints;

    string filename;
    if(argc > 1){
        filename = argv[1];
        cout << filename << endl;
    } else {
        filename = DEFAULT_FILENAME;
    }
    get_points_from_file(filename, polyPoints);

    cout << "Input Points: " << endl;
    for(auto i: polyPoints){
        cout << i << ", " << endl;
    }
    cout << "------------" << endl;

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
    Triangulator t= Triangulator(poly, gfx_ptr);
    t.makeMonotone();

    if(VISUALISE) gfx_thread -> join();
    return 0;
}
