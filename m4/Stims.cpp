//
//  Stims.cpp
//  m3
//
//  Created by Harika Naidu on 2016-12-04.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "Stims.h"

namespace araig {
    int Stims::stims = 0;
    
    Stims::Stims(): araig::Stimulation(""), intensity(0), frequency(0), duration(0){};
    
    Stims::Stims(const std::string n, location_type l, const int i, const int f, const int d):
    araig::Stimulation(n), location(l), frequency(f), duration(d)
    {
        if (i > 0 && i < 100) {
            intensity = i;
        }
        
        stims++;
    }
    
    void Stims::display(std::ostream& os) const
    {
        os << Stim_name << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " << "Type = ";
        os << "stims" << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " << "Location = ";
        switch (location) {
            case araig::abs:
                os << "abs";
                break;
            case front:
                os << "front";
                break;
            case back:
                os << "back";
                break;
            case traps:
                os << "traps";
            default:
                break;
        }
        os <<std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " <<  "Intensity = ";
        os << intensity << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " <<  "Frequency =  ";
        os << frequency << std::endl;
        os << std::left << std::setw(5) << std::setfill(' ') << " " <<  "duration: " ;
        os << duration << std::endl;
    }
    
    Stims::~Stims()
    {
        stims--;
    }

}
