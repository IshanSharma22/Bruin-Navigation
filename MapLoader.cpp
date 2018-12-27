//
//  MapLoader.cpp
//  New Project 4
//
//  Created by Ishan Sharma on 3/11/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include "provided.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MapLoaderImpl
{
public:
    MapLoaderImpl();
    ~MapLoaderImpl();
    bool load(string mapFile);
    size_t getNumSegments() const;
    bool getSegment(size_t segNum, StreetSegment& seg) const;
    
private:
    vector<StreetSegment> m_VstSeg;
    int m_NstSeg;
};

MapLoaderImpl::MapLoaderImpl()
{
    m_NstSeg=0;
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream infile(mapFile);
    
    if (!infile){
        m_NstSeg=0;
        return false;
    }
    
    string s;
    
    while (getline(infile, s)){
        
        string x;
        getline(infile,x);
        string slat,slong, elat, elong;
        int c=0;
        while(x[c]!=','){
            slat+=x[c];
            c++;
        }
        c++;
        
        if(x[c]==' '){
            c++;
        }
        
        while(x[c]!=' '){
            slong+=x[c];
            c++;
        }
        c++;
        
        while(x[c] != ','){
            elat+=x[c];
            c++;
        }
        c++;
        
        if(x[c]==' '){
            c++;
        }
        
        while(c!=x.size()){
            elong+=x[c];
            c++;
        }
        c++;
        
        StreetSegment temp;
        temp.streetName=s;
        
        GeoCoord start((slat),(slong));
        GeoCoord end((elat),(elong));
        
        temp.segment.start=start;
        temp.segment.end=end;

        
        m_VstSeg.push_back(temp);
        int attrac;
        infile >> attrac;
        
        infile.ignore(10000, '\n');
        
        //int i=0;
        while (attrac>0){
            string s2;
            getline(infile, s2);
            string aname="";
            int j=0;
            
            while(s2[j]!='|'){
                aname+=s2[j];
                j++;
            }
            j++;
            
            string alat="";
            while(s2[j]!=','){
                alat+=s2[j];
                j++;
            }
            j++;
            if(s2[j]==' '){
                j++;
            }
            
            string along="";
            while(j!=s2.size()){
                along+=s2[j];
                j++;
            }
            
            Attraction t;
            t.name=aname;
            t.geocoordinates.latitude=stod(alat);
            t.geocoordinates.longitude=stod(along);
            
            t.geocoordinates.latitudeText=alat;
            t.geocoordinates.longitudeText=along;
            
            m_VstSeg[m_NstSeg].attractions.push_back(t);
            
            //i++;
            attrac--;
        }
        
        m_NstSeg++;
    }
    
    return true;  // This compiles, but may not be correct
}

size_t MapLoaderImpl::getNumSegments() const
{
    return m_NstSeg;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum >=getNumSegments()){
        return false;
    }
    seg=m_VstSeg[segNum];
    return true;
    
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
    m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
    delete m_impl;
}

bool MapLoader::load(string mapFile)
{
    return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
    return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
    return m_impl->getSegment(segNum, seg);
}
