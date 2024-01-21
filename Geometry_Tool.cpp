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

const double EPSILON = 0.000001; //10^(-6), for numerical precision with float numbers
const int SIZE = 100; //for the size of names

struct Point { double x; double y; char pointName[SIZE]; }; // x and y are the coordinates of the point
struct Line { double a; double b; double c; char lineName[SIZE]; double m; double k; }; // ax+by+c=0 - general equation of line, y=mx+k - Cartesian equation

bool isNameValid(char* name) //checks if name is valid
{
	if (!name) //check for nullptr
	{
		return false;
	}

	while (*name)
	{
		if (!((*name >= 'a' && *name <= 'z') || (*name >= 'A' && *name <= 'Z') || (*name >= '0' && *name <= '9') || *name == '_'))
			//valid characters are the Arabic numerals, the letters of the Latin alphabet and the underscore
		{
			return false;
		}
		name++;
	}
	return true;
}

bool equalNames(char* name1, char* name2)
{
	for (int i = 0; name1[i]&&name2[i]; i++)
	{
		if (name1[i] != name2[i])
		{
			return false;
		}
	}
	return true;
}

bool isPointExist(Point* pointRecord, Point& point_temp, int& filledPoints)
{
	for (int i = 0; i < filledPoints; i++)
	{
		if (equalNames(pointRecord[i].pointName, point_temp.pointName))
		{
			point_temp = pointRecord[i]; //if it exists, we will work with it
			return true;
		}
	}
	return false;
}

bool isLineExist(Line* lineRecord, Line& line_temp, int& filledLines)
{
	for (int i = 0; i < filledLines; i++)
	{
		if (equalNames(lineRecord[i].lineName, line_temp.lineName))
		{
			line_temp = lineRecord[i]; //if it exists, we will work with it
			return true;
		}
	}
	return false;
}

bool isTriangleExist(Point point1, Point point2, Point point3)
//we can find out if triangle exists by calculating its area, if it is zero-it doesn't exist
{
	double area = 0.5*(point1.x*(point2.y-point3.y) + point2.x * (point3.y - point1.y) + point3.x * (point1.y - point2.y));
	return area;
}

Line lineThroughTwoPoints(Point point1, Point point2)
{
	Line line_temp{};
	line_temp.m = (point2.y - point1.y) / (point2.x - point1.x);
	line_temp.a = point1.y - point2.y;
	line_temp.b = point2.x - point1.x;
	line_temp.c = point1.x * point2.y - point2.x * point1.y;
	return line_temp;
}

Line altitude(Point p1, Point p2, Point h)
//the altitude is from h to the line that goes through p1 and p2
{
	Line line_temp = lineThroughTwoPoints(p1, p2); 
	Line altitude {};
	altitude.m = -1.0 / line_temp.m;
	altitude.a = altitude.m;
	altitude.b = 1.0;
	altitude.c = h.y - altitude.m * h.x;
	return altitude;
}

Line median(Point p1, Point p2, Point m)
//the median is from m to the midpoint between p1 and p2
{
	Point midpoint{};
	midpoint.x = (p1.x + p2.x) / 2.0;
	midpoint.y = (p1.y + p2.y) / 2.0;
	Line median = lineThroughTwoPoints(midpoint, m);
	return median;
}

Line perpBisector(Point p1, Point p2)
//the perpendicular bisector is the line that is perpendicular to the line through p1 and p2 and goes through its midpoint
{
	Line line_temp = lineThroughTwoPoints(p1, p2);
	Point midpoint{};
	midpoint.x = (p1.x + p2.x) / 2.0;
	midpoint.y = (p1.y + p2.y) / 2.0;

	Line perpBisector{};
	perpBisector.m = -1.0 / line_temp.m;
	perpBisector.k = midpoint.y - perpBisector.m * midpoint.x;
	perpBisector.a = -perpBisector.m;
	perpBisector.b = 1.0;
	perpBisector.c = -perpBisector.k;

	return perpBisector;
}

