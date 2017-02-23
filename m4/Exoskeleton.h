//
//  Exoskeleton.h
//  m3
//
//  Created by Harika Naidu on 2016-12-04.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#ifndef _EXOSKELETON_H_
#define _EXOSKELETON_H_

#include "Stimulation.h"

namespace araig {
    //concreate class inherited from Stimulation: Exoskeleton
    class Exoskeleton: public Stimulation {
        int intensity;
        int duration;
    public:
        static int exoskeletons;
        Exoskeleton();
        Exoskeleton(const std::string, const int, const int);
        void display(std::ostream&) const;
        ~Exoskeleton();
    };
}

#endif /* _EXOSKELETON_H_ */
