//
//  main.cpp
//  m3
//
//  Created by Harika Naidu on 2016-12-03.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "Stimulation.h"
#include "Stims.h"
#include "Exoskeleton.h"
#include "Task.h"
#include "ARAIG_Sensors.h"
#include "Profile.h"

int main(int argc, const char * argv[]) {
    
    std::cout << "\nCommand Line : ";
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << ' ';
    }
    std::cout << std::endl;
    if (argc != 5) {
        std::cerr << "\n***Incorrect number of arguments***\n";
        return 1;
    }

    try {
        araig::ARAIG_Sensors sensors(argv[1],argv[2]);
        
        std::ofstream outfile(argv[4], std::ios::out);
        
        araig::Profile profile(argv[3], outfile, sensors);
        
        profile.run();
        
        if (!outfile.fail()) { //write to file
            profile.displayCompleted(outfile);
        }
        outfile.clear();
        outfile.close();
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        return 2;
    }
    
    std::cout << "\nPress any key to continue ... \n";
    std::cin.get();
    
    return 0;
}