void inputPoint(Point* pointRecord, int& filledPoints) //define a geometric point with its coordinates
{
	if (!pointRecord) //check for nullptr
	{
		return;
	}

	Point point_temp {};
	std::cout << "Please, input the coordinates of a point:";
	std::cin >> point_temp.x >> point_temp.y;

	std::cout << "Please, input a name for the point:";
	std::cin>>point_temp.pointName;

	while (!isNameValid(point_temp.pointName)) //if the name is not valid ask for a new name
	{
		std::cout << "Invalid input, please input another name: ";
		std::cin >> point_temp.pointName;
	}
	*(pointRecord + filledPoints) = point_temp;
	filledPoints++;  //when the name is valid, enter the point in the array with all points, increased by one the number of entered
	std::cout << "You've input a point " << point_temp.pointName << "(" << point_temp.x << ", " << point_temp.y << ")" << std::endl;
}

void inputLine(Line* lineRecord, int& filledLines) //define a geometric line with its coefficients
{
	if (!lineRecord) //check for nullptr
	{
		return;
	}

	Line line_temp {};
	std::cout << "Please, input the coefficients of a line: ";
	std::cin >> line_temp.a >> line_temp.b >> line_temp.c;
	line_temp.m = -line_temp.a / line_temp.b;
	line_temp.k = -line_temp.c / line_temp.b; //m and k for Cartesian form

	std::cout << "Please, input a name for the line: ";
	std::cin >> line_temp.lineName;

	while (!isNameValid(line_temp.lineName)) //if the name is not valid ask for a new name
	{
		std::cout << "Invalid input, please input another name: ";
		std::cin >> line_temp.lineName;
	}
	*(lineRecord + filledLines) = line_temp; //when the name is valid, enter the line in the array with all lines
	filledLines++; //increase by one the number of entered
	std::cout << "You've input a line " << line_temp.lineName << ": " << line_temp.a << "x + " << line_temp.b << "y + " << line_temp.c << std::endl;
}

Point choosePoint(Point* pointRecord, int& filledPoints)
{
	Point point_temp{};
	if (!filledPoints) //if we dont have any points
	{
		inputPoint(pointRecord, filledPoints);
		point_temp = *pointRecord; //the point is the only one we have
	}
	else
	{
		std::cout << "Please, enter a point (by its name):" << std::endl;
		std::cin >> point_temp.pointName;

		while (!isPointExist(pointRecord, point_temp, filledPoints)) //record the point while checking if it exists already
		{
			std::cout << "Invalid input, please input another point: ";
			std::cin >> point_temp.pointName;
		}
	}
	return point_temp;
}

void chooseThreeValidPoints(Point* pointRecord, int& filledPoints, Point& point1, Point& point2, Point& point3)
{
	point1 = choosePoint(pointRecord, filledPoints);
	switch (filledPoints) //to choose 3 valid points
	{
	case 1:
		inputPoint(pointRecord, filledPoints);
		point2 = pointRecord[1];
		inputPoint(pointRecord, filledPoints);
		point3 = pointRecord[2];
		break;
	case 2:
		inputPoint(pointRecord, filledPoints);
		point3 = pointRecord[2];
		break;
	default:
		point2 = choosePoint(pointRecord, filledPoints);
		point3 = choosePoint(pointRecord, filledPoints);
		break;
	}
}

Line chooseLine(Line* lineRecord, int& filledLines)
{
	Line line_temp{};
	if (!filledLines) //if we dont have any points
	{
		inputLine(lineRecord, filledLines);
		line_temp = *lineRecord; //the line is the only one we have
	}
	else
	{
		std::cout << "Please, enter a line (by its name):" << std::endl;
		std::cin >> line_temp.lineName;

		while (!isLineExist(lineRecord, line_temp, filledLines)) //record the line while checking if it exists already
		{
			std::cout << "Invalid input, please input another point: ";
			std::cin >> line_temp.lineName;
		}
	}
	return line_temp;
}

void isPointOnLine(Point pointRecord[], Line lineRecord[], int& filledPoints, int& filledLines) //determines if a point lies on a line
{
	Point point = choosePoint(pointRecord, filledPoints);
	Line line = chooseLine(lineRecord, filledLines);

	if ((line.a * point.x + line.b * point.y + line.c) < EPSILON) //  ax+by+c<EPSILON (we use epsilon for floating-point precision)
	{
		std::cout << "Yes, the point " << point.pointName << " lies on line " << line.lineName;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "No, the point " << point.pointName << " does not lie on line " << line.lineName;
		std::cout << std::endl;
	}
}

