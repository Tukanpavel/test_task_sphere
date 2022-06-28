#include "CalcSphereMovement.hpp"
#include "SphereBorder.hpp"
#include <fstream>
#include <iostream>

void CalcSphereMovement( const cadcam::mwTPoint3d<double>& refPoint,
									const unsigned long nx, const unsigned long ny,
									const unsigned long nz, const double delta,
									const double sphereRad,
									const cadcam::mwTPoint3d<double>& sphereStartPos,
									const cadcam::mwTPoint3d<double>& sphereEndPos,
									const std::string &outputFileName )
{
	CleanPreviousRun(outputFileName);

	cadcam::mwTPoint3d<double> tempPos = cadcam::mwTPoint3d<double>();

	SphereBorder<double>* border = SphereBorder<double>::Builder()
		.WithRefPoint(refPoint)
		->WithStartPoint(sphereStartPos)
		->WithEndPoint(sphereEndPos)
		->WithSphereRad(sphereRad)
		->WithXNumber(nx)
		->WithYNumber(ny)
		->WithZNumber(nz)
		->WithDelta(delta)
		->Build();

	for ( double x = refPoint.x();  x <= border->xMax();  x += delta)
	{
		if ( x < border->xMin() )
		{
			continue;
		}

		tempPos.x(x);

		for ( double y = refPoint.y(); y <= border->yMax(); y += delta)
		{
			
			if ( y < border->yMin() )
			{
				continue;
			}
			
			tempPos.y(y);

			for ( double z = refPoint.z(); z <= border->zMax(); z += delta)
			{
				if ( z < border->zMin() )
				{
					continue;
				}

				tempPos.z(z);

				// case where scalar product to start point is negative

				if ( ScalarProductIsNegative( sphereStartPos, sphereEndPos, tempPos ) ) 
				{
					double result = PointToPointDestination( sphereStartPos, tempPos );
					
					if ( result <= sphereRad )
					{
						PrintPoint( tempPos, outputFileName );

					}

					continue;
				}

				// case where scalar product to an end point is negative

				if ( ScalarProductIsNegative( sphereEndPos, sphereStartPos, tempPos ) )
				{
					double result = PointToPointDestination( sphereEndPos, tempPos );

					if ( result <= sphereRad )
					{
						PrintPoint( tempPos, outputFileName );

					}

					continue;
				}

				// case where both of products are positive

				double result = PointToLineDestination( sphereStartPos, sphereEndPos, tempPos );
				
				if ( result <= sphereRad )
				{
					PrintPoint( tempPos, outputFileName );
				}

			}
		}
	}

}

bool ScalarProductIsNegative( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& endVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = endVectorPoint - startVectorPoint;
	cadcam::mwTPoint3d<double> b = point - startVectorPoint;
	return (a * b < 0);
}

double PointToPointDestination( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = startVectorPoint - point;
	return ~a;
}

double PointToLineDestination( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& endVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = endVectorPoint - startVectorPoint;
	cadcam::mwTPoint3d<double> b = point - startVectorPoint;
	return  ~( a % b ) / ~ a;
}

void PrintPoint( const cadcam::mwTPoint3d<double>& point, const std::string& outputFileName)
{
	std::ofstream out;
	out.open(outputFileName, std::ios::app);
	out << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
	out.close();
}

void CleanPreviousRun(const std::string& outoutFileName) {
	std::ofstream out;
	out.open(outoutFileName, std::ios::trunc);
	out.close();
}