#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct ClassInfo
{
    string courseID;
    string name;
    vector<int> days; // 1 for Monday, 2 for Tuesday, etc until 5 is Friday
    int startTime;    // 1000 is 10:00
    int endTime;      // 11000 is 11:00
    string location;  // future implementation
};

// functions
void printClassDetails(const unordered_map<string, vector<ClassInfo>> &classes);
void saveToFile(const unordered_map<string, vector<ClassInfo>> &classes, const string &filename);
void loadFromFile(unordered_map<string, vector<ClassInfo>> &classes, const string &filename);
void addClass(unordered_map<string, vector<ClassInfo>> &classes);
vector<ClassInfo> convertToVector(const unordered_map<string, vector<ClassInfo>> &classes);
unordered_map<string, vector<ClassInfo>> convertToMap(const vector<ClassInfo> &classVector);
string toUpper(const string &str);
void removeClass(unordered_map<string, vector<ClassInfo>> &classes);
vector<ClassInfo> filterByMultipleCriteria(
    const unordered_map<string, vector<ClassInfo>> &classes,
    const vector<string> &desiredCourseIDs,
    int preferredStartTime,
    int preferredEndTime,
    const vector<int> &preferredDays);

#endif