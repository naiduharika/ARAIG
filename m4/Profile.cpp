//
//  Profile.cpp
//  m4
//
//  Created by Harika Naidu on 2016-12-06.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "Profile.h"

namespace araig {
    
    Profile::Profile(const char* file, std::ofstream& outfile, ARAIG_Sensors& as)
    {
        //open file
        std::ifstream f1(file, std::ios::in);
        //throw error
        if (!f1){
            throw std::string("*** Failed to open file ") + std::string(file) + std::string(" ***");
        }
        
        //create profile objects
        ToRun.clear();
        std::string line;
        char comma = ',';
        char n_line = '\n';
    
        while (f1.good()) {
            getline(f1, student._FirstName, comma);
            getline(f1, student._LastName, comma);
            f1 >> student._IDnum;
            f1.ignore(2000, n_line);

            getline(f1, instructor._FirstName, comma);
            getline(f1, instructor._LastName, comma);
            f1 >> instructor._IDnum;
            f1.ignore(2000, n_line);
            
            f1 >> calib.max;
            f1.ignore();
            
            f1 >> calib.min;
            f1.ignore(2000, n_line);
            
            while (getline(f1, line, n_line)) {
                line.erase(std::remove(line.begin(), line.end(), '\r'),line.end());
                for (size_t i = 0; i < as.getsize(); i++)
                    if(line == as[i].getName()){
                        ToRun.push_back(std::shared_ptr<Task> (new Task(as[i])));
                    }
                }
        }
        f1.close(); //close file
        
        if (!outfile) {
            throw std::string("*** Failed to open file ") + std::string(file) + std::string(" ***");
        }
        
        if (!outfile.fail()) { //write araig sensor content to file
            listinfo(outfile);
        }
    }
    
    //A function that displays all the Tasks currently in the ToRun container to the screen
    void Profile::displayToRun(std::ostream& os) const
    {
        for (std::vector<std::shared_ptr<Task>>::const_iterator r = ToRun.begin(); r != ToRun.end(); r++)
            (*r)->execute(os);
        os << "\n";
    }
    
    //A function that displays all the Tasks currently in the Completed container to the screen
    void Profile::displayCompleted(std::ostream& os) const
    {
        for (std::vector<std::shared_ptr<Task>>::const_iterator c = completed.begin(); c != completed.end(); c++)
           (*c)->execute(os);
        os << "\n";
    }
    
    //A function that displays the next Task to be executed to the screen
    void Profile::displayNext(std::ostream& os) const
    {
            ToRun.front()->execute(os);
    }
    
    //A function that displays the last completed Task to the screen
    void Profile::displayLastCompleted(std::ostream& os) const
    {
        os << "Last completed Task is... \n";
        os << "**";
        os << completed.back()->getName();
        os << "**";
        os << std::endl;
    }
    
    //A function that executes the flight plan.
    //Based on user input, this function will execute the next Task in the ToRun container and then move the Task to the Completed Container.
    void Profile::run()
    {
        listinfo(std::cout);
        completed.clear();
        int input;
        
        do {
            input = menu();
            
            switch (input) {
                case 1:
                    if (!ToRun.empty()) {
                        displayToRun(std::cout);
                    } else {
                        std::cout << "All tasks have been completed" << std::endl;
                    }
                    pause();
                    break;
                
                case 2:
                    if(!ToRun.empty()){
                        runflightplan();
                    } else {
                        std::cout << "\n ** End of Flight Plan ** " << std::endl;
                    }
                    pause();
                    break;
                    
                case 3:
                    if(!ToRun.empty()){
                        std::cout << "Next Task is... \n";
                        std::cout << "**";
                        std::cout << ToRun.front()->getName();
                        std::cout << "**" << std::endl;
                    } else {
                        std::cout << "All tasks have been completed " << std::endl;
                    }
                    pause();
                    break;

                    
                case 4:
                    if (!completed.empty()) {
                    displayLastCompleted(std::cout);
                    }else{
                        std::cout << "No tasks have been completed yet\n" << std::endl;
                    }
                    pause();
                    break;
                    
                case 5:
                    if (!completed.empty()){
                    displayCompleted(std::cout);
                    } else {
                        std::cout << "No tasks have been completed yet\n" << std::endl;
                    }
                    pause();
                    break;
                    
                case 0: std::cout << "Existing Flight Plan, Good Bye!!" << std::endl;
                    break;
                    
                default: std::cout << "===Invalid Selection, try again.===\n" << std::endl;
                    pause();
                    break;
            }
        } while (input != 0);
        
    }
    
    void Profile::runflightplan()
    {
        std::cout << "\n ** Executing Flight Plan **" << std::endl;
            displayNext(std::cout);

            completed.push_back(std::shared_ptr<Task>(new Task(std::move(*ToRun.front()))));
            ToRun.erase(ToRun.begin());
    }
    
    void Profile::listinfo(std::ostream& of) const
    {
        of << std::setw(13) << std::left << "Student: " << student._FirstName << " " << student._LastName << " - " << student._IDnum << std::endl;
        of << std::setw(13) << std::left << "Instructor: " << instructor._FirstName << " " << instructor._LastName << " - " << instructor._IDnum << std::endl;
        of << "Student Calibration:" << std::endl;
        of << "MAX = " << calib.max << std::endl;
        of << "MIN = " << calib.min << std::endl;
    }
    
    
    int Profile::menu()
    {
        int input;
        std::cout << "------------------------------------------------------" << std::endl
        << "Flight Plan Management Tool" << std::endl
        << "*** Choose from options (1 - 5) or press 0 to exit ***" << std::endl
        << "______________________________________________________" << std::endl
        
        << "1 - Display all Tasks" << std::endl
        << "2 - Exectue a Task" << std::endl
        << "3 - Display Next task" << std::endl
        << "4 - Display Last completed task" << std::endl
        << "5 - Display all completed tasks" << std::endl
        << "0 - Exit" << std::endl
        << "> - ";
        
        
        std::cin >> input;
        
        if (std::cin.fail() || input >= 6) {
            std::cin.clear();
            std::cin.ignore();
            input = -1;
        }
        
        return input;
    }
    
    void Profile::pause()
    {
        char a = '\0';
        
        std::cout << "\nPress Enter to continue..." << std::endl;
        while(a != '\n'){
            std::cin.get(a);
            std::cin.ignore();
        }
    }
    
    Profile::~Profile(){}
}
