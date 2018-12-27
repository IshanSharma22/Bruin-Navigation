//
//  AttractionMapper.cpp
//  New Project 4
//
//  Created by Ishan Sharma on 3/11/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "provided.h"
#include <string>
#include <cctype>
#include "MyMap.h"
using namespace std;

 class AttractionMapperImpl
 {
 public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
 private:
 MyMap<string, GeoCoord> m_map;
 };
 
 AttractionMapperImpl::AttractionMapperImpl()
 {
 }
 
 AttractionMapperImpl::~AttractionMapperImpl()
 {
 }
 
 void AttractionMapperImpl::init(const MapLoader& ml)
 {
     for (int i=0; i<ml.getNumSegments(); i++){
         StreetSegment s;
         ml.getSegment(i, s);
         if(s.attractions.size()>0){
         for(int j=0; j<s.attractions.size(); j++){
             string temp = s.attractions[j].name;
             for (int x=0; x<temp.size(); x++){
                 temp[x]=tolower(temp[x]);
             }
             m_map.associate(temp, s.attractions[j].geocoordinates);
            }
         }
     }
 
 }
 
 bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
 {
     for (int x=0; x<attraction.size(); x++){
         attraction[x]=tolower(attraction[x]);
     }
     
     const GeoCoord* geo=m_map.find(attraction);
     
     if (geo!=NULL){
         gc=(*geo);
         return true;
     }
     else
        return false;
 }
 
 //******************** AttractionMapper functions *****************************
 
 // These functions simply delegate to AttractionMapperImpl's functions.
 // You probably don't want to change any of this code.
 
 AttractionMapper::AttractionMapper()
 {
	m_impl = new AttractionMapperImpl;
 }
 
 AttractionMapper::~AttractionMapper()
 {
	delete m_impl;
 }
 
 void AttractionMapper::init(const MapLoader& ml)
 {
	m_impl->init(ml);
 }
 
 bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
 {
	return m_impl->getGeoCoord(attraction, gc);
 }

