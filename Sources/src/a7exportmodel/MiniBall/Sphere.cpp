#include "StdAfx.h"

#include "Sphere.h"

#include "Vector.h"
#include "Matrix.h"

#include "stdlib.h"

namespace MiniBall
{
	const float radiusEpsilon = 1e-4f;   // NOTE: To avoid numerical inaccuracies

	Sphere::Sphere()
	{
		radius = -1;
	}

	Sphere::Sphere(const Sphere &S)
	{
		radius = S.radius;
		center = S.center;
	}

	Sphere::Sphere(const Point &O)
	{
		radius = 0 + radiusEpsilon;
		center = O;
	}

	Sphere::Sphere(const Point &O, float R)
	{
		radius = R;
		center = O;
	}

	Sphere::Sphere(const Point &O, const Point &A)
	{
		Vector a = A - O;

		Vector o = 0.5f * a;

		radius = Vector::N(o) + radiusEpsilon;
		center = O + o;
	}

	Sphere::Sphere(const Point &O, const Point &A,  const Point &B)
	{
		Vector a = A - O;
		Vector b = B - O;

		float Denominator = 2.0f * ((a % b) * (a % b));

		Vector o = ((b^2) * ((a % b) % a) +
		            (a^2) * (b % (a % b))) / Denominator;

		radius = Vector::N(o) + radiusEpsilon;
		center = O + o;
	}

	Sphere::Sphere(const Point &O, const Point &A, const Point &B, const Point &C)
	{
		Vector a = A - O;
		Vector b = B - O;
		Vector c = C - O;

		float Denominator = 2.0f * Matrix::det(a.x, a.y, a.z,
		                                       b.x, b.y, b.z,
		                                       c.x, c.y, c.z);

		Vector o = ((c^2) * (a % b) +
		            (b^2) * (c % a) +
		            (a^2) * (b % c)) / Denominator;

		radius = Vector::N(o) + radiusEpsilon;
		center = O + o;
	}

	Sphere &Sphere::operator=(const Sphere &S)
	{
		radius = S.radius;
		center = S.center;

		return *this;
	}

	float Sphere::d(const Point &P) const
	{
		return Point::d(P, center) - radius;
	}

	float Sphere::d2(const Point &P) const
	{
		return Point::d2(P, center) - radius*radius;
	}

	float Sphere::d(const Sphere &S, const Point &P)
	{
		return Point::d(P, S.center) - S.radius;
	}

	float Sphere::d(const Point &P, const Sphere &S)
	{
		return Point::d(P, S.center) - S.radius;
	}

	float Sphere::d2(const Sphere &S, const Point &P)
	{
		return Point::d2(P, S.center) - S.radius*S.radius;
	}

	float Sphere::d2(const Point &P, const Sphere &S)
	{
		return Point::d2(P, S.center) - S.radius*S.radius;
	}

	Sphere Sphere::recurseMini(Point *P[], unsigned int p, unsigned int b)
	{
		Sphere MB;

		switch(b)
		{
		case 0:
			MB = Sphere();
			break;
		case 1:
			MB = Sphere(*P[-1]);
			break;
		case 2:
			MB = Sphere(*P[-1], *P[-2]);
			break;
		case 3:
			MB = Sphere(*P[-1], *P[-2], *P[-3]);
			break;
		case 4:
			MB = Sphere(*P[-1], *P[-2], *P[-3], *P[-4]);
			return MB;
		}

		for(unsigned int i = 0; i < p; i++)
			if(MB.d2(*P[i]) > 0)   // Signed square distance to sphere
			{
				for(unsigned int j = i; j > 0; j--)
				{
					Point *T = P[j];
					P[j] = P[j - 1];
					P[j - 1] = T;
				}

				MB = recurseMini(P + 1, i, b + 1);
			}

		return MB;
	}

	Sphere Sphere::miniBall(Point P[], unsigned int p)
	{
		Point **L = new Point*[p];

		for(unsigned int i = 0; i < p; i++)
			L[i] = &P[i];

		Sphere MB = recurseMini(L, p);

		delete[] L;

		return MB;
	}

	Sphere Sphere::smallBall(Point P[], unsigned int p)
	{
		Vector center;
		float radius = -1;

		if ( p > 0 )
		{
			center = 0;

			for ( unsigned int i = 0; i < p; i++ )
				center += P[i];

			center /= (float)p;

			for ( unsigned int i = 0; i < p; i++ )
			{
				float d2 = Point::d2( P[i], center );
			
				if(d2 > radius)
					radius = d2;
			}

			radius = sqrtf(radius) + radiusEpsilon;
		}

		return Sphere(center, radius);
	}
}