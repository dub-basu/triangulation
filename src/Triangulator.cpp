//
// Created by Abhishek Pandey on 24-04-2019.
//

#include <iostream>
#include <stack>
#include "Polygon.h"
#include "DCEL.h"
#include "EventQueue.tpp"

using namespace std;

class Triangulator
{
    DCEL tri;
    Polygon P;
    EventQueue<Vertex*> pq;
    Status <HalfEdge*> st;

    void handleStart(Vertex *v)
    {
        st.insert(v->incidentEdge);
        v->incidentEdge->helper=v;
    }

    void handleEnd(Vertex *v)
    {
        vertexType temp=v->incidentEdge->twin->next->twin->helper->type;
        if(temp==vertexType::MERGE)
        {
            tri.addEdge(v,v->incidentEdge->twin->next->twin->helper);
        }
        st.remove(v->incidentEdge->twin->next->twin);
    }

    void handleSplit(Vertex *v)
    {
        HalfEdge *i=st.searchL(v);
        tri.addEdge(v,i->helper);
        i->helper=v;
        st.insert(v->incidentEdge);
        v->incidentEdge->helper=v;
    }

    void handleMerge(Vertex *v)
    {
        vertexType temp=v->incidentEdge->twin->next->twin->helper->type;
        if(temp==vertexType::MERGE)
        {
            tri.addEdge(v,v->incidentEdge->twin->next->twin->helper);
        }
        st.remove(v->incidentEdge->twin->next->twin);
        HalfEdge *i=st.searchL(v);
        if(i->helper->type == vertexType::MERGE)
        {
            tri.addEdge(v,i->helper);
        }
        i->helper=v;
    }

    bool isRight(Vertex *prevV, Vertex *v)
    {
        if(fabsl(prevV->y-v->y)<=1e-6)
        {
            if( (prevV->x) < (v->x))
                return true;
            return false;
        }
        else if(prevV->y>v->y)
            return true;
        return false;
    }
    void handleRegular(Vertex *v)
    {
        HalfEdge *i=v->incidentEdge->twin->next->twin; //Ei-1
        Vertex *prevV=i->origin;
        if(isRight(prevV,v))
        {
            if(i->helper->type==vertexType::MERGE)
            {
                tri.addEdge(v,i->helper);
            }
            st.remove(i);
            st.insert(v->incidentEdge);
            v->incidentEdge->helper=v;
        }
        else
        {
            HalfEdge *i=searchL(v);
            if(i->helper->type==vertexType::MERGE)
            {
                tri.addEdge(v,i->helper);
            }
            i->helper=v;
        }

    }

    void makeMonotone ()
    {
        //Event Queue done.

        while(pq.size()>0)
        {
            Vertex* i=pq.extractMin();
            if(i->type==vertexType::START)
            {
                handleStart(i);
            }
            else if(i->type==vertexType::END)
            {
                handleEnd(i);
            }
            else if(i->type==vertexType::SPLIT)
            {
                handleSplit(i);
            }
            else if(i->type==vertexType::MERGE)
            {
                handleMerge(i);
            }
            else if(i->type==vertexType::REGULAR)
            {
                handleRegular(i)
            }
        }

    }
    //TODO : Implement & Test chains.
    bool checkSameChain(Vertex *v1, Vertex*v2)
    {
        int sign1,sign2;

        Vertex *prevV1 = v1->incidentEdge->twin->next->twin->origin;
        Vertex *prevV2 = v2->incidentEdge->twin->next->twin->origin;

        if(fabsl(prevV1.y-v1.y)<=1e-6)
            sign1=0;
        else if(prevV1.y<v1.y)
            sign1=0;
        else sign1=-1;

        if(fabsl(prevV2.y-v2.y)<=1e-6)
            sign2=0;
        else if(prevV2.y<v2.y)
            sign2=0;
        else sign2=-1;

        return sign1==sign2;
    }



    void triangulateMonotonePolygon(Face *f)
    {
        vector <Vertex *> s;
        EventQueue<Vertex *> l;

        /**Experimental**/
        HalfEdge *e=f->startEdge;
        l.insert(e->origin);
        HalfEdge *temp=e;
        e=e->next;
        int n=1;
        while(e!=temp)
        {
            l.insert(e->origin);
            e=e->next;
            ++n;
        }
        /**End of Experimental**/

        Vertex *u1,*u2,*uj,*prevu;
        u1=l.extractMin();
        u2=l.extractMin();
        s.push_back(u1);
        s.push_back(u2);
        prevu=u2;
        for(int j=0;j<n-1;j++)
        {
            uj=l.extractMin();
            if(checkSameChain(uj,s.back()))
            {
                while(!s.empty())
                {
                    if(s.size()>1)
                    {
                        tri.addEdge(uj,s.back());
                    }
                    s.pop_back();
                }
                s.push_back(prevu);
                s.push_back(uj);

            }
            else
            {
                Vertex *lastPopped=s.back();
                s.pop_back();
                bool diagonalInside=true;
                int ct=0;
                while(s.size()>0 and diagonalInside)
                {
                    Point mid= Point((uj->x+s.back()->x)/2,(uj->y+s.back()->y)/2);
                    diagonalInside= P.pointInside(mid) && P.LineInside(Point(uj->x,uj->y),Point(s.back()->x,s.back()->y));

                    if(!diagonalInside)break;
                    lastPopped=s.back();
                    tri.addEdge(uj,s.back());
                    s.pop_back();
                }
                s.push_back(lastPopped);
                s.push_back(uj);
            }

            prevu=uj;
        }

        Vertex *un=l.extractMin();
        st.pop();
        while(st.size()>1)
        {
            tri.addEdge(un,st.top());
            st.pop();
        }


    }

public:
    Triangulator (Polygon a)
    {
        Polygon P=Polygon(a.pointList);
        tri=DCEL(P);
        for(auto i:tri.points)
        {
            pq.insert(i);
            cout<<i->x<<" "<<i->y<<" ";
            switch(i->type)
            {
                case vertexType::REGULAR:
                    cout<<"Regular\n";
                    break;
                case vertexType::END:
                    cout<<"End\n";
                    break;
                case vertexType ::MERGE:
                    cout<<"Merge\n";
                    break;
                case vertexType ::SPLIT:
                    cout<<"SPLIT\n";
                    break;
                case vertexType ::START:
                    cout<<"START\n";
                    break;
                default :
                    cout<<"ERROR\n";
                    break;
            }
        }

    }

};
