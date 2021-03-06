#ifndef STUDENTFILE_H_INCLUDED
#define STUDENTFILE_H_INCLUDED

#include "Student.h"
#include "General.h"

void bufferRead(vector<student>&);

void writeToFile(vector<student>&, int, bool);
void writeToFile(vector<student>&, vector<student>&, bool);

void generateStudents();

bool compareByLastName(const student&, const student&);
bool compareByFinalGrade(const student&, const student&);
bool isGood(const student&);

void sortStudents(list<student>&, list<student>&, list<student>&);
void sortStudents2(list<student>&, list<student>&);

template <class T>
void sortStudents(T& group, T& groupGood, T& groupBad) {

    std::sort(group.begin(), group.end(), compareByFinalGrade);
    auto it = std::find_if(group.begin(), group.end(), isGood);

    std::copy(it, group.end(), std::back_inserter(groupGood));
    std::copy(group.begin(), it, std::back_inserter(groupBad));

    std::sort(groupGood.begin(), groupGood.end(), compareByLastName);
    std::sort(groupBad.begin(), groupBad.end(), compareByLastName);
}


template <class T>
void sortStudents2(T& groupBad, T& groupGood) {

    std::sort(groupBad.begin(), groupBad.end(), compareByFinalGrade);
    auto it = std::find_if(groupBad.begin(), groupBad.end(), isGood);

    std::copy(it, groupBad.end(), std::back_inserter(groupGood));

    groupBad.erase(it, groupBad.end());

    std::sort(groupGood.begin(), groupGood.end(), compareByLastName);
    std::sort(groupBad.begin(), groupBad.end(), compareByLastName);
}
#endif // STUDENTFILE_H_INCLUDED