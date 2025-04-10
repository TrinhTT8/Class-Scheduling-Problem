#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include "schedule.h"

using namespace std;

// Use Greedy Algorithm to select non-overlapping classes
vector<vector<ClassInfo>> Schedule::greedySchedule(vector<ClassInfo> &classes)
{
    vector<vector<ClassInfo>> allSchedules;
    vector<ClassInfo> selectedClasses;
    unordered_map<int, int> previousClassEndTime;     // Store the day and end time of the class
    unordered_map<string, bool> scheduledCourseNames; // Track already scheduled course names

    // Loop through all classes in the classes vector
    for (auto it = classes.begin(); it != classes.end();)
    {
        ClassInfo &c = *it;   // Get the current class
        bool suitable = true; // boolean to check if the class does overlap

        // Skip if this course name has already been scheduled
        if (scheduledCourseNames.find(c.name) != scheduledCourseNames.end())
        {
            it = classes.erase(it); // Remove this class and continue
            continue;               // Skip the class if it's already in the schedule
        }

        // Looping through the days of the class (if the sections happen on more than one day)
        for (int day : c.days)
        {
            if (c.startTime < previousClassEndTime[day])
            {                     // Check for overlap on that specific day
                suitable = false; // the class cannot be scheduled due to time conflict
                break;
            }
        }

        // If no overlap, select the class and update previousClassEndTime
        if (suitable)
        {
            selectedClasses.push_back(c);
            scheduledCourseNames[c.name] = true; // Mark the course name as scheduled
            for (int day : c.days)
            {
                previousClassEndTime[day] = c.endTime; // Update the end time for the specific day
            }
        }
    }

    // Add the selected classes as a new schedule
    allSchedules.push_back(selectedClasses);

    return allSchedules; // Return all schedules found
}

// Print out all the suggested schedules (if applicable)
void printSchedule(const vector<ClassInfo> &selectedClasses)
{
    int i = 0;
    string startT, endT;
    for (const ClassInfo &c : selectedClasses)
    {
        cout << "Course: " << c.name << " (ID: " << c.courseID << "), Days: ";

        // Convert number into words representation of days
        for (int d : c.days)
        {
            switch (d)
            {
            case 1:
                cout << "Monday ";
                break;
            case 2:
                cout << "Tuesday ";
                break;
            case 3:
                cout << "Wednesday ";
                break;
            case 4:
                cout << "Thursday ";
                break;
            case 5:
                cout << "Friday ";
                break;
            default:
                break;
            }
        }

        startT = to_string(c.startTime);
        endT = to_string(c.endTime);

        // Parse the string to format how the time usually looks (e.g. 10:30, 08:30, etc.)
        cout << ", Time: " << startT[0] + startT[1] << ":" << startT[2] + startT[3] << "-" << endT[0] + endT[1] << ":" << endT[2] + endT[3];
        cout << ", Location: " << c.location << endl;
    }
}
