//
//  main.cpp
//  Project 4
//
//  Created by Ishan Sharma on 3/8/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include <iostream>
#include "MyMap.h"
#include "AttractionMapper.cpp"
using namespace std;

int main(){
    cout<<"Yes"<<endl;
    MapLoader ml;
    ml.load("/Users/ishansharma/Desktop/Uni/Winter Quarter 2017/CS 32/P4Testing/ex.txt");
    cout << ml.getNumSegments() << endl;
    //AttractionMapper am;
    
}
