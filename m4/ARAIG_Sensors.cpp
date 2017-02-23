//
//  ARAIG_Sensors.cpp
//  m3
//
//  Created by Harika Naidu on 2016-12-04.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "ARAIG_Sensors.h"

namespace araig {
    
    ARAIG_Sensors::ARAIG_Sensors()
    {
        _task_list = nullptr;
        simList.clear();
    }
    
    ARAIG_Sensors::ARAIG_Sensors(const char* StimFile, const char* TaskFile)
    {
        //open the files
        std::ifstream f1(StimFile, std::ios::in), f2(TaskFile, std::ios::in);
        
        //throw error if file cannot be opened
        if (!f1){
            throw std::string("*** Failed to open file ") + std::string(StimFile) + std::string(" ***");
        }
        if (!f2) {
            throw std::string("*** Failed to open file ") + std::string(TaskFile) + std::string(" ***");
        }
        
        //creating stimulations and adding to simList in ARAIG_Sensors
        std::string type, na, loc;
        int intense, freq, dur;
        char delimit = ',';
        
        while(f1.good())
        {
            
            getline(f1, type, delimit); //get line until delimit ','
            
            if (type == "stim") //Check type if stim
            {
                getline(f1, na, delimit); //get name of the sim
                getline(f1, loc, delimit); //get loction
                f1 >> intense; //get intensity
                f1.ignore();
                f1 >> freq; //get frequency
                f1.ignore();
                f1 >> dur; //get duration
                f1.ignore(2000, '\n');
                
                int id = 0; //deduce the location string to an int to pass location_type
                if (loc == "abs") {id = 1;}
                else if (loc == "front") {id = 2;}
                else if (loc == "back"){id = 3;}
                else if (loc == "traps"){id = 4;}
                else {std::cout << "Invalid location type";}
                
                //create new stims object
                simList.push_back(std::shared_ptr<Stimulation> (new Stims(na, location_type(id), intense, freq, dur)));
            }
            else if (type == "exoskeleton") //if type exos
            {
                getline(f1, na, delimit); //get name
                f1 >> intense; //get intensity
                f1.ignore();
                f1 >> dur; //get duration
                f1.ignore(2000, '\n');
               
                //create new exos object
                simList.push_back(std::shared_ptr<Stimulation> (new Exoskeleton(na, intense, dur)));
            }
        }
        f1.close(); //close file
        
        //creating Task and adding to dynamically allocated _tast_list in ARAIG_Sensors
        std::string line, t, _t1st, tname, simname;
        char comma = ',';
        char newline = '\n';
        size_t count= 0;
        int idx = 0;
        
        while (!f2.eof()) { //get number of lines
            getline(f2, line, newline);
            if((size_t)line.find_first_of(comma) != std::string::npos)
                count++;
        }
        size = count;
        f2.clear();
        f2.seekg(0, std::ios::beg); //rewind
            
        _task_list = new Task*[count]; //allocate memory to hold the task
        
        while(f2.good())
        {
                getline(f2, t, newline); //read line
                
                std::istringstream is(t);
                
                if((size_t)t.find_first_of(comma) != std::string::npos){ //look for a comma
                    tname = t.erase(0,t.find_first_of(comma)+1); //get task name by erasing TASK,
                    tname.erase(std::remove(tname.begin(), tname.end(), '\r'),tname.end()); //erase the traiing '\r' char
                    is.ignore(2000, '\n');
                    
                        _task_list[idx] = new Task(tname); //creat task object
                        idx++; //increment index
                    }
                else{
                    is >> simname; //get simulation name
                    simname.erase(std::remove(simname.begin(), simname.end(), '\r'), simname.end()); //erase the traiing '\r' char
                    is.ignore(2000, '\n');
                    
                    for (std::vector<std::shared_ptr<Stimulation>>::iterator i = simList.begin(); i != simList.end(); i++) {
                        //find a match for the simname in stimulation
                        if((*i)->getname() == simname) {
                            //if found add the stimulation to the task list
                            *_task_list[idx-1] += (std::shared_ptr<Stimulation> (*i));
                        }
                    }
                }
            }
        
        f2.close();//close file
    }
    
    //function that will write the contents of memory (all the dynamically created Stimulation objects information) to an ostream&
    std::ostream& ARAIG_Sensors::dump(std::ostream& os) const
    {
        for (size_t i = 0; i < size; i++)
            _task_list[i]->dump(os);
        
        return os;
    }
    
    std::ostream& operator << (std::ostream& os, const ARAIG_Sensors& as)
    {
        as.dump(os);
        return os;
    }
    
    //deallocate dynamically created memory
    ARAIG_Sensors::~ARAIG_Sensors()
    {
        for (size_t i = 0; i < size; i++)
        delete _task_list[i];
        delete [] _task_list;
        _task_list = nullptr;
        
    }

}
