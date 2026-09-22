
#include <iostream>
using namespace std;

int main()
{
    const int STUDENTS = 6;
    const int SUBJECTS = 4;
    string subjectNames[SUBJECTS] = {"English", "Mathematics", "Programming", "AI"};

    // Create and initialize the 2D array with marks of 6 students in 4 subjects
    int marks[STUDENTS][SUBJECTS] = {
        {78, 85, 90, 88},
        {65, 70, 60, 75},
        {90, 95, 88, 92},
        {55, 60, 65, 58},
        {82, 79, 91, 85},
        {70, 68, 75, 72}
    };

    

    cout << "Student\t";
    for (int j = 0; j < SUBJECTS; j++)
        cout << subjectNames[j] << "\t";
    cout << endl;

    for (int i = 0; i < STUDENTS; i++)
    {
        cout << "S" << (i + 1) << "\t";
        for (int j = 0; j < SUBJECTS; j++)
        {
            cout << marks[i][j] << "\t\t";
        }
        cout << endl;
    }


    int totalMarks[STUDENTS];
    float averageMarks[STUDENTS];


    for (int i = 0; i < STUDENTS; i++)
    {
        int sum = 0;
        for (int j = 0; j < SUBJECTS; j++)
        {
            sum += marks[i][j];
        }
        totalMarks[i] = sum;
        averageMarks[i] = (float)sum / SUBJECTS;

        cout << "Student S" << (i + 1)
             << " -> Total: " << totalMarks[i]
             << ", Average: " << averageMarks[i] << endl;
    }

  
    for (int j = 0; j < SUBJECTS; j++)
    {
        int highest = marks[0][j];
        int topStudent = 0;
        for (int i = 1; i < STUDENTS; i++)
        {
            if (marks[i][j] > highest)
            {
                highest = marks[i][j];
                topStudent = i;
            }
        }
        cout << subjectNames[j] << " -> Highest: " << highest
             << " (Student S" << (topStudent + 1) << ")" << endl;
    }

    // 6. Find and display the student with the highest total marks
    int bestStudent = 0;
    int bestTotal = totalMarks[0];
    for (int i = 1; i < STUDENTS; i++)
    {
        if (totalMarks[i] > bestTotal)
        {
            bestTotal = totalMarks[i];
            bestStudent = i;
        }
    }

    
    cout << "Student S" << (bestStudent + 1)
         << " with Total Marks = " << bestTotal << endl;

    return 0;
}
