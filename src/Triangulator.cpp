//
// Created by Abhishek Pandey on 24-04-2019.
//


#include "Triangulator.h"
using namespace std;




    void Triangulator::handleStart(Vertex *v)
    {
        st.insert(*v->incidentEdge);
        cout<<"Set the helper of "<<*v->incidentEdge<<" as "<<*v<<endl;
        v->incidentEdge->helper=v;
    }

    void Triangulator::handleEnd(Vertex *v)
    {
        vertexType temp=v->incidentEdge->twin->next->twin->helper->type;
        HalfEdge *prev=v->incidentEdge->twin->next->twin;
        if(temp==vertexType::MERGE)
        {
            //TODO Add Edge
            cout<<"Added edge b/w "<<*v<<" "<<*prev->helper<<" to make monotone"<<endl;
            tri.addEdge(v,prev->helper);
            if(this -> visualise){
                gfx -> add_edge(*v, *(prev -> helper));
                gfx -> render();
            }
        }
        cout<<"Removing edge "<<*prev<<" from status"<<endl;
        st.remove(*prev);
        st.inorder();cout<<endl;
    }

    void Triangulator::handleSplit(Vertex *v)
    {
        HalfEdge *i=st.searchL(*v->incidentEdge);
        i=i->origin->incidentEdge;
        cout<<"Left to "<<*v<<" is edge "<<*i<<endl;
        //TODO Add Edge
        tri.addEdge(v,i->helper);
        if(this -> visualise){
            gfx -> add_edge(*v, *(i -> helper));
            gfx -> render();
        }
        cout<<"Added edge b/w "<<*v<<" "<<*i->helper<<endl;
        i->helper=v;
        cout<<"Inserted edge "<<*v->incidentEdge<<endl;
        st.insert(*v->incidentEdge);
        v->incidentEdge->helper=v;
        cout<<"Set "<<*i<<" helper as "<<*v<<" and "<<v->incidentEdge<<" helper as"<<v<<endl;
    }

    void Triangulator::handleMerge(Vertex *v)
    {
        vertexType temp;
        cout<<"V="<<*v<<endl;
        cout<<"Temp="<<(*v->incidentEdge->twin->next->twin->helper)<<endl;
        HalfEdge *prev=v->incidentEdge->twin->next->twin;
        temp=prev->helper->type;
        if(temp==vertexType::MERGE)
        {
            //TODO Add Edge
            tri.addEdge(v,prev->helper);
            if(this -> visualise){
                gfx -> add_edge(*v, *(prev -> helper));
                gfx -> render();
            }
            cout<<"Added edge b/w "<<(*v)<<" "<<(*prev->helper)<<endl;
        }
        cout<<"Removing from status rn "<<(*prev)<<endl;
        st.inorder();cout<<endl;
        st.remove(*prev);
        cout<<"Removed from status "<<endl;
        st.inorder();cout<<endl;
        HalfEdge *i=st.searchL(*v->incidentEdge);
        i=i->origin->incidentEdge;
        cout<<"Left edge of "<<*v<<" is "<<*i<<endl;
        if(i->helper->type == vertexType::MERGE)
        {
            //TODO Add Edge
            tri.addEdge(v,i->helper);
            if(this -> visualise){
                gfx -> add_edge(*v, *(i -> helper));
                gfx -> render();
            }

            cout<<"Added edge b/w "<<*v<<" "<<*i->helper<<endl;
        }
        i->helper=v;
        cout<<"Set "<<*i<<" helper as "<<*i->helper<<endl;
    }

    bool Triangulator::isRight(Vertex *prevV, Vertex *v)
    {
        //cout<<*prevV<<" "<<*v<<" VIA?? ";
        if(fabsl(prevV->y-v->y)<=1e-6)
        {
            //cout<<"Via C1"<<endl;
            if( (prevV->x) < (v->x))
                return true;
            return false;
        }
        else if(prevV->y>v->y)
            return true;
        //cout<<"Via C3"<<endl;
        return false;
    }
    void Triangulator::handleRegular(Vertex *v)
    {
        HalfEdge *i=v->incidentEdge->twin->next->twin; //Ei-1
        Vertex *prevV=i->origin;
        cout<<"Prev edge="<<*i<<endl;
        if(isRight(prevV,v))
        {
            cout<<"Poly to Right "<<" helper of this edge"<<*i<<" is "<<*i->helper<<endl;
            if(i->helper->type==vertexType::MERGE)
            {
                //TODO Add Edge
                tri.addEdge(v,i->helper);
                if(this -> visualise){
                    gfx -> add_edge(*v, *(i -> helper));
                    gfx -> render();
                }

                cout<<"Added edge b/w"<<*v<<" "<<*i->helper<<endl;
            }
            st.remove(*i);
            st.insert(*v->incidentEdge);
            cout<<"Removed "<<*i<<" inserted "<<*v->incidentEdge<<endl;
            st.inorder();cout<<endl;
            v->incidentEdge->helper=v;
            cout<<"Set "<<*v->incidentEdge<<" helper to "<<*v<<endl;
        }
        else
        {
            cout<<"Poly to Left"<<endl;
            HalfEdge *i = (st.searchL(*v->incidentEdge));
            i=i->origin->incidentEdge;
            cout<<"Left to "<<*v<<" is edge "<<*i<<endl;
            if(i->helper->type==vertexType::MERGE)
            {
                //TODO Add Edge
                tri.addEdge(v,i->helper);
                if(this -> visualise){
                    gfx -> add_edge(*v, *(i-> helper));
                    gfx -> render();
                }
                cout<<"Added edge b/w "<<*v<<" "<<*i->helper<<endl;
            }
            i->helper=v;
            cout<<"Helper of "<<*i->helper<<" = "<<*v<<endl;
        }

    }


    //TODO : Implement & Test chains.
    bool Triangulator::checkSameChain(Vertex *v1, Vertex*v2, vector<Vertex *>&lChain,vector<Vertex *> rChain)
    {
        int sign1,sign2;

        for(auto i:lChain)
        {
            if(i==v1)
                sign1=1;
            if(i==v2)
                sign2=1;
        }

        for(auto i:rChain)
        {
            if(i==v1)
                sign1=2;
            if(i==v2)
                sign2=2;
        }

        return sign1==sign2;

//        int sign1,sign2;
//
//        Vertex *prevV1 = v1->incidentEdge->twin->next->twin->origin;
//        Vertex *prevV2 = v2->incidentEdge->twin->next->twin->origin;
//
//        if(fabsl(prevV1->y-v1->y)<=1e-6)
//            sign1=0;
//        else if(prevV1->y<v1->y)
//            sign1=0;
//        else sign1=-1;
//
//        if(fabsl(prevV2->y-v2->y)<=1e-6)
//            sign2=0;
//        else if(prevV2->y<v2->y)
//            sign2=0;
//        else sign2=-1;
//
//        return sign1==sign2;
    }



    void Triangulator::triangulateMonotonePolygon(Face *f)
    {
        vector <Vertex *> s;
        EventQueue<Vertex*> l;
        //cout<<P.pointList.size()<<" is size when in func"<<endl;

        DCEL tri2=tri;
        /**Experimental**/
        HalfEdge *e=f->startEdge;
        l.insert(e->origin);
        //cout<<"Inserted "<<(*e->origin)<<" ";
        HalfEdge *temp=f->startEdge;
        e=e->next;
        int n=1;
        Point maxP=Point(-1e9,-1e9),minP=Point(1e9,1e9);
        HalfEdge *minE,*maxE;
        while(e!=temp)
        {
            l.insert(e->origin);
            //cout<<"Inserted "<<(*e->origin)<<" ";
            e=e->next;
            ++n;
            if(Point(e->origin->x,e->origin->y).y<minP.y or (fabsl(e->origin->y-minP.y<=1e-6 and e->origin->x>minP.x)))
            {
                minP=*e->origin;
                minE=e;
            }
            if(maxP.y<e->origin->y or (fabsl(maxP.y-e->origin->y)<=1e-6 and maxP.x<e->origin->x))
            {
                maxP=*e->origin;
                maxE=e;
            }
        }
        cout<<"N="<<n<<" l.size()="<<l.size()<<endl;

        cout<<maxP<<" "<<minP<<endl;

        vector<Vertex *>lChain,rChain;


        e=maxE;

        do {
            lChain.push_back(e->origin);
            e=e->next;
        }while(e!=minE);

        do
        {
            rChain.push_back(e->origin);
            e=e->next;
        }while(e!=maxE);

        //cout<<lChain.size()<<" "<<rChain.size()<<endl;

        //cout<<lChain.size()<<" "<<rChain.size()<<endl;
        if(lChain.size()+rChain.size()<=3)return;

        cout<<"LCHAIN: ";
        for(auto i:lChain)cout<<*i<<" ";cout<<endl;

        cout<<"RCHAIN: ";
        for(auto i: rChain)cout<<*i<<" ";cout<<endl;


        /**End of Experimental**/

        Vertex *u1,*u2,*uj,*prevu;
        u1=l.extractMin();
        if(this -> visualise){
            gfx -> update_event(*u1);
            gfx -> render();
        }

        u2=l.extractMin();
        if(this -> visualise){
            gfx -> update_event(*u2);
            gfx -> render();
        }

        s.push_back(u1);
        s.push_back(u2);
        prevu=u2;
        for(int j=2;j<n-1;j++)
        {
//            cout<<"j="<<j<<endl;
            uj=l.extractMin();
            if(this -> visualise){
                gfx -> update_event(*uj);
                gfx -> render();
            }
           
            cout<<l.size()<<endl;
            cout<<"Uj="<<*uj<<" Top="<<*s.back()<<" Same chain? "<<checkSameChain(uj,s.back(),lChain,rChain)<<endl;
            if(!checkSameChain(uj,s.back(),lChain,rChain))
            {
                while(!s.empty())
                {
                    if(s.size()>1 and *uj!=*s.back())
                    {
                        cout<<*uj;
                        cout<<" S.back()=";
                        cout<<*s.back()<<endl;
                        cout<<"NOT Same Chain, "<<*uj<<" "<<*s.back()<<" s.size()="<<s.size()<<endl;

                        if(*uj->incidentEdge->next->origin!= *s.back() and *uj->incidentEdge->twin->next->twin->origin !=*s.back())
                        {
                            cout<<"Actually Added!!"<<endl;
                            //TODO Add Edge
                            tri.addEdge(uj,s.back());
                            if(this -> visualise){
                                gfx -> add_edge(*uj, *(s.back()));
                                gfx -> render();
                            }


                        }

//                        cout<<"Added"<<endl;
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
                cout<<"Last Popped="<<*lastPopped<<endl;
                bool diagonalInside=true;
                int ct=0;
                while(s.size()>0 and diagonalInside)
                {
                    Point mid= Point((uj->x+s.back()->x)/2,(uj->y+s.back()->y)/2);
                    bool isInsideFace=false;
                    bool LineIsInside=true;
                    for(auto j:tri.faces)
                    {
                        vector<Point> points;
                        Face *f=j;
                        HalfEdge *e=f->startEdge,*temp=e;
                        do
                        {
                            points.push_back(Point(e->origin->x,e->origin->y));
                            e=e->next;
                        }while(temp!=e);
                        Polygon P=Polygon(points);
                        isInsideFace |=P.pointInside(mid);
                        LineIsInside&=P.LineInside(Point(uj->x,uj->y),Point(s.back()->x,s.back()->y));
                        cout<<"Point Is in? "<<P.pointInside(mid)<<"&& LineIsIN? "<<P.LineInside(Point(uj->x,uj->y),Point(s.back()->x,s.back()->y))<<" ";
                    }
                    diagonalInside = isInsideFace && LineIsInside ;
                    //cout<<"SS, added edge b/w "<<*uj<<" and "<<*s.back()<<" is in? "<<diagonalInside<<" s.size()="<<s.size()<<endl;
                    if(!diagonalInside)break;
                    lastPopped=s.back();

                    if(*uj->incidentEdge->next->origin!= *s.back() and *uj->incidentEdge->twin->next->twin->origin !=*s.back())
                    {
                        cout<<"Actually Added!!"<<endl;
                        //TODO Add Edge
                        tri.addEdge(uj,s.back());
                        if(this -> visualise){
                            gfx -> add_edge(*uj, *(s.back()));
                            gfx -> render();
                        }
                    }

                    s.pop_back();
                }
                s.push_back(lastPopped);
                s.push_back(uj);
            }
            cout<<"Stack has : ";
            for(auto i:s)cout<<*i<<" ";cout<<endl;
            prevu=uj;
            //tri.printDCEL();
        }
        assert(l.size()==1);
        Vertex *un=l.extractMin();
        s.pop_back();
        cout<<"s.size()="<<s.size()<<endl;
        while(s.size()>1)
        {
            cout<<"Adding edge b/w "<<(*un)<<" "<<(*s.back())<<endl;
            //TODO Add Edge
            tri.addEdge(un,s.back());
            if(this -> visualise){
                gfx -> add_edge(*un, *(s.back()));
                gfx -> render();
            }

            s.pop_back();
        }
        s.pop_back();
        assert(l.size()==0);

        //tri.printDCEL();


    }


Triangulator::Triangulator(Polygon a, TriangulatorGraphix* gfx_ptr)
    {

        if(gfx_ptr != NULL){
            this -> visualise = true;
            this -> gfx = gfx_ptr;
        } else {
            this -> visualise = false;
        }

        this->P=Polygon(a.pointList);
        if(this -> visualise){
            draw_polygon(this -> P);
            std::cout << "\nadded" << std::endl;
            gfx -> render();
        }
        //cout<<P.pointList.size()<<" is size of pointlist!!"<<endl;
        //for(auto i:P.pointList)cout<<i<<" ";cout<<endl;
        tri=DCEL(P);
        for(auto i:tri.points)
        {
            pq.insert(i);
            //cout<<pq.size()<<" inserted "<<(*i)<<endl;
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

    void Triangulator::makeMonotone ()
    {
        //Event Queue done.
        while(pq.size()>0)
        {
            Vertex *i=pq.extractMin();
            if(this -> visualise){
                gfx -> update_event(*i);
                gfx -> render();
            }
            cout<<"Handling "<<(*i)<<" in the queue, of type "<<" ";

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

            HalfEdge::lastReference = *i;
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
                handleRegular(i);
            }
            else
                assert(false);
        }
        cout << "Y monotone done :" << tri.faces.size() << " monotones present\n" ;
        tri.printDCEL();

        vector <Face*> facesToIterate= tri.faces;
        for(int i=0;i<facesToIterate.size();i++)
        {
            cout<<"Triangulating face "<<i<<endl;

            triangulateMonotonePolygon(tri.faces[i]);
        }

        tri.printDCEL();

    }

void Triangulator::draw_polygon(Polygon P){
    for(int i=0;i<P.pointList.size()-1;i++){
        gfx -> add_edge(P.pointList[i], P.pointList[i+1]);
        // std::cout << "\n\n line added \n\n";
        // std::cout << P.pointList[i];
        // std::cout << "point" << std::endl;
    }
    gfx -> add_edge(P.pointList[P.pointList.size()-1], P.pointList[0]);
}
