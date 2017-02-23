//
//  Stimulation.h
//  m3
//
//  Created by Harika Naidu on 2016-12-03.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#ifndef _STIMULATION_H_
#define _STIMULATION_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <new>

namespace araig {
    //Abstract Base class: Stimulation
    class Stimulation {
    protected:
        std::string Stim_name;
    public:
        static int stimulations;
        Stimulation(const std::string); //one argument constructor
        std::string getname(); //return name of the stimulation
        virtual void display(std::ostream&) const = 0; //pure virtual function display
        virtual ~Stimulation() = 0;
    };
    std::ostream& operator << (std::ostream&, const Stimulation&);
}

#endif /* _STIMULATION_H_ */
