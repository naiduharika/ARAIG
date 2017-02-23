//
//  Stims.h
//  m3
//
//  Created by Harika Naidu on 2016-12-04.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#ifndef _STIMS_H_
#define _STIMS_H_

#include "Stimulation.h"

namespace araig {
    enum location_type {abs = 1,front, back, traps}; //enum for location type
    
    //concreate class inherited from Stimulation: Stims
    class Stims: public Stimulation {
        location_type location;
        int intensity;
        int frequency;
        int duration;
    public:
        static int stims;
        Stims();
        Stims(const std::string, location_type, const int, const int, const int);
        void display(std::ostream&) const;
        ~Stims();
    };

}

#endif /* _STIMS_H_ */
