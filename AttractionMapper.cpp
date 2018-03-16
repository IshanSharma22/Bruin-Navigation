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
                m_map.associate(s.attractions[j].name, s.attractions[j].geocoordinates);
            }
        }
    }
    
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
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

