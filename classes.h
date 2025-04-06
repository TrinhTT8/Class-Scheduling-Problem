#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct ClassInfo {
    string courseID;
    string name;
    vector<int> days;
    string startTime;   // Need to adjust this to number type so we can compare
    string endTime;     // Need to adjust this to number type so we can compare
    string location; // future implementation
};

// functions
void printClassDetails(const unordered_map<string, ClassInfo>& classes);
void saveToFile(const unordered_map<string, ClassInfo>& classes, const string& filename);
void loadFromFile(unordered_map<string, ClassInfo>& classes, const string& filename);
void addClass(unordered_map<string, ClassInfo>& classes);
vector<ClassInfo> convertToVector(const unordered_map<string, ClassInfo>& classes);
unordered_map<string, ClassInfo> convertToMap(const vector<ClassInfo>& classVector);
void removeClass(unordered_map<string, ClassInfo>& classes);
void filterByCourseID(const unordered_map<string, ClassInfo>& classes, const string& keyword);


#endif
