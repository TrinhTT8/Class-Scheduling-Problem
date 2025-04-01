#include "classes.h"
#include <fstream>
#include <sstream>

// display all classes
void printClassDetails(const unordered_map<string, ClassInfo>& classes) {
    if (classes.empty()) {
        cout << "No classes available. Please add a class first.\n";
        return;
    }

    cout << "\nClasses:\n";
    for (auto it = classes.begin(); it != classes.end(); ++it) {
		string courseID = it->second.courseID;
		string name = it->second.name;
		string startTime = it->second.startTime;
		string endTime = it->second.endTime;
		string days = it->second.days;
		string location = it->second.location;
		
		cout << "- " << courseID << " - " << name << "\n";
		cout << "  Time: " << startTime << " - " << endTime << "\n";
		cout << "  Days: " << days << "\n";
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
	
	//iterates through  classes until end and saves to file
    for (auto it = classes.begin(); it != classes.end(); ++it) {
		string courseID = it->second.courseID;
		string name = it->second.name;
		string days = it->second.days;
		string startTime = it->second.startTime;
		string endTime = it->second.endTime;
		string location = it->second.location;

		outFile << courseID << ",";
		outFile << name << ",";
		outFile << days << ",";
		outFile << startTime << ",";
		outFile << endTime << ",";
		outFile << location << "\n";
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

    string line, courseID, name, days, startTime, endTime, location;
    while (getline(inFile, line)) {
        stringstream ss(line);
        getline(ss, courseID, ',');
        getline(ss, name, ',');
        getline(ss, days, ',');
        getline(ss, startTime, ',');
        getline(ss, endTime, ',');
        getline(ss, location, ',');
        classes[courseID] = {courseID, name, days, startTime, endTime, location};
    }
    inFile.close();
    cout << "\nClasses loaded successfully!\n";
}

// add a new class
void addClass(unordered_map<string, ClassInfo>& classes) {
    cin.ignore();
    string courseID, name, days, startTime, endTime, location;
    
    cout << "\nEnter course ID: ";
    getline(cin, courseID);
    
    if (classes.find(courseID) != classes.end()) {
        cout << "This course ID already exists. Try a different ID.\n\n";
        return;
    }
    
    cout << "Enter class name: ";
    getline(cin, name);

    cout << "Enter days the class meets (Mon/Wed/Fri): ";
    getline(cin, days);

    cout << "Enter start time (10:00 AM): ";
    getline(cin, startTime);

    cout << "Enter end time (11:30 AM): ";
    getline(cin, endTime);

    cout << "Enter location (DP 201): ";
    getline(cin, location);

    classes[courseID] = {courseID, name, days, startTime, endTime, location};
    cout << "\nClass added successfully!\n";
}
