#ifndef CALCSPHEREMOVEMENT_HPP
#define CALCSPHEREMOVEMENT_HPP

#include "mwTPoint3d.hpp"

void CalcSphereMovement(const cadcam::mwTPoint3d<double>& refPoint,
                  const unsigned long nx, const unsigned long ny,
                  const unsigned long nz, const double delta,
                  const double sphereRad,
                  const cadcam::mwTPoint3d<double>& sphereStartPos,
                  const cadcam::mwTPoint3d<double>& sphereEndPos,
                  const std::string &outputFileName );
void PrintPoint(const cadcam::mwTPoint3d<double>& point, const std::string& outputName);

double PointToLineDestination(const cadcam::mwTPoint3d<double>& startVectorPoint,
    const cadcam::mwTPoint3d<double>& endVectorPoint,
    const cadcam::mwTPoint3d<double>& point);
double PointToPointDestination(const cadcam::mwTPoint3d<double>& startVectorPoint,
    const cadcam::mwTPoint3d<double>& point);
bool ScalarProductIsNegative(const cadcam::mwTPoint3d<double>& startVectorPoint,
    const cadcam::mwTPoint3d<double>& endVectorPoint,
    const cadcam::mwTPoint3d<double>& point);
void CleanPreviousRun(const std::string& outputFileName);
#endif /* CALCSPHEREMOVEMENT_HPP */
