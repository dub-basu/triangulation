//
// Created by Abhishek Pandey on 26-04-2019.
//

#ifndef TRIANGULATION_TRIANGULATOR_H
#define TRIANGULATION_TRIANGULATOR_H
#include <iostream>
#include <stack>
#include "Polygon.h"
#include "DCEL.h"
#include "EventQueue.tpp"
#include "Status.tpp"
#include <assert.h>
#include "TriangulatorGraphix.h"

/**
 * Triangulator class has functionalities to triangualate a given Y monotone polygon.
 *
 */



class Triangulator
{
    DCEL tri; //!< This DCEL stores the information of Polygon, its faces and also the final triangulation.
    Polygon P; //!< The initial Polygon P which is to be triangulated
    EventQueue<Vertex*> pq; //!< Event Queue storing the points in order visited by Sweep Line
    Status <HalfEdge> st; //!< Status for storing the edges and getting Left and Right neighbours
    bool visualise; //!< Flag to determine whether visualisations are turned on
    TriangulatorGraphix* gfx;/**< Pointer to graphix object. */

    /**
     * Handles START vertices
     * @param v Vertex to handle passed by reference.
     */
    void handleStart(Vertex *v);
    /**
     * Handles END vertices
     * @param v Vertex to handle passed by reference.
     */
    void handleEnd(Vertex *v);
    /**
     * Handles SPLIT vertices
     * @param v Vertex to handle passed by reference.
     */
    void handleSplit(Vertex *v);
    /**
     * Handles MERGE vertices
     * @param v Vertex to handle passed by reference.
     */
    void handleMerge(Vertex *v);
    /**
     * Tells if Polygon is to the right of edge defined by prevV and v
     * @param v Vertices v to handle passed by reference.
     * @param prevV Vertex just before vertex v
     * @return A boolean value true or false depending on if the Polygon's interior is towards right or not.
     */
    bool isRight(Vertex *prevV, Vertex *v);
    /**
     * Handles REGULAR vertices
     * @param v Vertex to handle passed by reference.
     *
     */
    void handleRegular(Vertex *v);
    /**
     * Checks if vertices lie in same chain or not.
     * @param v1 First vertex to check
     * @param v2 Second vertex to check
     * @param lChain Left chain passed by reference
     * @param rChain Right chain passed by reference
     * @return Returns true or false depending on if points are in same chain
     */
    bool checkSameChain(Vertex *v1, Vertex*v2, vector<Vertex *>&lChain,vector<Vertex *> rChain);
    /**
     * Triangulates the Y-monotone Polygon passed
     * @param f Face of the polygon too triangulate
     */
    void triangulateMonotonePolygon(Face *f);

    /**
     * Utility function to draw the iterate over the
     * edges of the polygon and draw them
    */
    void draw_polygon(Polygon);

public:
    /**
     * Constructor of the class. Makes DCEL given a Polygon a.
     * @param a Polygon to store in DCEL
     */
    Triangulator (Polygon a, TriangulatorGraphix* gfx = NULL);
    /**
     * Given a polygon, decomposes it into Y-Monotone Polygons
     */
    void makeMonotone ();

};
#endif //TRIANGULATION_TRIANGULATOR_H
