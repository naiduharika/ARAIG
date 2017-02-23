//
//  Profile.h
//  m4
//
//  Created by Harika Naidu on 2016-12-06.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <vector>
#include <iterator>
#include "ARAIG_Sensors.h"
#include "Exoskeleton.h"
#include "Stims.h"
#include "Stimulation.h"
#include "Task.h"

namespace araig {
    
    struct calibration {
        int max ;
        int min ;
    };
    
    struct person {
        std::string _FirstName;
        std::string _LastName;
        int _IDnum;
        
    };
    class Profile {
        person student;
        person instructor;
        calibration calib;
        std::string file;
        std::vector<std::shared_ptr<Task>> ToRun;
        std::vector<std::shared_ptr<Task>> completed;
    public:
        Profile(const char*, std::ofstream&, ARAIG_Sensors&);
        void displayToRun(std::ostream&) const;
        void displayCompleted(std::ostream&) const;
        void displayNext(std::ostream&) const;
        void displayLastCompleted(std::ostream&) const;
        Task& operator[](size_t i) const {return *ToRun[i];};
        void run();
        int menu();
        void listinfo(std::ostream&) const;
        void runflightplan();
        void pause();
        void loadfile(std::ostream&) const;
        ~Profile();
    };
}

#endif /* _PROFILE_H_ */
