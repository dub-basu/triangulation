#include "DCEL.h"
#include "LSISegment.h"
#include "primitives.h"

void DCEL::addEdge(Point, Point) {

}

void DCEL::printDCEL(){
    for (int i = 0; i < this->faces.size(); i++){
        cout << "Face num " << i << "\n" ;
        HalfEdge* iter = faces[i]->startEdge;
        HalfEdge* start = faces[i]->startEdge;
        cout << "\t" << *(iter->origin);
        iter = iter->next;
        while(iter != start){
            cout << "\t" << *(iter->origin);
            iter = iter->next;
        }
        cout << "\n";
    }


}


void DCEL::addEdge(Vertex* start, Vertex* end) {

    vector<Face*> containingFaces;

    for (auto f : faces){
        bool startPresent = false;
        bool endPresent = false;

        HalfEdge *startEdge = f->startEdge;
        HalfEdge *it = startEdge->next;

        if(startEdge->origin == start){
            startPresent = true;
            // cout << "HERE\n";
        }

        if(startEdge->origin == end){
            endPresent = true;
        }
        while(it != startEdge){
            if(it->origin == start){
                startPresent = true;
            }

            if(it->origin == end){
                endPresent = true;
            }

            it = it->next;
        }

        if(startPresent && endPresent){
            containingFaces.push_back(f);
        }


    }

    if(containingFaces.size() == 0){
        cout << "ERROR : YOU ARE CUTTING OTHER LINES\n";
        return;
    }
    if(containingFaces.size() == 2){
        cout << "ERROR : YOU ARE ADDING AN EXISTING EDGE\n";
        return;
    }
    if(containingFaces.size() >= 2){
        cout << "ONLY GOD CAN SAVE YOU KAUSTUBH\n";
        return;
    }

    Face* oldFace = containingFaces[0];




    HalfEdge *startEdge = new HalfEdge(start);
    //startEdge->end = end;

    HalfEdge *endEdge = new HalfEdge(end);
    //endEdge->end = start;

    // Face *oldFace = start->incidentEdge->incidentFace;
    Face *newFace = new Face();
    this->faces.push_back(newFace);

    HalfEdge *itEdge = oldFace->startEdge;

    do{
        if(itEdge->origin == start){
            endEdge->next = itEdge;
            startEdge->previous = itEdge->previous;
        }
        if(itEdge->origin == end){
            startEdge->next = itEdge;
            endEdge->previous = itEdge->previous;
        }

        itEdge = itEdge->next;
    } while (itEdge != oldFace->startEdge);

    startEdge->incidentFace = newFace;
    endEdge->incidentFace = oldFace;

//    startEdge->next = end->incidentEdge;
//    startEdge->previous = start->incidentEdge->previous;

    startEdge->next->previous = startEdge;
    startEdge->previous->next = startEdge;

//    endEdge->next = start->incidentEdge;
//    endEdge->previous = end->incidentEdge->twin->next->twin;

    endEdge->next->previous = endEdge;
    endEdge->previous->next = endEdge;

    startEdge->twin = endEdge;
    endEdge->twin = startEdge;

    oldFace->startEdge = startEdge;
    newFace->startEdge = endEdge;

    HalfEdge *iter = startEdge->next;
    while (iter != startEdge){
        iter -> incidentFace = startEdge->incidentFace;
        iter = iter->next;
    }

    iter = endEdge->next;
    while(iter != endEdge){
        iter->incidentFace = endEdge->incidentFace;
        iter = iter->next;
    }

}

DCEL::DCEL() {
    // Does nothing.
}

/**
 * Is point a below point p in priority?
 * @param a - Point in question
 * @param p - Reference point
 * @return - True or false.
 */
bool isBelow(Point a,Point p)
{
    return (a.y<p.y || ( fabsl(a.y - p.y)<=1e-6 && a.x > p.x));
}
vertexType getType(Point a,Point b,Point c) {
    long double x1, x2, y1, y2;
    x1 = b.x - a.x;
    y1 = b.y - a.y;

    x2 = c.x - b.x;
    y2 = c.y - b.y;

    long double cross = x1 * y2 - y1 * x2;

    bool c1=isBelow(b,a);
    bool c2=isBelow(b,c);

    if(c1 and c2)
    {
        if (cross > 0.0)
            return vertexType::END;
        else
            return vertexType::MERGE;
    }
    else if(!c1 and !c2)
    {
        if (cross > 0.0)
            return vertexType::START;
        else
            return vertexType::SPLIT;
    }
    return vertexType::REGULAR;
}

