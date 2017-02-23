//
//  Task.h
//  m3
//
//  Created by Harika Naidu on 2016-12-03.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#ifndef _TASK_H_
#define _TASK_H_

#include <list>
#include <iterator>
#include <memory>
#include <sstream>
#include "Stimulation.h"

namespace araig {
    
    class Task {
        std::string Task_Name;
        std::list<std::shared_ptr<Stimulation>> Stim_List;
    public:
        Task();
        Task(const std::string);
        Task(std::string n, std::list<std::shared_ptr<Stimulation>> lst);
        Task(const Task&);
        Task& operator=(const Task&);
        Task(Task&&);
        Task&& operator=(Task&&);
        std::string getName() {return Task_Name;}
        const Task& operator+=(std::shared_ptr<Stimulation>);
        const Stimulation& operator[](size_t i) const;
        void remove(std::string name);
        std::ostream& dump(std::ostream& os) const;
        std::ostream& execute(std::ostream& os) const;
        ~Task(); //destructor
    };
    std::ostream& operator << (std::ostream&, const Task&);
}

#endif /* _TASK_H_ */
