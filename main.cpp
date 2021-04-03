#include "Student.h"
#include "StudentFile.h"
#include "General.h"
#include "Test.h"

int main(int argc, char* argv[]) {
    vector<student> group;  // student vector
    vector<student> groupGood;  
    vector<student> groupBad;  
    list<student> lgroup;  
    list<student> lgroupGood;  
    list<student> lgroupBad;  
    deque<student> dgroup;  
    deque<student> dgroupGood;  
    deque<student> dgroupBad;  
    string fileName = "test/kursiokai";
    int n;                  // number of students
    bool run = true;        // used for while loops in main
    bool gradeNumber;       // flag for if grade number is known
    char readfile;
    char ansMedian;
    char ansfile;
    const char* dir = "test";

    if (argc > 1 && strcmp(argv[1], "test") == 0)
    {
        _mkdir(dir);
        generateStudents(1000, fileName);
        generateStudents(10000, fileName);
        generateStudents(100000, fileName);
        generateStudents(1000000, fileName);
        generateStudents(10000000, fileName);

        if (argc > 2 && strcmp(argv[2], "vector") == 0)
        {
            testVector(group, groupGood, groupBad, fileName, 1000);
            testVector(group, groupGood, groupBad, fileName, 10000);
            testVector(group, groupGood, groupBad, fileName, 100000);
            testVector(group, groupGood, groupBad, fileName, 1000000);
            testVector(group, groupGood, groupBad, fileName, 10000000);
        }
        else if (argc > 2 && strcmp(argv[2], "list") == 0)
        {
            testList(lgroup, lgroupGood, lgroupBad, fileName, 1000);
            testList(lgroup, lgroupGood, lgroupBad, fileName, 10000);
            testList(lgroup, lgroupGood, lgroupBad, fileName, 100000);
            testList(lgroup, lgroupGood, lgroupBad, fileName, 1000000);
            testList(lgroup, lgroupGood, lgroupBad, fileName, 10000000);
        }
        else if (argc > 2 && strcmp(argv[2], "deque") == 0)
        {
            testDeque(dgroup, dgroupGood, dgroupBad, fileName, 1000);
            testDeque(dgroup, dgroupGood, dgroupBad, fileName, 10000);
            testDeque(dgroup, dgroupGood, dgroupBad, fileName, 100000);
            testDeque(dgroup, dgroupGood, dgroupBad, fileName, 1000000);
            testDeque(dgroup, dgroupGood, dgroupBad, fileName, 10000000);
        }
        else 
        {
            exit(0);
        }
            
    }
    else
    {
        cout << "Get students from file or enter manually?(f/m): ";
        do {
            cin >> readfile;
            if (std::toupper(readfile) == 'F')
            {
                cout << "Use exiting file or generate?(e/g): ";
                do {
                    cin >> ansfile;
                    if (std::toupper(ansfile) == 'E')
                    {
                        cout << "Use median for final grade?(y/n): ";
                        do {
                            cin >> ansMedian;
                            if (std::toupper(ansMedian) == 'Y')
                            {
                                bufferRead(group);
                                auto start2 = std::chrono::high_resolution_clock::now();
                                cout << "Calculating..." << endl;
                                finalGradeMedian(group, group.size());
                                std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now() - start2;
                                std::cout << "Calculating took " << diff2.count() << " s" << endl;
                                auto start3 = std::chrono::high_resolution_clock::now();
                                cout << "Writing..." << endl;
                                writeToFile(group, group.size(), true);
                                run = false;
                                std::chrono::duration<double> diff3 = std::chrono::high_resolution_clock::now() - start3;
                                std::cout << "Writing took " << diff3.count() << " s" << endl;
                            }
                            else if (std::toupper(ansMedian) == 'N')
                            {
                                bufferRead(group);
                                auto start2 = std::chrono::high_resolution_clock::now();
                                cout << "Calculating..." << endl;
                                finalGradeAverage(group, group.size());
                                std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now() - start2;
                                std::cout << "Calculating took " << diff2.count() << " s" << endl;
                                auto start3 = std::chrono::high_resolution_clock::now();
                                cout << "Writing..." << endl;
                                writeToFile(group, group.size(), false);
                                run = false;
                                std::chrono::duration<double> diff3 = std::chrono::high_resolution_clock::now() - start3;
                                std::cout << "Writing took " << diff3.count() << " s" << endl;
                            }
                            else
                            {
                                cout << endl;
                                cout << "Error: bad entry" << endl;
                                cout << "Try again(y/n): ";
                                run = true;
                            }
                        } while (run);
                        run = false;
                    }
                    else if (std::toupper(ansfile) == 'G')
                    {
                        
                        generateStudents();
                        bufferRead(group);

                        auto start2 = std::chrono::high_resolution_clock::now();
                        cout << "Calculating..." << endl;

                        finalGradeMedian(group, group.size());

                        std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now() - start2;
                        std::cout << "Calculating took " << diff2.count() << " s" << endl;
                        cout << "Sorting..." << endl;
                        auto start = std::chrono::high_resolution_clock::now();

                        sortStudents(group, groupGood, groupBad);

                        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
                        std::cout << "Sorting took " << diff.count() << " s" << endl;
                        auto start3 = std::chrono::high_resolution_clock::now();
                        cout << "Writing..." << endl;

                        writeToFile(groupGood, groupBad, false);

                        std::chrono::duration<double> diff3 = std::chrono::high_resolution_clock::now() - start3;
                        std::cout << "Writing took " << diff3.count() << " s" << endl;
                        run = false;
                        
                    }
                    else
                    {
                        cout << endl;
                        cout << "Error: bad entry" << endl;
                        cout << "Try again(y/n): ";
                        run = true;
                    }
                } while (run);
            }
            else if (std::toupper(readfile) == 'M')
            {
                cout << "Enter the number of students: ";

                do
                {
                    try
                    {
                        n = std::stoi(getDigits());
                        run = false;
                    }
                    catch (std::exception& e)
                    {
                        cout << "Error: number entered is to big." << endl;
                        cout << "Try again: ";
                        run = true;
                    }
                } while (run);

                for (int i = 0; i < n; i++)
                {
                    group.push_back(student());

                    cout << "Enter students first name: ";
                    do {
                        cin >> group[i].firstName;
                        cout << endl;
                    } while (!validateName(group[i].firstName));

                    cout << "Enter students last name: ";
                    do {
                        cin >> group[i].lastName;
                        cout << endl;
                    } while (!validateName(group[i].lastName));

                    char ansGrade;
                    cout << "Is the number of grades known?(y/n): ";
                    do {
                        cin >> ansGrade;
                        if (std::toupper(ansGrade) == 'Y')
                        {
                            int temp;
                            cout << "Enter the number of grades: ";
                            do {
                                do {
                                    try
                                    {
                                        temp = std::stoi(getDigits());
                                        run = false;
                                    }
                                    catch (std::exception& e)
                                    {
                                        cout << "Error: number entered is to big." << endl;
                                        cout << "Try again: ";
                                        run = true;
                                    }
                                } while (run);

                                if (temp > 0)
                                {
                                    group[i].homeworkSize = temp;
                                    run = false;
                                }
                                else
                                {
                                    cout << "Error! the number of grades cant be 0" << endl;
                                    cout << "Try to enter your number again: ";
                                    run = true;
                                }
                            } while (run);
                            gradeNumber = true;
                        }
                        else if (std::toupper(ansGrade) == 'N')
                        {
                            cout << endl;
                            gradeNumber = false;
                            run = false;
                        }
                        else
                        {
                            cout << endl;
                            cout << "Error: bad entry" << endl;
                            cout << "Try again(y/n): ";
                            run = true;
                        }
                    } while (run);

                    char ansRandom;
                    cout << "Generate grades randomly?(y/n): ";
                    do {
                        cin >> ansRandom;
                        if (std::toupper(ansRandom) == 'Y')
                        {
                            cout << endl;
                            generateGrades(gradeNumber, group[i]);
                            run = false;
                        }
                        else if (std::toupper(ansRandom) == 'N')
                        {
                            homeworkGrades(gradeNumber, group[i]);
                            cout << endl << "Enter students exam grade: ";
                            group[i].examGrade = getExam();
                            run = false;
                        }
                        else
                        {
                            cout << endl;
                            cout << "Error: bad entry" << endl;
                            cout << "Try again(y/n): ";
                            run = true;
                        }
                    } while (run);
                }
                group.shrink_to_fit();

                cout << "Use median for final grade?(y/n): ";
                do {
                    cin >> ansMedian;
                    if (std::toupper(ansMedian) == 'Y')
                    {
                        finalGradeMedian(group, n);
                        print(group, n, true);
                        run = false;
                    }
                    else if (std::toupper(ansMedian) == 'N')
                    {
                        finalGradeAverage(group, n);
                        print(group, n, false);
                        run = false;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Error: bad entry" << endl;
                        cout << "Try again(y/n): ";
                        run = true;
                    }
                } while (run);
                run = false;
            }
            else
            {
                cout << endl;
                cout << "Error: bad entry" << endl;
                cout << "Try again(f/m): ";
            }
        } while (run);
        system("pause");
    }
}


