#ifndef SPHEREBORDER_HPP
#define SPHEREBORDER_HPP


#include"mwTPoint3d.hpp"

template < typename T>
class SphereBorder
{
private:
	SphereBorder<T>()
	{
		this->minPoint = cadcam::mwTPoint3d<T>();
		this->maxPoint = cadcam::mwTPoint3d<T>();
	};
	cadcam::mwTPoint3d<T> minPoint;
	cadcam::mwTPoint3d<T> maxPoint;
	void MinPoint(const cadcam::mwTPoint3d<T>& newPoint)
	{
		this->minPoint = newPoint;
	};
	void MaxPoint(const cadcam::mwTPoint3d<T>& newPoint)
	{
		this->maxPoint = newPoint;
	}
public:
	inline T xMin()
	{
		return minPoint.x();
	};
	inline T xMax()
	{
		return maxPoint.x();
	};
	inline T yMin()
	{
		return minPoint.y();
	};
	inline T yMax()
	{
		return maxPoint.y();
	};
	inline T zMin()
	{
		return minPoint.z();
	};
	inline T zMax()
	{
		return maxPoint.z();
	}
	class Builder
	{
	private:
		T x;
		T y;
		T z;
		T delta;
		T sphereRad = 0;
		cadcam::mwTPoint3d <T> refPoint;
		cadcam::mwTPoint3d <T> startPoint;
		cadcam::mwTPoint3d <T> endPoint;
	public:
		Builder* WithRefPoint(const cadcam::mwTPoint3d<T>& refPoint)
		{
			this->refPoint = refPoint;
			return this;
		};
		Builder* WithStartPoint(const cadcam::mwTPoint3d<T>& startPoint)
		{
			this->startPoint = startPoint;
			return this;
		};
		Builder* WithEndPoint(const cadcam::mwTPoint3d<T>& endPoint)
		{
			this->endPoint = endPoint;
			return this;
		};
		Builder* WithXNumber(const T& x) {
			this->x = x;
			return this;
		}
		Builder* WithYNumber(const T& y) {
			this->y = y;
			return this;
		}
		Builder* WithZNumber(const T& z) {
			this->z = z;
			return this;
		}
		Builder* WithDelta(const T& delta) {
			this->delta = delta;
			return this;
		}
		Builder* WithSphereRad(const T& sphereRad)
		{
			this->sphereRad = sphereRad;
			return this;
		};
		SphereBorder* Build()
		{
			SphereBorder* newBorder = new SphereBorder();

			double xLowBorder = fmin(this->startPoint.x(), this->endPoint.x()) - this->sphereRad;
			double xHighBorder = fmax(this->startPoint.x(), this->endPoint.x()) + this->sphereRad;

			double yLowBorder = fmin(this->startPoint.y(), this->endPoint.y()) - this->sphereRad;
			double yHighBorder = fmax(this->startPoint.y(), this->endPoint.y()) + this->sphereRad;
			
			double zLowBorder = fmin(this->startPoint.z(), this->endPoint.z()) - this->sphereRad;
			double zHighBorder = fmax(this->startPoint.z(), this->endPoint.z()) + this->sphereRad;

			xHighBorder = fmin(xHighBorder, (this->x - 1) * this->delta);
			yHighBorder = fmin(yHighBorder, (this->y - 1) * this->delta);
			zHighBorder = fmin(zHighBorder, (this->z - 1) * this->delta);

			newBorder->MinPoint(cadcam::mwTPoint3d<T>(xLowBorder, yLowBorder, zLowBorder));
			newBorder->MaxPoint(cadcam::mwTPoint3d<T>(xHighBorder, yHighBorder, zHighBorder));

			return newBorder;
		};
	};
};

#endif // SPHEREBORDER_HPP

