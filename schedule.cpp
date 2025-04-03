#include <algorithm>
#include <unordered_map>
#include "schedule.h"
// As of right now we do not take into account when is the latest time the users want to have a class

vector<ClassInfo> Schedule::greedySchedule(vector<ClassInfo> &classes)
{
    vector<ClassInfo> selectedClasses;
    unordered_map<int, int> previousClassEndTime; // Store the day and the end time of the class

    // Use Greedy Algorithm select non-overlapping class
    for (const ClassInfo& c : classes)
    {                         // Loop through all classes in the classes vector
        bool suitable = true; // boolean to check if the class does overlap

        for (int day : c.days)
        {                                                // Looping through the days of the class (if the sections happen on more than one day)
            if (c.startTime < previousClassEndTime[day]){ // Check if the course start time happens before the previous class end time for specific day
                suitable = false;                        // the class cannot be scheduled due to time conflict
                break;
            }                                       // exit the loop
        }

        // If no overlap, select the class and update previousClassEndTime
        if (suitable)
        {
            selectedClasses.push_back(c);
        }
        for (int day : c.days)
        {
            previousClassEndTime[day] = c.endTime;
        }
    }

    return selectedClasses;
}