void equationOfParallelLine(Point pointRecord[], Line lineRecord[], int& filledPoints, int& filledLines)
{
	Point point = choosePoint(pointRecord, filledPoints);
	Line line = chooseLine(lineRecord, filledLines);

	double k_new = point.y - line.m * point.x; //find out the new k from the x and y from the given point
	if (k_new == line.k)
	{
		std::cout << "The point lies on the line already. The requested parallel line is the same as the given.";
		return;
	}

	std::cout << "The equation of a line that is parallel to the given line and passes through the given point is: ";
	std::cout << -line.m << "x + y + " << -k_new << " = 0" << std::endl;
	//the parralel line has the same slope and the new k
}

void equationOfPerpendicularLine(Point pointRecord[], Line lineRecord[], int& filledPoints, int& filledLines)
{
	Point point = choosePoint(pointRecord, filledPoints);
	Line line = chooseLine(lineRecord, filledLines);

	double m_new = -1.0 / line.m;
	double k_new = point.y - m_new * point.x; //find out the new k from the x and y from the given point

	std::cout << "The equation of a line that is perpendicular to the given line and passes through the given point is: ";
	std::cout << -m_new << "x + y + " << -k_new << " = 0" << std::endl;
}

void intersectionOfTwoLines(Line lineRecord[], int& filledLines)
{
	Line line1 = chooseLine(lineRecord, filledLines);
	Line line2{};
	if (filledLines == 1)
	{
		inputLine(lineRecord, filledLines);
		line2 = lineRecord[1]; //the element on first index is exactly the one we entered if the lines are not enough
	}
	else
	{
		line2 = chooseLine(lineRecord, filledLines);
	}
	Point point{};

	if (line1.m == line2.m)
	{
		std::cout << "The lines are parallel and do not intersect." << std::endl;
		return;
	}

	point.x = (line2.k - line1.k) / (line1.m - line2.m);
	point.y = line1.m * point.x + line1.k;

	std::cout << "The intersection point of the lines is (" << point.x << ", " << point.y << ")";
}

void equationsOfAltitudes(Point pointRecord[], Line lineRecord[], int& filledPoints, int& filledLines)
{
	Point point1{};
	Point point2{};
	Point point3{};
	chooseThreeValidPoints(pointRecord, filledPoints, point1, point2, point3);
	if (!isTriangleExist(point1, point2, point3))
	{
		std::cout << "Тhese three points do not form a triangle.";
		return;
	}
	std::cout << std::endl;

	Line altitudeFrom1 = altitude(point2, point3, point1); //altitude that goes from point1 to line through point2 and point3
	std::cout << "The equation of the altitude that goes from " << point1.pointName << " in the triangle is: ";
	std::cout << altitudeFrom1.a << "x - " << altitudeFrom1.b << "y + " << altitudeFrom1.c << " = 0" << std::endl;
	std::cout << std::endl;

	Line altitudeFrom2 = altitude(point1, point3, point2); //altitude that goes from point2 to line through point1 and point3
	std::cout << "The equation of the altitude that goes from " << point2.pointName << " in the triangle is: ";
	std::cout << altitudeFrom2.a << "x - " << altitudeFrom2.b << "y + " << altitudeFrom2.c << " = 0" << std::endl;
	std::cout << std::endl;

	Line altitudeFrom3 = altitude(point1, point2, point3); //altitude that goes from point3 to line through point1 and point2
	std::cout << "The equation of the altitude that goes from " << point3.pointName << " in the triangle is: ";
	std::cout << altitudeFrom3.a << "x - " << altitudeFrom3.b << "y + " << altitudeFrom3.c << " = 0" << std::endl;
	std::cout << std::endl;
}

void equationsOfMedians(Point pointRecord[], Line lineRecord[], int& filledPoints, int& filledLines)
{
	Point point1{};
	Point point2{};
	Point point3{};
	chooseThreeValidPoints(pointRecord, filledPoints, point1, point2, point3);
	if (!isTriangleExist(point1, point2, point3)) 
	{
		std::cout << "Тhese three points do not form a triangle.";
		return;
	}
	std::cout << std::endl;

	Line medianFrom1 = median(point2, point3, point1); //the median that is from point1 to the line through point2 and point3
	std::cout << "The equation of the median that goes from " << point1.pointName << " in the triangle is: ";
	std::cout << medianFrom1.a << "x + " << medianFrom1.b << "y + " << medianFrom1.c << " = 0" << std::endl;
	std::cout << std::endl;

	Line medianFrom2 = median(point1, point3, point2); //the median that is from point2 to the line through point1 and point3
	std::cout << "The equation of the median that goes from " << point2.pointName << " in the triangle is: ";
	std::cout << medianFrom2.a << "x + " << medianFrom2.b << "y + " << medianFrom2.c << " = 0" << std::endl;
	std::cout << std::endl;

	Line medianFrom3 = median(point1, point2, point3); //the median that is from point3 to the line through point1 and point2
	std::cout << "The equation of the median that goes from " << point3.pointName << " in the triangle is: ";
	std::cout << medianFrom3.a << "x + " << medianFrom3.b << "y + " << medianFrom3.c << " = 0" << std::endl;
	std::cout << std::endl;
}

