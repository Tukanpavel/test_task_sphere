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
#endif /* CALCSPHEREMOVEMENT_HPP */
