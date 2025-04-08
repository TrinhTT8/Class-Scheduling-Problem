#include <iostream>
#include <unordered_map>
#include "classes.h"

using namespace std;

int main() {
    unordered_map<string, ClassInfo> classDetails;
    string filename = "classes.txt";

    //load classes from file
    loadFromFile(classDetails, filename);

    int choice = 0;

    while (choice != 6) {
        cout << "\n1. View Class Details\n";
        cout << "2. Add a New Class\n";
        cout << "3. Search for Class by Course ID\n";
        cout << "4. Remove a Class\n";
        cout << "5. Filter for Class by Course ID\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
			//show all classes
            printClassDetails(classDetails);
        } 
        else if (choice == 2) {
			//add new class
            addClass(classDetails);
            saveToFile(classDetails, filename);
        } 
        else if (choice == 3) {
	    string searchID;
	    cout << "Enter course ID: ";
	    cin.ignore();
	    getline(cin, searchID);
	
	    if (classDetails.find(searchID) != classDetails.end()) {
	        const ClassInfo& classInfo = classDetails[searchID];
	        cout << "\nClass Found:\n";
	        cout << "Course ID: " << classInfo.courseID << "\n";
	        cout << "Name: " << classInfo.name << "\n";
	        cout << "Time: " << classInfo.startTime << " - " << classInfo.endTime << "\n";
	        cout << "Days: ";
	        for (int day : classInfo.days) {
	            switch (day) {
	                case 1: cout << "Monday "; break;
	                case 2: cout << "Tuesday "; break;
	                case 3: cout << "Wednesday "; break;
	                case 4: cout << "Thursday "; break;
	                case 5: cout << "Friday "; break;
	                default: cout << "Unknown "; break;
	            }
	        }
	        cout << "\n";
	        cout << "Location: " << classInfo.location << "\n";
	    } else {
	        cout << "Class with ID " << searchID << " not found.\n";
	    }
	}

        else if (choice == 4) {
            removeClass(classDetails);
            saveToFile(classDetails, filename);
        }
        else if (choice == 5) {
            string keyword;
            cout << "Enter part of the course ID to search: ";
            cin >> keyword;
            filterByCourseID(classDetails, keyword);
        }
        else if (choice == 6) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Please try again.\n";
        }
    }

    return 0;
}
