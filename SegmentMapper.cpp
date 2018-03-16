/*
#include "provided.h"
#include "MyMap.h"
#include <vector>
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
    
private:
    MyMap<GeoCoord, vector<StreetSegment>> m_segMap;
    void help_associate(GeoCoord geo, StreetSegment seg);
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{

    StreetSegment seg;
    for (int i=0; i<ml.getNumSegments(); i++){
        GeoCoord st;
        GeoCoord end;
        ml.getSegment(i, seg);
        st=seg.segment.start;
        end=seg.segment.end;
        help_associate(st, seg);
        help_associate(end, seg);
        int Asize=seg.attractions.size();
        int k=0;
        while(Asize>0){
            GeoCoord attracGeo =seg.attractions[k].geocoordinates;
            help_associate(attracGeo, seg);
        }
    }

}

void SegmentMapperImpl::help_associate(GeoCoord geo, StreetSegment seg){

    vector<StreetSegment>* p;
    p = m_segMap.find(geo);
    if(p && (*p).size() > 0){
        (*p).push_back(seg);
    }
    else{
        vector<StreetSegment> n;
        n.push_back(seg);
        m_segMap.associate(geo, n);
    }

}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    const vector<StreetSegment> emptysegments;
    
	const vector<StreetSegment>* segments;
    
    segments = m_segMap.find(gc);
    if (segments!=NULL)
        return (*segments);
    else
        return emptysegments;
    
    return emptysegments;
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
*/