void equationsOfperpendicularBisectors(Point pointRecord[], Line lineRecord[], int& filledPoints, int& filledLines)
{
	Point point1{};
	Point point2{};
	Point point3{};
	chooseThreeValidPoints(pointRecord, filledPoints, point1, point2, point3);
	if (!isTriangleExist(point1, point2, point3))
	{
		std::cout << "Тhese three points do not form a triangle.";
		return;
	}
	std::cout << std::endl;

	Line perpBisectorThrough12 = perpBisector(point1, point2); //the perpendicular bisector that passes the line through point1 and point2
	std::cout << "The equation of the perpendicular bisector that passes the line through " << point1.pointName << " and "<<point2.pointName <<" in the triangle is: ";
	std::cout << perpBisectorThrough12.a << "x + " << perpBisectorThrough12.b << "y + " << perpBisectorThrough12.c << " = 0" << std::endl;
	std::cout << std::endl;

	Line perpBisectorThrough23 = perpBisector(point2, point3); //the perpendicular bisector that passes the line through point2 and point3
	std::cout << "The equation of the perpendicular bisector that passes the line through " << point2.pointName << " and " << point3.pointName << " in the triangle is: ";
	std::cout << perpBisectorThrough23.a << "x + " << perpBisectorThrough23.b << "y + " << perpBisectorThrough23.c << " = 0" << std::endl;
	std::cout << std::endl;

	Line perpBisectorThrough31 = perpBisector(point3, point1); //the perpendicular bisector that passes the line through point3 and point1
	std::cout << "The equation of the perpendicular bisector that passes the line through " << point3.pointName << " and " << point1.pointName << " in the triangle is: ";
	std::cout << perpBisectorThrough31.a << "x + " << perpBisectorThrough31.b << "y + " << perpBisectorThrough31.c << " = 0" << std::endl;
	std::cout << std::endl;
}
int main()
{
	Point pointRecord[SIZE];
	int filledPoints = 0; //the number of the entered points

	Line lineRecord[SIZE];
	int filledLines = 0; //the number of the entered lines

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

		switch (choice)
		{
		case 1:
			inputPoint(pointRecord, filledPoints);
			std::cout << std::endl;
			break;
		case 2:
			inputLine(lineRecord, filledLines);
			std::cout << std::endl;
			break;
		case 3:
			isPointOnLine(pointRecord, lineRecord, filledPoints, filledLines);
			std::cout << std::endl;
			break;
		case 4:
			equationOfParallelLine(pointRecord, lineRecord, filledPoints, filledLines);
			std::cout << std::endl;
			break;
		case 5:
			equationOfPerpendicularLine(pointRecord, lineRecord, filledPoints, filledLines);
			std::cout << std::endl;
			break;
		case 6:
			intersectionOfTwoLines(lineRecord, filledLines);
			std::cout << std::endl;
			break;
		case 7:
			equationsOfAltitudes(pointRecord, lineRecord, filledPoints, filledLines);
			std::cout << std::endl;
			break;
		case 8:
			equationsOfMedians(pointRecord, lineRecord, filledPoints, filledLines);
			std::cout << std::endl;
			break;
		case 9:
			equationsOfperpendicularBisectors(pointRecord, lineRecord, filledPoints, filledLines);
			std::cout << std::endl;
			break;
		case 10:
			break;
		case 11:
			std::cout << "test";
			break;
		case 12:
			break;
		case 13:
			std::cout << "Have a nice day!";
			break;
		default:
			std::cout << "Please enter a valid option!" << std::endl;
			std::cout << std::endl;
			break;
		}

	} while (choice != 13);

	return 0;
}
