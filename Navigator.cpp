//
//  Navigator.cpp
//  New Project 4
//
//  Created by Ishan Sharma on 3/11/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "provided.h"
#include "MyMap.h"
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include "suport.h"
using namespace std;


string direction(double angle);

string direction(double angle){
    if (angle>= 0 && angle<=22.5){
        return "east";
    }
    else if ( angle > 22.5 && angle <=67.5){
        return "northeast";
    }
    else if ( angle > 67.5 && angle <=112.5){
        return "north";
    }
    else if ( angle > 112.5 && angle <=157.5){
        return "northwest";
    }
    else if ( angle > 157.5 && angle <=202.5){
        return "west";
    }
    else if ( angle > 202.5 && angle <=247.5){
        return "southwest";
    }
    else if ( angle > 247.5 && angle <=292.5){
        return "south";
    }
    else if ( angle > 292.5 && angle <=337.5){
        return "southeast";
    }
    else if ( angle > 337.5 && angle <=360){
        return "east";
    }
    else
        return "north";
}

void navMapper(MyMap<PrioGeoCord, PrioGeoCord> &cf, vector<NavSegment> & dir, PrioGeoCord end, PrioGeoCord start){
    PrioGeoCord* prevPoint;
    PrioGeoCord current=end;
    
    const GeoCoord p;
    const GeoCoord c;
    
    prevPoint=cf.find(current);
    
    while((*prevPoint).name!="ISHANSHARMA,HYRANA,SONIPAT"){
        
        GeoSegment geos1;
        geos1.start=(*prevPoint).geo;
        geos1.end=current.geo;
        double a2=angleOfLine(geos1);
        string as2= direction(a2);
        double d= distanceEarthMiles((*prevPoint).geo, current.geo);
        
        NavSegment navp(as2, current.name, d, geos1);
        dir.push_back(navp);
        
        if((*prevPoint).name != current.name){
            GeoSegment gs1, gs2;
            gs2.start=(*prevPoint).geo;
            gs2.end= current.geo;
            PrioGeoCord*pp=cf.find(*prevPoint);
            gs1.start=(*pp).geo;
            gs1.end=(*prevPoint).geo;
            double ang1=angleBetween2Lines(gs1, gs2);
            string angs1;
            if(ang1<180)
                angs1="left";
            else if (ang1>=180)
                angs1="right";
            NavSegment navt (angs1, current.name);
            dir.push_back(navt);
        }
    
        current=(*prevPoint);
        prevPoint=cf.find(*prevPoint);
    }
    
    reverse(dir.begin(), dir.end());
}

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;

private:
    AttractionMapper m_am;
    SegmentMapper m_sm;
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    MapLoader ml;
    if(!ml.load(mapFile)){
        return false;
    }
    
    m_am.init(ml);
    m_sm.init(ml);
    
    return true;  // This compiles, but may not be correct
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    MyMap<PrioGeoCord, PrioGeoCord> cameFrom;
    MyMap<PrioGeoCord, double> distanceSoFar;
    
    priority_queue<PrioGeoCord> geoPrioQ;
    
    if(directions.size()>0){
        directions.clear(); //DOES THIS WORK
    }
    
    GeoCoord startAttrac;
    GeoCoord endAttrac;
    
    if ( !m_am.getGeoCoord(start, startAttrac)){
        return NAV_BAD_SOURCE;
    }
    
    if ( !m_am.getGeoCoord(end, endAttrac)){
        return NAV_BAD_DESTINATION;
    }

    PrioGeoCord ed;
    ed.geo=endAttrac;
    ed.priority=0;
    
    PrioGeoCord st;
    st.geo=startAttrac;
    st.priority=0;

    PrioGeoCord null;                       // This node is there to have a stopping condition
    null.name="ISHANSHARMA,HYRANA,SONIPAT";  // RANDOM string that indicates reaching the end

    vector<StreetSegment> streets;
    streets = m_sm.getSegments(startAttrac);
    
    st.name=streets[0].streetName;
    
    geoPrioQ.push(st);

    cameFrom.associate(st, null);
    distanceSoFar.associate(st, 0);
    
    while(!geoPrioQ.empty()){
        PrioGeoCord curr = geoPrioQ.top();
        geoPrioQ.pop();
        
        streets = m_sm.getSegments(curr.geo);
        
        for (int i=0; i<streets.size(); i++){
            for(int j=0; j<streets[i].attractions.size(); j++){
                if(streets[i].attractions[j].geocoordinates==endAttrac){
                    ed.name=streets[i].streetName;
                    curr.name=streets[i].streetName;
                    cameFrom.associate(ed, curr);
                    navMapper(cameFrom, directions, ed, st);
                    return NAV_SUCCESS;
                }
            }
        }

        for( int i=0; i<streets.size(); i++){
            PrioGeoCord op1;
            PrioGeoCord op2;
            
            op1.geo=streets[i].segment.start;
            op2.geo=streets[i].segment.end;
            
            op1.name=streets[i].streetName;
            op2.name=streets[i].streetName;
            
            double newdist= *(distanceSoFar.find(curr)) + distanceEarthMiles(curr.geo, op1.geo);
            double*p=distanceSoFar.find(op1);
            if (!p || newdist < (*p)){
                distanceSoFar.associate(op1, newdist);
                double prio = newdist + distanceEarthMiles(endAttrac, op1.geo);
                op1.priority=prio;
                geoPrioQ.push(op1);
                cameFrom.associate(op1, curr);
            }
            
            double newdist2= *(distanceSoFar.find(curr)) + distanceEarthMiles(curr.geo, op2.geo);
            double*p2=distanceSoFar.find(op2);
            if (!p2 || newdist2 < (*p2)){
                distanceSoFar.associate(op2, newdist2);
                double prio2 = newdist2 + distanceEarthMiles(endAttrac, op2.geo);
                op2.priority=prio2;
                geoPrioQ.push(op2);
                cameFrom.associate(op2, curr);
            }
            
        }
    }
    
    return NAV_NO_ROUTE;  // This compiles, but may not be correct
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
