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
        
        double slat,slong, elat, elong;
        
        infile >> slat;
        infile.ignore(1000, ',');
        infile.ignore(1000, ' ');
        
        infile>> slong;
        infile.ignore(1000, ' ');
        
        infile >> elat;
        infile.ignore(1000, ',');
        
        infile>> elong;
        infile.ignore(10000, '\n');
        
        StreetSegment temp;
        temp.streetName=s;
        
        temp.segment.start.latitude=slat;
        temp.segment.start.longitude=slong;
        
        temp.segment.end.latitude= elat;
        temp.segment.end.longitude= elong;
        
        temp.segment.start.latitudeText=to_string(slat);
        temp.segment.start.longitudeText=to_string(slong);
        
        temp.segment.end.latitudeText=to_string(elat);
        temp.segment.end.longitudeText=to_string(elong);

        m_VstSeg.push_back(temp);
        int attrac;
        infile >> attrac;
        
        infile.ignore(10000, '\n');
        
        int i=0;
        while (attrac>0){
            string s2;              // ONLY TAKES FIRST WORD FIX!!!!!!!!!!
            infile >> s2;
            
            infile.ignore(1000, '|');
            double alat, along;
            infile >> alat;
            infile.ignore(1000, ',');
            infile.ignore(1000, ' ');
            infile >> along;
            infile.ignore(10000, '\n');
            
            Attraction temp;
            temp.name=s2;
            temp.geocoordinates.latitude=alat;
            temp.geocoordinates.longitude=along;
            
            temp.geocoordinates.latitudeText=to_string(alat);
            temp.geocoordinates.longitudeText=to_string(along);
            
            m_VstSeg[m_NstSeg].attractions.push_back(temp);
            
            i++;
            attrac--;
        }
        
        m_NstSeg++;
    }
    
	return false;  // This compiles, but may not be correct
}

size_t MapLoaderImpl::getNumSegments() const
{
    return m_NstSeg;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum < 0 ||segNum >=getNumSegments()){
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
