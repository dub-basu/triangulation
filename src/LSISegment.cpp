//
// Created by kaustubh0x77 on 24/4/19.
//

#include "primitives.h"
#include "LSISegment.h"

#define DELTA 0.00005
#define abs fabsl

LSISegment& LSISegment::operator=(LSISegment& a) {
    if(a.start_pt().is_nan() || a.end_pt().is_nan()) return(a);
    // this->ls = a.ls;
    this->start_point = a.start_pt();
    this->end_point = a.end_pt();
    return *this;
}


LSISegment::LSISegment(){

}


LSISegment::LSISegment(LineSegment l){
    this -> start_point = l.start_pt();
    this -> end_point = l.end_pt();
}

bool LSISegment::operator<(const LSISegment& lsi) const {
    Point this_upper = this->start_pt(), this_lower = this->end_pt();
    Point lsi_upper = lsi.start_pt(), lsi_lower = lsi.end_pt();

    // const LSISegment debug = LSISegment(LineSegment(Point(1,9),Point(3,8)));
    //cout<<"Comparing "<<(*this)<<" "<<lsi<<endl;
    if((this_upper.y < this_lower.y) || ( abs(this_upper.y - this_lower.y)<ERROR && this_upper.x >= this_lower.x)){
        Point temp = this_upper;
        this_upper = this_lower;
        this_lower = temp;
    }
    if((lsi_upper.y < lsi_lower.y) || (abs(lsi_upper.y - lsi_lower.y)<ERROR && lsi_upper.x >= lsi_lower.x)){
        Point temp = lsi_upper;
        lsi_upper = lsi_lower;
        lsi_lower = temp;
    }

    if ((lastReference == this_upper || lastReference == this_lower) &&
        (lastReference == lsi_upper  || lastReference == lsi_lower) ){
        //cout << "\n\n\n\nSHOULDNT PRINT\n\n\n\n";
        if (lastReference == this_upper && lastReference == lsi_upper){
            Point comp = Point(lastReference.x, lastReference.y - DELTA);

            bool toReturn = this->horizontal_projection(comp).x
                            < lsi.horizontal_projection(comp).x;
            //cout << "1."<< toReturn << "\n";
            return toReturn;
        }
        if (lastReference == this_upper && lastReference == lsi_lower){
//            cout << true << "\n";
            bool toReturn = true;
            //cout << "2."<< toReturn << "\n";

            return true;
        }
        if (lastReference == this_lower && lastReference == lsi_lower){
            //cout << "LL\n";
            Point comp = Point(lastReference.x, lastReference.y + DELTA);

            bool toReturn = this->horizontal_projection(comp).x
                            < lsi.horizontal_projection(comp).x;
//            cout << toReturn << "\n";
               //cout << "3."<< toReturn << "\n";

            return toReturn;
        }
        if (lastReference == this_lower && lastReference == lsi_upper){
//            cout << false << "\n";
               //cout << "4."<< false << "\n";

            return false;
        }

    }
    else if(lastReference == this_lower || lastReference == lsi_lower){
//        if (lastReference == Point(1,6)){ //this_lower == Point(1,6) || lsi_lower == Point(1,6)){
//            //cout << *this << " < " << lsi << "@ " << lastReference <<" = ";
//        }
        Point comp;
        if(this->contains_point(lastReference) && lsi.contains_point(lastReference)){
            comp = Point(lastReference.x, lastReference.y + DELTA);
        }
        else {
            comp = lastReference;
        }

        bool toReturn = this->horizontal_projection(comp).x
                        < lsi.horizontal_projection(comp).x;
        //if (lastReference == Point(1,6)){
        //    cout << toReturn << "\n";
        //}

       //cout << "5. Verdict="<< toReturn << "\n";
       //cout<<"Last Ref:"<<lastReference<<endl;

        return toReturn;
    }
    else if(lastReference == this_upper || lastReference == lsi_upper){
        Point comp;
        if(this->contains_point(lastReference) && lsi.contains_point(lastReference)){
            comp = Point(lastReference.x, lastReference.y - DELTA);
            //    cout << "A" ;
        }
        else {
            comp = lastReference;
            //    cout << "B";

        }
        bool toReturn = this->horizontal_projection(comp).x
                        < lsi.horizontal_projection(comp).x;
        //cout << "6."<< toReturn;// << "\n";
//        cout <<"\t"<<this->horizontal_projection(comp).x << " < "
//             << lsi.horizontal_projection(comp).x << "\n";
        return toReturn;
    }
    else  {
        // Only in case of ordering event point
        Point comp = Point(lastReference.x, lastReference.y);

        bool toReturn = this->horizontal_projection(comp).x
                        < lsi.horizontal_projection(comp).x;
        //cout << "7."<< toReturn << "\n";

        return toReturn;
    }
}

Vertex LSISegment::lastReference = Vertex(NAN_POINT);
