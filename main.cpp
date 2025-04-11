#include <iostream>
#include <unordered_map>
#include "classes.h"
#include "schedule.h"
#include <cctype>

using namespace std;

int main()
{
    unordered_map<string, vector<ClassInfo>> classDetails;
    string filename = "classes.txt";
    string startT, endT;

    // load classes from file
    loadFromFile(classDetails, filename);

    int choice = 0;

    while (choice != 6)
    {
        cout << "\n1. View Class Details\n";
        cout << "2. Add a New Class\n";
        cout << "3. Search for Class by Course ID\n";
        cout << "4. Remove a Class\n";
        cout << "5. Generate schedule\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            // show all classes
            printClassDetails(classDetails);
        }
        else if (choice == 2)
        {
            // add new class
            addClass(classDetails);
            saveToFile(classDetails, filename);
        }
        else if (choice == 3)
        {
            // filtering the classes with specific courseID
            string searchID;
            cout << "Enter course ID: ";
            cin.ignore();
            getline(cin, searchID);

            auto it = classDetails.find(searchID);
            if (it != classDetails.end())
            {
                cout << "\nClasses Found for ID: " << searchID << "\n";
                for (const ClassInfo &classInfo : it->second)
                {
                    cout << "\nCourse ID: " << classInfo.courseID << "\n";
                    cout << "Name: " << classInfo.name << "\n";
                    cout << "Time: " << classInfo.startTime << " - " << classInfo.endTime << "\n";
                    cout << "Days: ";
                    for (int day : classInfo.days)
                    {
                        switch (day)
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
                            cout << "Unknown ";
                            break;
                        }
                    }
                    cout << "\nLocation: " << classInfo.location << "\n";
                }
            }
            else
            {
                cout << "Class with ID " << searchID << " not found.\n";
            }
        }

        else if (choice == 4)
        {
            // option to remove class
            removeClass(classDetails);
            saveToFile(classDetails, filename);
        }
        else if (choice == 5)
        {
            // option for generating a schedule
            int numCourses;
            vector<string> desiredCourseIDs;
            int startTime, endTime;
            vector<int> preferredDays;

            cout << "How many courses do you want the schedule for? ";
            cin >> numCourses;
            cout << "Enter course IDs:\n";
            for (int i = 0; i < numCourses; ++i)
            {
                string id;
                cin >> id;
                desiredCourseIDs.push_back(toUpper(id));
            }

            cout << "Enter preferred start time (e.g., 900 for 9:00 AM): ";
            cin >> startTime;
            cout << "Enter preferred end time (e.g., 1400 for 2:00 PM): ";
            cin >> endTime;

            int day;
            cout << "Enter preferred days (e.g., 1 3 5), then press Enter\n1 = Monday\n2 = Tuesday\n3 = Wednesday\n4 = Thursday\n5 = Friday\n";
            cin.ignore();
            while (cin >> day)
            {
                preferredDays.push_back(day);
                if (cin.peek() == '\n')
                    break;
            }

            vector<ClassInfo> filtered = filterByMultipleCriteria(classDetails, desiredCourseIDs, startTime, endTime, preferredDays);

            cout << "\nFiltered Classes:";
            cout << endl;
            for (const ClassInfo &c : filtered)
            {
                cout << "Course ID: " << c.courseID << "\n";
                cout << "Name: " << c.name << "\n";

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
                cout << "Time: " << startT.substr(0, 2) << ":" << startT.substr(2, 2) << "-" << endT.substr(0, 2) << ":" << endT.substr(2, 2) << endl;
                cout << "Days: ";
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
                        cout << "Unknown ";
                        break;
                    }
                }
                cout << "\nLocation: " << c.location << "\n";
                cout << "------------------------\n";
            }

            // If no classes meet the requirements then display a message
            if (filtered.empty())
            {
                cout << "No classes match your requirments at the moment, please try again";
            }
            else
            {
                Schedule scheduler;
                // Call the greedySchedule function
                vector<vector<ClassInfo>> schedules = scheduler.greedySchedule(filtered);

                // Print out all the suggested schedules
                cout << "\nSuggested Schedules\n\n";
                int scheduleNum = 1;
                for (const auto &schedule : schedules)
                {
                    cout << "Schedule " << scheduleNum++ << ":\n";
                    scheduler.printSchedule(schedule);
                    cout << "--------------------------\n";
                }
            }
        }
        else if (choice == 6)
        {
            // option for exiting the menu
            cout << "Goodbye!\n";
        }
        else
        {
            cout << "Please try again.\n";
        }
    }

    return 0;
}