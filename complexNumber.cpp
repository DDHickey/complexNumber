#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdio.h>
#include <math.h>

#define PI  3.14159265

using namespace std;

int countLines();
void clearSceen();
double rectToR(double xValue, double yValue);
double rectToTheta(double xValue, double yValue);
void printMenu(string words[], int i);
void printSelectionType(string type, string xDetails, string yDetails);
void inputCoords(string xDetails, string yDetails);
bool readfromFile(string words[]);

int main(){

	// Initializing the different type of variables for the program.

	int count = countLines();
	int i = 0;
	double xValue, yValue, theta = 0.0;
	bool execute = false;
	string eachLine[count];
	string confirmed,accepted,type,xDetails,yDetails, polarSign = "";
	
	// Print the menu for the program.
	readfromFile(eachLine);
	printMenu(eachLine,i);


// While loop that will allow you to cycle between the types of coordinates.

	while (execute == false)
	{
cin >> accepted;

// Move right
if (accepted == "a" || accepted == "A"){
	i -= 2;
	if (i == -2){
		i = 6;
	}
	clearSceen();
	printMenu(eachLine,i);
	cout << endl;
}
// Move Left
else if (accepted == "d" || accepted == "D"){
	i += 2;
	if (i == 8){
		i = 0;
	}
	clearSceen();
	printMenu(eachLine,i);
	cout << endl;
}
// Execute selected option.
else if (accepted == "y" || accepted == "Y"){
	clearSceen();
	// Polar
	if (i == 0)
	{
		type = "Polar";
		xDetails = "r";
		yDetails = "θ";

	}
	// Rectangular
	else if( i == 2)
	{
		type = "Rectangular";
		xDetails = "x";
		yDetails = "y";

	}
	// Complex
	else if (i == 4)
	{
		type = "Complex";
		xDetails = "real";
		yDetails = "imaginary";
		
	}
	else if(i == 6){
		cout << "Now Closing!" << endl;
		exit(1);
	}
	execute = true;
}
// If input is not A, D or Y.
else 
{
	cout << "Please type: 'A' or 'D' to move! And 'Y' to execute!" << endl;
}
	}

// End of the while loop. Precondition: A type of coordinate has been selected.

	clearSceen();
	printSelectionType(type, xDetails, yDetails);

// Beging while loop to extract values of the coordinates.
while (confirmed != "Y")
{
	if (xDetails == "real")
	{
	cout << xDetails + ": ";
	cin >> xDetails;

	cout << yDetails + " (Do not include the i) :";
	cin >> yDetails;
	}
	else {
	cout << xDetails + ": ";
	cin >> xDetails;

	cout << yDetails + ": ";
	cin >> yDetails;
	}
	
	stringstream keyX(xDetails);
	keyX >> xValue;

	stringstream keyY(yDetails);
	keyY >> yValue;

	cout << "Is this correct? (Y/N)     ";
	inputCoords(xDetails,yDetails);
	cin >> confirmed;
	if (confirmed != "Y"){
		if (type == "Rectangular")
	{
		xDetails = "x";
		yDetails = "y";
	}
	else if(type == "Polar")
	{
		xDetails = "r";
		yDetails = "θ";
	}
	else if(type == "Complex")
	{
		xDetails = "real";
		yDetails = "imaginary";
	}
	}
}
// End of the while loop. Precondition: A value has been typed in for each coordinate.

clearSceen();
cout << type + ": ";
inputCoords(xDetails,yDetails);
cout << "Converting..." << endl;
cout << endl;

if (type == "Rectangular")
	{
		double rValue = rectToR(xValue,yValue);
		double thetaValue = rectToTheta(xValue,yValue);
		cout << "Polar: (" << rValue << ", " << thetaValue << "º)  or  ";
		cout << "Polar: (" << rValue << ", " << thetaValue * PI / 180 << " rad)" << endl;

		double real = rValue * cos(thetaValue * PI / 180);
		double imaginary = rValue * sin(thetaValue * PI / 180);

		cout << "Complex: (" << real << ", " << imaginary << "i)";
	}
	else if(type == "Polar")    
	{
		cout << "Theta is 'Deg' or 'Rad' ?" << endl;
		cin >> polarSign;
		clearSceen();

		cout << endl;
		cout << "Polar: ";
		inputCoords(xDetails,yDetails);
		cout << "Converting..." << endl;
		cout << endl;

		if(polarSign == "Deg"){
			yValue = yValue * PI / 180;
		}

		double newX = xValue * cos(yValue); 
		double newY = xValue * sin(yValue);

		cout << "Rectangular: (" << ceil(newX) << ", " << ceil(newY) << ")" << endl;
		cout << "Complex: (" << ceil(newX) << ", " << ceil(newY) << "i)" << endl;
	}
	else if(type == "Complex")
	{



		cout << "Rectangular: (" << xValue << ", " << yValue << ")" << endl;
		double rValue = rectToR(xValue,yValue);
		double thetaValue = rectToTheta(xValue,yValue);
		cout << "Polar: (" << rValue << ", " << thetaValue << "º)  or  ";
		cout << "Polar: (" << rValue << ", " << thetaValue * PI / 180 << " rad)" << endl;

	}

cout << "\n" << endl;
cout << "Thank you!" << endl;

	// End of program.
	return 0;
}

double rectToTheta(double xValue, double yValue)
{
	double theta = atan(yValue / xValue) * 180 / PI ;
	if (xValue < 0 && yValue > 0)
	{	
		theta += 180;
	} 
	else if (xValue < 0 && yValue < 0)
	{	
		theta += 180;
	}
	else if (xValue > 0 && yValue < 0)
	{
		theta += 360;
	}
	
	return theta;
}

double rectToR(double xValue, double yValue)
{
	double num = sqrt(xValue * xValue + yValue * yValue);
	return num;
}


void inputCoords(string xDetails, string yDetails)
{
	cout << "(" + xDetails + ", " + yDetails + ")" << endl;
}

void printSelectionType(string type, string xDetails , string yDetails)
{
	cout << "You selected " + type + " coordinates to convert from." << endl;
	cout << endl;
	cout << "Please type the coordinates in the form of (" + xDetails + ", " + yDetails + ")" << endl;
	cout << endl;
}

int countLines(){
	ifstream file;

	file.open("complexMenu.txt");
	int num = 0;
	string line = "";

	if(file.is_open()){
		while (getline(file, line)){
			num++;
		}
	}

	else {

		cout << "Could not successfully open file! Closing applicaion!" << endl;
		exit(1);
	}
	return num;
}

void clearSceen()
{
	for (int i = 0; i < 25; i++){
		cout << endl;
	}
}

void printMenu(string words[], int i)
{
	cout << words[8] << endl;
	cout << endl; 
	cout << words[i] << endl;
	cout << words[i+1] << endl;
}

bool readfromFile(string words[]){
	ifstream file;

	file.open("complexMenu.txt");
	int num = 0;
	string line = "";

	if(file.is_open()){
		while (getline(file, line)){
			words[num] = line;
			num++;
		}
		file.close();
	}

	else {

		cout << "Could not successfully open file! Closing applicaion!" << endl;
		exit(1);
	}
	return num;
}