DCEL::DCEL(Polygon poly) {
    int numPts = poly.pointList.size();

    Face* inner = new Face();
    Face* outer = new Face();


    Vertex *start = new Vertex(poly.pointList[0]);
    this->points.push_back(start);

    HalfEdge *startEdge = new HalfEdge(start);
    HalfEdge *lastEdge = startEdge;

    start->incidentEdge = startEdge;
    startEdge->incidentFace = inner;

    HalfEdge *startEdgeReverse = new HalfEdge(start);
    HalfEdge *lastEdgeReverse = startEdgeReverse;

    inner->startEdge = startEdge;
    outer->startEdge = startEdgeReverse;
    start->type=getType(poly.pointList[numPts-1],poly.pointList[0],poly.pointList[1]);

    for(int vIndex = 1; vIndex < numPts; vIndex++){
        Vertex *newVertex = new Vertex(poly.pointList[vIndex]);
        newVertex->type=getType(poly.pointList[(numPts+vIndex-1)%numPts],poly.pointList[vIndex],poly.pointList[(vIndex+1)%numPts]);
        this->points.push_back(newVertex);

        HalfEdge *newEdge = new HalfEdge(newVertex);
        HalfEdge *newEdgeReverse = new HalfEdge(newVertex);

        newVertex->incidentEdge = newEdge;

        lastEdge->twin = newEdgeReverse;
        newEdgeReverse->twin = lastEdge;

        newEdge->previous = lastEdge;
        newEdge->incidentFace = inner;
        lastEdge->next = newEdge;

        newEdgeReverse->next = lastEdgeReverse;
        newEdgeReverse->incidentFace = outer;
        lastEdgeReverse->previous = newEdgeReverse;

        lastEdge = newEdge;
        lastEdgeReverse = newEdgeReverse;
    }

    lastEdge->twin = startEdgeReverse;
    startEdgeReverse->twin = lastEdge;


    startEdge->previous = lastEdge;
    lastEdge->next = startEdge;

    startEdgeReverse->next = lastEdgeReverse;
    lastEdgeReverse->previous = startEdgeReverse;

//    Vertex* it = start;
//    do {
//        Vertex* next = it->incidentEdge->next->origin;
//
//        it->incidentEdge->next = next;
//
//        it = next;
//    } while (it != start);

    this->faces.push_back(inner);
    //this->faces.push_back(outer);
}

Vertex::Vertex(Point p) {
    this->x = p.x;
    this->y = p.y;
    this->incidentEdge = NULL;
}

bool Vertex::operator<(const Vertex & rt) {
    //return false;
    if (this->y > rt.y){
        return true;
    }

    if (fabsl(this->y - rt.y) < 0.0001){
        return this->x < rt.x;
    }

    return false;
}

//bool Vertex::operator<(const Vertex * rt) {
//    //return false;
//    if (this->y > rt->y){
//        return true;
//    }
//
//    if (fabsl(this->y - rt->y) < 0.0001){
//        return this->x < rt->x;
//    }
//
//    return false;
//
//}


HalfEdge::HalfEdge(Vertex *start) {
    this->origin = start;
    this->incidentFace = NULL;
    this->next = this;
    this->previous = this;
    this->twin = this;
    this->helper = start;
}

bool HalfEdge::operator<(const HalfEdge &rt) {
    // Making thisSeg
    Point thisStart = Point(this->origin->x, this->origin->y);
    Point thisEnd = Point(this->next->origin->x, this->next->origin->y);

    LineSegment thisSeg(thisStart, thisEnd);
    LSISegment thisLSISeg(thisSeg);

    //Making other seg
    Point rtStart = Point(rt.origin->x, rt.origin->y);
    Point rtEnd = Point(rt.next->origin->x, rt.next->origin->y);
    LineSegment rtSeg(rtStart, rtEnd);
    LSISegment rtLSISeg(rtSeg);

    LSISegment::lastReference = HalfEdge::lastReference;
    return thisLSISeg < rtLSISeg;

}

