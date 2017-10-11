// TowerTest.cpp 
//

#include "stdafx.h"
#include <math.h>
#include <iostream>

using namespace std;

// For the CN Tower, we use 6377571.76 as the earth radius.
// The CN Tower sky pod is 447

// The Willis (Sears) Tower in Chicago seems to be standing right at sea level
// and the earth radius there is 6369000 meters
// The sky deck observation area is 477 meters.

const int secondsInDay = 86400;

double dEarthRadius = 6369000; // or 6377571.76;
double dTestAngle = 20;

double ourheight = 477; // or 447;
bool bTowerGreater = true;

double pi = 3.141592653589793;

// y = 6270.14	equation for the solar plane
// 20x = y		equation for the starting guess for the line for the tower
// So using algabraic substition
// x =  6270.14 / 20
double TowerLineEquationY(double y)
{
	double dX = y / dTestAngle;
	return dX;
}

double TowerLineEquationX(double X)
{
	double dy = X * dTestAngle;
	return dy;
}


double CircleIntersection(double x)
{
	double dReturn = (dEarthRadius * dEarthRadius) - (x * x);
	dReturn = sqrt(dReturn);
	return dReturn;

}

double calculatetowerheight(double x1, double y1, double x2, double y2)
{
	double aSquared = (x1 - x2);
	aSquared = aSquared * aSquared;

	double bSquared = (y1 - y2);
	bSquared = bSquared * bSquared;

	double dHypotenuse = sqrt(aSquared + bSquared);
	
	return dHypotenuse;
}

bool CloseEnough(double y1, double y2)
{
	double Test = (y1 + y2);
	Test = Test / 2;

	if (Test == y1)
		return true;
	
	if (Test == y2)
		return true;

	if (y1 < Test)
		Test = Test - y1;
	else if (y2 < Test)
		Test = Test - y2;

	Test = Test * 1000000;

	if (Test < 1)
	{
		return true;
	}
	else
		return false;

}

int main()
{
	

	// input values:
/*	double dEarthRadius = 6377571.76;
	double dTestAngle = 20;
	double ourheight = 447;
*/
	/*
	cout << "Using the Geodetic Data chart for the radius at the latitude ";
	cout << "where the tower stands plus the number of meters above seal level,";
	cout << "enter the radius in meters:";
	
	cin >> dEarthRadius;

	cout << "Enter the number in meters for the height of the observation deck:";

	cin >> ourheight;

	// for now, we will ommit the users ability to enter the test angle initial value, to make things simple.
	*/
	double dTowerHeight = 0.0;

	double dLinearAngleDifferential = 1.0;

	if (dTowerHeight != ourheight)
		do
		{

			double y = dEarthRadius;
			double x = TowerLineEquationY(dEarthRadius);

			double y1 = y;
			double y2 = CircleIntersection(x);

			double dInterval = 10.0;

			if (CloseEnough(y1, y2) == false)
				do
				{
					if (y1 > y2)
						do
						{
							x = x - dInterval;
							y1 = TowerLineEquationX(x);
							y2 = CircleIntersection(x);

							if (y1 < y2)
							{
								if (dInterval > 0.000000001)
									dInterval = (dInterval * 99) / 100;
							}
						} while ((y1 > y2) && (CloseEnough(y1, y2) == false));

						if (y1 < y2)
							do
							{
								x = x + dInterval;
								y1 = TowerLineEquationX(x);
								y2 = CircleIntersection(x);

								if (y1 > y2)
								{
									if (dInterval > 0.000000001)
										dInterval = (dInterval * 99) / 100;
								}
//								iTrimmer = (int)(y1 * 1000);
//								y1 = (double)(y1 / 1000);

							} while ((y1 < y2) && (CloseEnough(y1, y2) == false));
				} while (CloseEnough (y1, y2) == false);

				//now we find the length of our tower

				dTowerHeight = calculatetowerheight(TowerLineEquationY(dEarthRadius), dEarthRadius, TowerLineEquationY(y2), y2);


				if (dTowerHeight > ourheight)
				{
					// we need a steeper angle
					dTestAngle = dTestAngle + dLinearAngleDifferential;

					if (bTowerGreater == false)
					{
						// we have flipped to the other side of measurement
						dLinearAngleDifferential = (dLinearAngleDifferential * 999) / 1000;
						bTowerGreater = true;
					}
				}
				if (dTowerHeight < ourheight)
				{
					dTestAngle = dTestAngle - dLinearAngleDifferential;
					if (bTowerGreater == true)
					{
						// we have flipped to the other side of measurement
						dLinearAngleDifferential = (dLinearAngleDifferential * 999) / 1000;
						bTowerGreater = false;
					}
				}
					
		} while (CloseEnough(dTowerHeight, ourheight) == false);

		// this gives a results in radians
		dTestAngle = atan(dTestAngle);  // 84.430937780135920 for the CN Tower
		// 1.5589528808956008 radians
		// this converts it to degrees
		dTestAngle = dTestAngle * 180 / pi;
		// 89.321420535078829 degrees
		// this gives us the number we really need:

		dTestAngle = 90 - dTestAngle;  //84.430937780135920;
		// 0.67857946492117094 is the actual angle to use
        // and now for the final calculations

		dTestAngle = (dTestAngle * secondsInDay) / 360;

		// at this point, or variable "dTestAngle" equals the number of seconds

		if (dTestAngle > 60)
		{
			// if it is more than one minute
			int minutes = dTestAngle / 60;
			int seconds = (dTestAngle - minutes * 60);

			cout << "The time difference is " << minutes << " minutes and " << seconds << " seconds";

		}
		else
		{

			cout << "The time difference is " << dTestAngle << " seconds";

		}


    return 0;
}

