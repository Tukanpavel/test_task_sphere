#include <string>
#include "mwTPoint3d.hpp"
#include <ctime>
#include <iostream>

#include "CalcSphereMovement.hpp"

//#############################################################################

int main(int argc, char* argv[])
{

	//Point cloud reference point at 0, 0, 0
	cadcam::mwTPoint3d<double> referencePoint( 0., 0., 0. );

	//Number of points in x direction
	const unsigned long nx = 1000;

	//Number of points in y direction
	const unsigned long ny = 500;

	//Number of points in z direction
	const unsigned long nz = 100;

	//Distance between points in the point grid (same fo x, y and z directions)
	const double delta = 1.;

	//Radius of the sphere
	const double sphereRad = 5.;

	//Name of the file to write the data to
	const std::string outputFileName( "test.asc" );

	// sphere movement start and end positions
	cadcam::mwTPoint3d<double> sphereStartPos(200, 200,	50);
	cadcam::mwTPoint3d<double> sphereEndPos(700, 400, 150);

	unsigned int startTime = std::clock();

	//Evaluation here
	CalcSphereMovement( referencePoint, nx, ny, nz, delta, sphereRad,
	             sphereStartPos, sphereEndPos, outputFileName );
	unsigned int finishTime = std::clock();

	std::cout << finishTime - startTime;

	return 0;
}

