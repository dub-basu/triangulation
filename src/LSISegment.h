//
// Created by kaustubh0x77 on 24/4/19.
//

#include "primitives.h"
#include "DCEL.h"

#ifndef TRIANGULATION_LSISEGMENT_H
#define TRIANGULATION_LSISEGMENT_H

class LSISegment: public LineSegment{
private:
public:
    static Vertex lastReference;

    /**
     * Standard operator < for the class
     * @return
     */
    bool operator< (const LSISegment&) const;
    /**
     * Standard operator > for the class
     * @return
     */
    bool operator> (const LSISegment&) const;
    /**
     * Standard operator != for the class
     * @return
     */
    bool operator != (const LSISegment&) const;
    /**
     * Standard operator <= for the class
     * @return
     */
    bool operator <= (const LSISegment&) const;
    /**
     * Default constructor for the class
     */
    LSISegment();
    /**
     * Parameterised constructor for the class
     */
    LSISegment(LineSegment);
    /**
     * Standard operator = for the class
     * @return
     */
    LSISegment& operator=(LSISegment& );
};


#endif //TRIANGULATION_LSISEGMENT_H
