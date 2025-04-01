#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct ClassInfo {
    string courseID;
    string name;
    string days;
    string startTime;
    string endTime;
    string location; // future implementation
};

// functions
void printClassDetails(const unordered_map<string, ClassInfo>& classes);
void saveToFile(const unordered_map<string, ClassInfo>& classes, const string& filename);
void loadFromFile(unordered_map<string, ClassInfo>& classes, const string& filename);
void addClass(unordered_map<string, ClassInfo>& classes);

#endif