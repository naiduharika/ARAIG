//
//  Stimulation.cpp
//  m3
//
//  Created by Harika Naidu on 2016-12-03.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "Stimulation.h"

namespace araig {
    
    int Stimulation::stimulations =0;
    
    Stimulation::Stimulation(const std::string n): Stim_name(n)
    {
        stimulations++;
    };
    
    std::string Stimulation::getname() {return Stim_name;}
    
    Stimulation::~Stimulation()
    {
        stimulations--;
    }
    
     std::ostream& operator << (std::ostream& os, const Stimulation& obj)
    {
        obj.display(os);
        return os;
    }
    
    
}
