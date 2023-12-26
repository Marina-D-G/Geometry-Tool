//**
//*
//* Solution to course project 8
//* Introduction to programming course
//* Faculty of Mathematics and Informatics of Sofia University
//* Winter semester 2023 / 2024
//*
//*@author Marina Gospodinova
//* @idnumber 1MI0600337
//* @compiler VC
//*
//*Main Program
//*
//*/


#include <iostream>
#include <cmath>

int main()
{
    struct Point { double x, y; }; // x and y are the coordinates of the point
    struct Line { Point a, b; }; // a and b are the points that define the line
    short choice;

    do {
        std::cout << "Select an operation (by entering its number):" << std::endl;
        std::cout << "1. Input a point" << std::endl;
        std::cout << "2. Input a line" << std::endl;
        std::cout << "3. Determine if a point lies on a line" << std::endl;
        std::cout << "4. Find the equation of a line that is parallel to a given line and passes through a given point" << std::endl;
        std::cout << "5. Find the equation of a line that is perpendicular to a given line through a given point" << std::endl;
        std::cout << "6. Find the intersection point of two lines" << std::endl;
        std::cout << "7. Find the equations of the altitudes in triangle" << std::endl;
        std::cout << "8. Find the equations of the medians in triangle" << std::endl;
        std::cout << "9. Find the equations of the perpendicular bisectors in triangle" << std::endl;
        std::cout << "10. Find the equation of a tangent to a parabola at a given point on the real line" << std::endl;
        std::cout << "11. Find intersection points of parabola and line" << std::endl;
        std::cout << "12. Determine the type of the quadrilateral formed by four given lines" << std::endl;
        std::cout << "13. Exit" << std::endl;

        std::cin >> choice;

    } while (choice != '13');

    return 0;
}