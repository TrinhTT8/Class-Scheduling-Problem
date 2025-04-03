// Greedy algorithm implemtation
/*  1. Sort the class based on their time and days
    2. Run the classes through the greedy algorithm
    3. Greedy algorithm picks the class that ends at the earliest time and continue to do so until the schedule is filled
    4. Should have multiple schedules for the users to examine*/

// Need a sorted vector
// Separate by days and sort by time 

#ifndef SCHEDULE.H
#define SCHEDULE .H

#include "classes.h"
#include <vector>

using namespace std;

class Schedule
{
public:
    // Need to pass the filterClasses vector
    static vector<ClassInfo>greedySchedule(vector<ClassInfo> &classinfo);
};

#endif SCHEDULE.H;