//
//  Exoskeleton.cpp
//  m3
//
//  Created by Harika Naidu on 2016-12-04.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "Exoskeleton.h"

namespace araig {
    
    int Exoskeleton::exoskeletons = 0;
    
    Exoskeleton::Exoskeleton():Stimulation(""), intensity(0), duration(0){};
    
    Exoskeleton::Exoskeleton(const std::string n, const int i,const int d):Stimulation(n),duration(d)
    {
        if (i > 0 && i < 100) {
            intensity = i;
        }
        
        exoskeletons++;
    }
    
    void Exoskeleton::display(std::ostream& os) const
    {
        os << Stim_name << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " << "Type = ";
        os << "exosceleton" << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " << "Intensity = ";
        os << intensity << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " << "duration = " ;
        os << duration << std::endl;
    }
    
    Exoskeleton::~Exoskeleton()
    {
        exoskeletons--;
    }

}
