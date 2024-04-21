#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& availability,
    const size_t needPerDay,
    const size_t maxShiftsPerWorker,
    DailySchedule& schedule,
    std::vector<size_t>& shiftsCount,
    size_t currentDay
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below


    sched = DailySchedule(avail.size(), vector<Worker_T>());

    std::vector<size_t> workerShifts(avail.size(), 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0);



}

bool scheduleHelper(
    const AvailabilityMatrix& availability,
    const size_t needPerDay,
    const size_t maxShiftsPerWorker,
    DailySchedule& schedule,
    std::vector<size_t>& shiftsCount,
    size_t currentDay
) {
    
    size_t day = currentDay;
    if (availability.size() == day) {
        return 1;
    }

    for (size_t workerID = 0; workerID < availability[currentDay].size(); workerID++) {
        if (availability[currentDay][workerID] && (true == (shiftsCount[workerID] < maxShiftsPerWorker))) {
            schedule[currentDay].push_back(workerID);
            shiftsCount[workerID] = shiftsCount[workerID] + 1;

            if (schedule[currentDay].size() == needPerDay) {
                size_t nextDay = currentDay + 1;
                if (scheduleHelper(availability, needPerDay, maxShiftsPerWorker, schedule, shiftsCount, nextDay)) {
                    return true;  
                }

            
                schedule[currentDay].pop_back();
                shiftsCount[workerID] = shiftsCount[workerID] - 1;
            }
        }
    }

    return false;
}