bool HalfEdge::operator<=(const HalfEdge &rt) {
    Point thisStart = Point(this->origin->x, this->origin->y);
    Point thisEnd = Point(this->next->origin->x, this->next->origin->y);

    LineSegment thisSeg(thisStart, thisEnd);
    LSISegment thisLSISeg(thisSeg);

    //Making other seg
    Point rtStart = Point(rt.origin->x, rt.origin->y);
    Point rtEnd = Point(rt.next->origin->x, rt.next->origin->y);
    LineSegment rtSeg(rtStart, rtEnd);
    LSISegment rtLSISeg(rtSeg);

    LSISegment::lastReference = HalfEdge::lastReference;
    return !(rtLSISeg < thisLSISeg);
}

bool HalfEdge::operator==(const HalfEdge &rt) {
    Point thisStart = Point(this->origin->x, this->origin->y);
    Point thisEnd = Point(this->next->origin->x, this->next->origin->y);

    LineSegment thisSeg(thisStart, thisEnd);
    LSISegment thisLSISeg(thisSeg);
//    cout<<"In equality!!"<<endl;
//    cout<<(*this)<<" "<<rt<<endl;
    //Making other seg
    Point rtStart = Point(rt.origin->x, rt.origin->y);
    Point rtEnd = Point(rt.next->origin->x, rt.next->origin->y);
    LineSegment rtSeg(rtStart, rtEnd);
    LSISegment rtLSISeg(rtSeg);

    LSISegment::lastReference = HalfEdge::lastReference;
    return !(thisLSISeg < rtLSISeg) && !(rtLSISeg < thisLSISeg);
}

bool HalfEdge::operator>(const HalfEdge &rt) {
    Point thisStart = Point(this->origin->x, this->origin->y);
    Point thisEnd = Point(this->next->origin->x, this->next->origin->y);

    LineSegment thisSeg(thisStart, thisEnd);
    LSISegment thisLSISeg(thisSeg);

    //Making other seg
    Point rtStart = Point(rt.origin->x, rt.origin->y);
    Point rtEnd = Point(rt.next->origin->x, rt.next->origin->y);
    LineSegment rtSeg(rtStart, rtEnd);
    LSISegment rtLSISeg(rtSeg);

    LSISegment::lastReference = HalfEdge::lastReference;
    return (rtLSISeg < thisLSISeg) ;
}

bool HalfEdge::operator>=(const HalfEdge &rt) {
    Point thisStart = Point(this->origin->x, this->origin->y);
    Point thisEnd = Point(this->next->origin->x, this->next->origin->y);

    LineSegment thisSeg(thisStart, thisEnd);
    LSISegment thisLSISeg(thisSeg);

    //Making other seg
    Point rtStart = Point(rt.origin->x, rt.origin->y);
    Point rtEnd = Point(rt.next->origin->x, rt.next->origin->y);
    LineSegment rtSeg(rtStart, rtEnd);
    LSISegment rtLSISeg(rtSeg);

    LSISegment::lastReference = HalfEdge::lastReference;
    return !(thisLSISeg < rtLSISeg);
}

bool HalfEdge::operator!=(const HalfEdge &rt) {
    Point thisStart = Point(this->origin->x, this->origin->y);
    Point thisEnd = Point(this->next->origin->x, this->next->origin->y);

    LineSegment thisSeg(thisStart, thisEnd);
    LSISegment thisLSISeg(thisSeg);

    //Making other seg
    Point rtStart = Point(rt.origin->x, rt.origin->y);
    Point rtEnd = Point(rt.next->origin->x, rt.next->origin->y);
    LineSegment rtSeg(rtStart, rtEnd);
    LSISegment rtLSISeg(rtSeg);

    LSISegment::lastReference = HalfEdge::lastReference;
    return !(thisLSISeg == rtLSISeg);
}




std::ostream& operator<<(std::ostream& os, const HalfEdge& halfEdge){
    os  << "HalfEdge starting at " << *halfEdge.origin << " to "
        << *halfEdge.next->origin << "\n";
    return os;
}


Vertex HalfEdge::lastReference = Vertex(NAN_POINT);



//HalfEdge& HalfEdge::operator=(const HalfEdge & he) {
//    this->origin = he.origin;
//    //Vertex* end;
//    this->twin = he.twin;
//    this->incidentFace = he.incidentFace;
//    this->next = he.next;
//    HalfEdge* previous;
//
//    Vertex* helper;
//}
