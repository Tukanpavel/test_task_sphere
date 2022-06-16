#include "CalcSphereMovement.hpp"
#include <fstream>

void CalcSphereMovement( const cadcam::mwTPoint3d<double>& refPoint,
									const unsigned long nx, const unsigned long ny,
									const unsigned long nz, const double delta,
									const double sphereRad,
									const cadcam::mwTPoint3d<double>& sphereStartPos,
									const cadcam::mwTPoint3d<double>& sphereEndPos,
									const std::string &outputFileName )
{
	cadcam::mwTPoint3d<double> tempPos = cadcam::mwTPoint3d<double>( refPoint );
	
	double x = tempPos.x();
	double y = tempPos.y();
	double z = tempPos.z();

	cadcam::mwTPoint3d<double> pathVector = sphereEndPos - sphereStartPos;

	//Path vector would be normalised
	Normalise( pathVector );

	cadcam::mwTPoint3d<double> startBorder = sphereStartPos - pathVector * sphereRad * sqrt(2);
	cadcam::mwTPoint3d<double> endBorder = sphereEndPos + pathVector * sphereRad * sqrt(2);

	double xLowBorder = fmin( startBorder.x(), endBorder.x() );
	double xHighBorder = fmax( startBorder.x(), endBorder.x() );

	double yLowBorder = fmin( startBorder.y(), endBorder.y() );
	double yHighBorder = fmax( startBorder.y(), endBorder.y() );

	double zLowBorder = fmin( startBorder.z(), endBorder.z() );
	double zHighBorder = fmax( startBorder.z(), endBorder.z() );
	

	for ( size_t i = 0; i < nx && x < xHighBorder; i++, tempPos.x( x + delta ) )
	{
		x = tempPos.x();

		if ( x < xLowBorder )
		{
			continue;
		}

		tempPos.y( refPoint.y() );

		for ( size_t j = 0; j < ny && y < yHighBorder; j++, tempPos.y( y + delta ) )
		{
			y = tempPos.y();

			if ( y < yLowBorder )
			{
				continue;
			}

			tempPos.z( refPoint.z() );

			for ( size_t k = 0; k < nz && z < zHighBorder; k++, tempPos.z( z + delta ) )
			{
				z = tempPos.z();

				if ( z < zLowBorder )
				{
					continue;
				}

				if ( ScalarProductIsNegative( sphereStartPos, sphereEndPos, tempPos ) ) 
				{
					long result = PointToPointDestination( sphereStartPos, tempPos );
					
					if ( result <= sphereRad )
					{
						PrintPoint( tempPos, outputFileName );

					}

					continue;
				}
				if ( ScalarProductIsNegative( sphereEndPos, sphereStartPos, tempPos ) )
				{
					long result = PointToPointDestination( sphereEndPos, tempPos );

					if ( result <= sphereRad )
					{
						PrintPoint( tempPos, outputFileName );

					}

					continue;
				}

				long result = PointToLineDestination( sphereStartPos, sphereEndPos, tempPos );
				
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
	long length = sqrt( vector.x() * vector.x() + 
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
	return ( a.x() * b.x() + a.y() * b.y() + a.z() + b.z() ) < 0;
}

long PointToPointDestination( const cadcam::mwTPoint3d<double>& startVectorPoint,
								const cadcam::mwTPoint3d<double>& point )
{
	cadcam::mwTPoint3d<double> a = startVectorPoint - point;
	return sqrt( a.x() * a.x() + a.y() * a.y() + a.z() * a.z() );
}

long PointToLineDestination( const cadcam::mwTPoint3d<double>& startVectorPoint,
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

void PrintPoint( const cadcam::mwTPoint3d<double>& point, const std::string& outputName)
{
	std::ofstream out;
	out.open(outputName);
	out << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
	out.close();
}
