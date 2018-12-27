//
//  suport.hpp
//  New Project 4
//
//  Created by Ishan Sharma on 3/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#ifndef suport_h
#define suport_h
#include "provided.h"

struct PrioGeoCord {
    GeoCoord geo;
    double priority;
    std::string name;
};



bool operator!=(const GeoCoord& a, GeoCoord& b);


bool operator==(GeoCoord& a, const GeoCoord& b);
bool operator<=(GeoCoord& a, const GeoCoord&b);
bool operator>=(GeoCoord& a, const GeoCoord&b);



bool operator==(PrioGeoCord& a, const PrioGeoCord& b);
bool operator<=(PrioGeoCord& a, const PrioGeoCord&b);
bool operator>=(PrioGeoCord& a, const PrioGeoCord&b);


bool operator<(const PrioGeoCord& a, const PrioGeoCord & b);


#endif /* suport_h */
