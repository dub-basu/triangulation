#include "DCEL.h"

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
    HalfEdge *endEdge = new HalfEdge(end);

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

    for(int vIndex = 1; vIndex < numPts; vIndex++){
        Vertex *newVertex = new Vertex(poly.pointList[vIndex]);
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

    this->faces.push_back(inner);
    //this->faces.push_back(outer);
}

Vertex::Vertex(Point p) {
    this->x = p.x;
    this->y = p.y;
    this->incidentEdge = NULL;
}

HalfEdge::HalfEdge(Vertex *start) {
    this->origin = start;
    this->incidentFace = NULL;
    this->next = NULL;
    this->previous = NULL;
    this->twin = NULL;
}
