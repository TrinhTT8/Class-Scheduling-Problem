#include "classes.h"
#include <fstream>
#include <sstream>

// display all classes
void printClassDetails(const unordered_map<string, ClassInfo>& classes) {
    if (classes.empty()) {
        cout << "No classes available.\n";
        return;
    }

    cout << "\nClasses:\n";
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        string courseID = it->second.courseID;
        string name = it->second.name;
        int startTime = it->second.startTime;
        int endTime = it->second.endTime;
        vector<int> days = it->second.days;
        string location = it->second.location;

        cout << "- " << courseID << " - " << name << "\n";
        cout << "  Time: " << startTime / 100 << ":" << startTime % 100 
	//display in HH:MM
             << " - " << endTime / 100 << ":" << endTime % 100 << "\n"; 
        cout << "  Days: ";
        for (int day : days) {
            switch (day) {
                case 1: cout << "Monday "; break;
                case 2: cout << "Tuesday "; break;
                case 3: cout << "Wednesday "; break;
                case 4: cout << "Thursday "; break;
                case 5: cout << "Friday "; break;
                default: break;
            }
        }
        cout << "  Location: " << location << "\n\n";
    }
}

// save a class directly to file
void saveToFile(const unordered_map<string, ClassInfo>& classes, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Could not open file for saving.\n";
        return;
    }

    // iterates through classes and saves to file
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        string courseID = it->second.courseID;
        string name = it->second.name;
        vector<int> days = it->second.days;
        int startTime = it->second.startTime;
        int endTime = it->second.endTime;
        string location = it->second.location;

        outFile << courseID << "," << name << ",";
        for (int day : days) {
            outFile << day << " ";
        }
        outFile << startTime << "," << endTime << "," << location << "\n";
    }
    outFile.close();
    cout << "\nSchedule saved to " << filename << " successfully!\n";
}

// load classes from a file
void loadFromFile(unordered_map<string, ClassInfo>& classes, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No classes found in file.\n";
        return;
    }

    string line, courseID, name, daysStr, location;
    int startTime, endTime;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, courseID, ',');
        getline(ss, name, ',');
        getline(ss, daysStr, ',');
        ss >> startTime;
        ss.ignore();
        ss >> endTime;
        getline(ss, location, ',');

        vector<int> days;
        stringstream daysStream(daysStr);
        int day;
        while (daysStream >> day) {
            days.push_back(day);
        }

        classes[courseID] = {courseID, name, days, startTime, endTime, location};
    }
    inFile.close();
    cout << "\nClasses loaded successfully!\n";
}

// add a new class
void addClass(unordered_map<string, ClassInfo>& classes) {
    cin.ignore();
    string courseID, name, daysStr, location;
    int startTime, endTime;

    cout << "\nEnter course ID: ";
    getline(cin, courseID);

    if (classes.find(courseID) != classes.end()) {
        cout << "This course ID already exists. Try a different ID.\n\n";
        return;
    }

    cout << "Enter class name: ";
    getline(cin, name);

    cout << "Enter days the class meets (1=Mon, 2=Tue, 3=Wed, 4=Thu, 5=Fri, spaces between days): ";
    getline(cin, daysStr);
    vector<int> days;
    stringstream ss(daysStr);
    int day;
    while (ss >> day) {
        days.push_back(day);
    }

    cout << "Enter start time (1030 for 10:30): ";
    cin >> startTime;

    cout << "Enter end time (1100 for 11:00): ";
    cin >> endTime;

    cin.ignore();
    cout << "Enter location (DP 201): ";
    getline(cin, location);

    classes[courseID] = {courseID, name, days, startTime, endTime, location};
    cout << "\nClass added successfully!\n";
}

// vector conversion
vector<ClassInfo> convertToVector(const unordered_map<string, ClassInfo>& classes) {
    vector<ClassInfo> classVector;
    for (const auto& entry : classes) {
        classVector.push_back(entry.second);
    }
    return classVector;
}

// map conversion (vector conversion needs to happen first)
unordered_map<string, ClassInfo> convertToMap(const vector<ClassInfo>& classVector) {
    unordered_map<string, ClassInfo> classMap;
    for (const ClassInfo& classInfo : classVector) {
        classMap[classInfo.courseID] = classInfo;
    }
    return classMap;
}

//removing a class
void removeClass(unordered_map<string, ClassInfo>& classes) {
    string courseID;
    cout << "Enter course ID to remove: ";
    cin >> courseID;

    auto it = classes.find(courseID);
    if (it != classes.end()) {
        classes.erase(it);
        cout << "Class removed successfully.\n";
    } else {
        cout << "Class not found.\n";
    }
}

//filtering a class by Course ID
void filterByCourseID(const unordered_map<string, ClassInfo>& classes, const string& keyword) {
    bool found = false;

    for (const auto& [id, info] : classes) {
        if (info.courseID.find(keyword) != string::npos) {
            cout << "Course ID: " << info.courseID << endl;
            cout << "Name: " << info.name << endl;
            cout << "Days: " << info.days << endl;
            cout << "Time: " << info.startTime << " - " << info.endTime << endl;
            cout << "Location: " << info.location << endl;
            cout << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No classes found with course ID containing \"" << keyword << "\".\n";
    }
}
