//
//  ARAIG_Sensors.h
//  m3
//
//  Created by Harika Naidu on 2016-12-03.
//  Copyright © 2016 Harika Naidu. All rights reserved.
//

#ifndef _ARAIG_SENSORS_H_
#define _ARAIG_SENSORS_H_

#include <vector>
#include <memory>
#include <algorithm>
#include "Stimulation.h"
#include "Stims.h"
#include "Exoskeleton.h"
#include "Task.h"

namespace araig {
    
    class ARAIG_Sensors {
        std::vector<std::shared_ptr<Stimulation>> simList;
        Task **_task_list;
        size_t size;
    public:
        ARAIG_Sensors();
        size_t getsize() {return size;};
        Task& operator[](size_t i) const {return *_task_list[i];};
        ARAIG_Sensors(const char*, const char*);
        std::ostream& dump(std::ostream& os) const;
        ~ARAIG_Sensors();
    };
    std::ostream& operator << (std::ostream&, const ARAIG_Sensors&);
}
#endif /* _ARAIG_SENSORS_H_ */
