#include "CalcSphereMovement.hpp"
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

	cadcam::mwTPoint3d<double> tempPos = cadcam::mwTPoint3d<double>( refPoint );

	double x = tempPos.x();
	double y = tempPos.y();
	double z = tempPos.z();

	cadcam::mwTPoint3d<double> startBorder = sphereStartPos;
	cadcam::mwTPoint3d<double> endBorder = sphereEndPos;

	double xLowBorder = fmin( startBorder.x(), endBorder.x() ) - sphereRad;
	double xHighBorder = fmax( startBorder.x(), endBorder.x() ) + sphereRad;

	double yLowBorder = fmin( startBorder.y(), endBorder.y() ) - sphereRad;
	double yHighBorder = fmax( startBorder.y(), endBorder.y() ) + sphereRad;
	
	double zLowBorder = fmin( startBorder.z(), endBorder.z() ) - sphereRad;
	double zHighBorder = fmax( startBorder.z(), endBorder.z() ) + sphereRad;

	for ( size_t i = 0; i < nx  && x <= xHighBorder; i++, tempPos.x(x + delta))
	{
		x = tempPos.x();
		if ( x < xLowBorder )
		{
			continue;
		}

		y = refPoint.y();
		tempPos.y( y );

		for ( size_t j = 0; j < ny  && y <= yHighBorder; j++, tempPos.y(y + delta))
		{
			y = tempPos.y();
			
			if ( y < yLowBorder )
			{
				continue;
			}
			z = refPoint.z();
			tempPos.z( z );

			for ( size_t k = 0; k < nz  && z <= zHighBorder; k++, tempPos.z(z + delta))
			{
				z = tempPos.z();
				
				if ( z < zLowBorder )
				{
					continue;
				}

				if ( ScalarProductIsNegative( sphereStartPos, sphereEndPos, tempPos ) ) 
				{
					double result = PointToPointDestination( sphereStartPos, tempPos );
					
					if ( result <= sphereRad )
					{
						PrintPoint( tempPos, outputFileName );

					}

					continue;
				}
				if ( ScalarProductIsNegative( sphereEndPos, sphereStartPos, tempPos ) )
				{
					double result = PointToPointDestination( sphereEndPos, tempPos );

					if ( result <= sphereRad )
					{
						PrintPoint( tempPos, outputFileName );

					}

					continue;
				}

				double result = PointToLineDestination( sphereStartPos, sphereEndPos, tempPos );
				
				if ( result <= sphereRad )
				{
					PrintPoint( tempPos, outputFileName );
				}

			}
		}
	}

}

void Normalise( cadcam::mwTPoint3d<double>& vector )
{
	double length = sqrt( vector.x() * vector.x() + 
						vector.y() * vector.y() +
						vector.z() * vector.z() );
	vector.x(vector.x() / length);
	vector.y(vector.y() / length);
	vector.z(vector.z() / length);
}

bool ScalarProductIsNegative( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& endVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = endVectorPoint - startVectorPoint;
	cadcam::mwTPoint3d<double> b = point - startVectorPoint;
	return (( a.x() * b.x() + a.y() * b.y() + a.z() + b.z() ) < 0);
}

double PointToPointDestination( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = startVectorPoint - point;
	return sqrt( a.x() * a.x() + a.y() * a.y() + a.z() * a.z() );
}

double PointToLineDestination( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& endVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = endVectorPoint - startVectorPoint;
	cadcam::mwTPoint3d<double> b = point - startVectorPoint;
	return sqrt( (a.y() * b.z() - a.z() * b.y()) * (a.y() * b.z() - a.z() * b.y()) +
				(a.z() * b.x() - a.x() * b.z()) * (a.z() * b.x() - a.x() * b.z()) +
				(a.x() * b.y() - a.y() * b.x()) * (a.x() * b.y() - a.y() * b.x()) ) /
				sqrt( a.x() * a.x() + a.y() * a.y() + a.z() * a.z() );
}

void PrintPoint( const cadcam::mwTPoint3d<double>& point, const std::string& outputFileName)
{
	std::ofstream out;
	out.open(outputFileName, std::ios::app);
	if (out.is_open())
	{
		out << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
	}
	out.close();
}

void CleanPreviousRun(const std::string& outoutFileName) {
	std::ofstream out;
	out.open(outoutFileName, std::ios::trunc);
	out.close();
}