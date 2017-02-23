//
//  Task.cpp
//  m3
//
//  Created by Harika Naidu on 2016-12-03.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#include "Task.h"

namespace araig {
    
    //default constructor puts a newly created Task in a safe state
    Task::Task()
    {
        Task_Name.clear(); 
        Stim_List.clear();
    }
    
    //one argument constructor
    Task::Task(const std::string n): Task_Name(n){}
    
    //two argument constructor to instantiate the task the name and list
    Task::Task(std::string n, std::list<std::shared_ptr<Stimulation>> lst)
    {
        Task_Name = n;
        Stim_List = lst;
    }
    
    //A copy constructor and operator to allow for Task object copy operations
    Task::Task(const Task& t)
    {
        Task_Name = t.Task_Name;
        Stim_List = t.Stim_List;
    }
    
    Task& Task::operator=(const Task& t)
    {
        if (this != &t)
        {
            Task_Name = t.Task_Name;
            Stim_List.clear();
            Stim_List = t.Stim_List;
        }
        return *this;
    }
    
    //A move constructor and operator to allow for Task object move operations
    Task::Task(Task&& t)
    {
        Task_Name = std::move(t.Task_Name);
        Stim_List = std::move(t.Stim_List);
        
        t.Task_Name.clear();
        t.Stim_List.clear();
    }
    
    Task&& Task::operator=(Task&& t)
    {
        if (this != &t)
        {
            Task_Name = std::move(t.Task_Name);
            
            Stim_List.clear();
            
            Stim_List = std::move(t.Stim_List);
            
            t.Task_Name.clear();
            t.Stim_List.clear();
        }
        return std::move(*this);
    }
    
    //An overloaded operator to add Stimulation objects using +=
     const Task& Task::operator+=(std::shared_ptr<Stimulation> t)
    {
        Stim_List.push_back(std::move(t));
        return *this;
    }
    
    //An overloaded operator to access Stimulation objects using []
    const Stimulation& Task::operator[](size_t i) const
    {
        std::shared_ptr<Stimulation> s = nullptr;
        std::list<std::shared_ptr<Stimulation>>::const_iterator it = Stim_List.begin(); //Iterator to be advanced.
        std::advance(it, i); //Increments the iterator it by i elements.
        
        s = *it; //assign the value it points to s
        
        return *s; //return the value s points to
    }
    
    //A function that allows the removal of a Stimulation based on Stimulation name
    void Task::remove(std::string name)
    {
        std::list<std::shared_ptr<Stimulation>>::iterator it = Stim_List.begin();
        while (it != Stim_List.end())
        {
            if ((*it)->getname() == name) {
                it = Stim_List.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    
    //A dump function that writes the Task configuration to an ostream&
    std::ostream& Task::dump(std::ostream& os) const
    {
        os << "\n" << Task_Name << std::endl;
        os << "------" <<std::endl;
        for (std::list<std::shared_ptr<Stimulation>>::const_iterator i = Stim_List.begin(); i != Stim_List.end(); i++)
        {
            (*i)->display(os);
        }
        return os;
    }
    
    //An execute function that takes an ostream& and activates each Stimulation that has been configured in the Task List
    std::ostream& Task::execute(std::ostream& os) const
    {
        os << "==============================" << std::endl;
        os << "Task Name: " << Task_Name << std::endl;
        os << "==============================" << std::endl;
        
        for (std::list<std::shared_ptr<Stimulation>>::const_iterator i =  Stim_List.begin(); i != Stim_List.end(); i++)
        {
            (*i)->display(os);
        }
        return os;
    }
    
    //destructor
    Task::~Task()
    {
        Task_Name.clear();
        Stim_List.clear();
    }
    
}

