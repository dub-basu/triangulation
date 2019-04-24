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


    bool operator< (const LSISegment&) const;
    bool operator> (const LSISegment&) const;
    bool operator != (const LSISegment&) const;
    bool operator <= (const LSISegment&) const;
    LSISegment();
    LSISegment(LineSegment);
    LSISegment& operator=(LSISegment& );
};


#endif //TRIANGULATION_LSISEGMENT_H
