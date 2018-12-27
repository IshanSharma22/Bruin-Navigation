//
//  suport.cpp
//  New Project 4
//
//  Created by Ishan Sharma on 3/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "suport.h"

bool operator==(GeoCoord& a, const GeoCoord& b){
    if (a.latitude==b.latitude && a.longitude==b.longitude)
        return true;
    else
        return false;
}

bool operator>=(GeoCoord& a, const GeoCoord& b){
    if(a.longitude==b.longitude){
        if(a.latitude>b.latitude)
            return true;
        else
            return false;
    }
    
    if(a.longitude>b.longitude)
        return true;
    else
        return false;
}

bool operator<=(GeoCoord& a, const GeoCoord& b){
    if(a.longitude==b.longitude){
        if(a.latitude<b.latitude)
            return true;
        else
            return false;
    }
    
    if(a.longitude<b.longitude)
        return true;
    else
        return false;
}

//----------------------------------------------------------//

bool operator==(PrioGeoCord& a, const PrioGeoCord& b){
    if (a.geo.latitude==b.geo.latitude && a.geo.longitude==b.geo.longitude)
        return true;
    else
        return false;
}

bool operator>=(PrioGeoCord& a, const PrioGeoCord& b){
    if(a.geo.longitude==b.geo.longitude){
        if(a.geo.latitude>b.geo.latitude)
            return true;
        else
            return false;
    }
    
    if(a.geo.longitude>b.geo.longitude)
        return true;
    else
        return false;
}

bool operator<=(PrioGeoCord& a, const PrioGeoCord& b){
    if(a.geo.longitude==b.geo.longitude){
        if(a.geo.latitude<b.geo.latitude)
            return true;
        else
            return false;
    }
    
    if(a.geo.longitude<b.geo.longitude)
        return true;
    else
        return false;
}


//----------------------------------------------------------//
bool operator<(const PrioGeoCord& a, const PrioGeoCord& b){
    if(a.priority>b.priority)
        return true;
    else
        return false;
}

//----------------------------------------------------------//
bool operator!=(const GeoCoord& a, GeoCoord& b){
    if(a.latitude!=b.latitude && a.longitude!= b.longitude)
        return true;
    else
        return false;
}

//----------------------------------------------------------//
