#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <random>
#include "schedule.h"

using namespace std;

vector<vector<ClassInfo>> Schedule::greedySchedule(vector<ClassInfo> &filtered)
{
    vector<vector<ClassInfo>> allSchedules;
    int numAttempts = 3; // Try 3 different random greedy schedules

    for (int attempt = 0; attempt < numAttempts; ++attempt)
    {
        vector<ClassInfo> shuffled = filtered; // Copy original
        random_device rd;
        mt19937 g(rd());
        shuffle(shuffled.begin(), shuffled.end(), g);   // Shuffle the vectors of filtered classes to obtain different schedules
        // Or else the algorithm always pick the first valid options 

        vector<ClassInfo> selectedClasses;
        unordered_map<int, int> previousClassEndTime;
        unordered_map<string, bool> scheduledCourseNames;

        for (const ClassInfo &c : shuffled)
        {
            // Skip the class if the same course name has already been scheduled 
            if (scheduledCourseNames[c.name])
                continue;

            bool suitable = true;

            // Make sure if the class happens on a specific day, it will take place after the previous class
            for (int day : c.days)
            {
                if (c.startTime < previousClassEndTime[day])
                {
                    suitable = false;
                    break;
                }
            }

            // Add to schedule if suitable
            if (suitable)
            {
                selectedClasses.push_back(c);
                scheduledCourseNames[c.name] = true;
                for (int day : c.days)
                {
                    previousClassEndTime[day] = c.endTime;
                }
            }
        }

        if (!selectedClasses.empty())
        {
            allSchedules.push_back(selectedClasses);
        }
    }

    return allSchedules;
}

// Print out all the suggested schedules (if applicable)
void Schedule::printSchedule(const vector<ClassInfo> &selectedClasses)
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

        // Convert start time and end time to strings
        startT = to_string(c.startTime);
        endT = to_string(c.endTime);

        if (startT.length() < 4)
        {
            startT = "0" + startT;
        }
        if (endT.length() < 4)
        {
            endT = "0" + endT;
        }

        // Parse the string to format how the time usually looks (e.g. 10:30, 08:30, etc.)
        cout << ", Time: " << startT.substr(0, 2) << ":" << startT.substr(2, 2) << "-" << endT.substr(0, 2) << ":" << endT.substr(2, 2);
        cout << ", Location: " << c.location << endl;
    }
}
