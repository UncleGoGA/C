#include <iostream>
#include <cmath>

using namespace std;

class Point
{
	float x, y;

public:
	Point(float x1 = 0, float y1 = 0)
	{
		x = x1;
		y = y1;
	}

	Point(const Point &A)
	{
		x = A.x;
		y = A.y;
	}

	Point operator+=(const Point &A)
	{
		x += A.x;
		y += A.y;
		return *this;
	}

	void see_point()
	{
		cout << "(" << x << "," << y << ")" << endl;
	}

	bool IsRight(Point A, Point B, Point C)
	{
		float D = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
		return D < 0 ? true : false;
	}

	friend class Triangle;
	friend bool IsRight(Point A, Point B, Point C);
};

class Triangle
{
	Point a, b, c;
	float ab, bc, ac;
	float S;
	int number;

public:
	static int count;

	Point get_point(char flag)
	{
		if (flag == 'a')
		{
			return a;
		}
		else if (flag == 'b')
		{
			return b;
		}
		else
		{
			return c;
		}
	}

	Triangle(Point A, Point B, Point C) : a(A), b(B), c(C)
	{
		number = ++count;
		ab = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
		bc = sqrt((b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y));
		ac = sqrt((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y));
		S = abs(a.x * b.y + b.x * c.y + a.y * c.x - c.x * b.y - a.x * c.y - b.x * a.y) / 2;
	}

	~Triangle()
	{
		--count;
	}

	void shift(const Point &Delta)
	{
		a += Delta;
		b += Delta;
		c += Delta;
	}

	bool operator>(const Triangle &T)
	{
		return S > T.S ? true : false;
	}

	void see_triangle()
	{
		cout << "Triangle number: " << number << endl;
		cout << "Pounts: " << endl;
		cout << "A";
		a.see_point();
		cout << "B";
		b.see_point();
		cout << "C";
		c.see_point();
		cout << "Sides: " << endl;
		cout << "AB = " << ab << endl;
		cout << "BC = " << bc << endl;
		cout << "AC = " << ac << endl;
		cout << "Square: " << S << endl;
		cout << endl;
	}

	int get_number()
	{
		return number;
	}

	//Определяет вхождение вершин треугольника T через выичсление площадей
	bool includes(const Triangle &T)
	{
		float S1, S2, S3;
		S1 = Triangle(a, b, T.a).S + Triangle(b, c, T.a).S + Triangle(c, a, T.a).S;
		if (S1 != S)
			return false;
		else
		{
			S2 = Triangle(a, b, T.b).S + Triangle(b, c, T.b).S + Triangle(c, a, T.b).S;
			if (S2 != S)
				return false;
			else
			{
				S3 = Triangle(a, b, T.c).S + Triangle(b, c, T.c).S + Triangle(c, a, T.c).S;
				if (S3 != S)
					return false;
				else
					return true;
			}
		}
	}

	//Определяет вхождение вершин треугольника T через определение стороны, с которой стоит эта вершина относительно векторов треугольника this
	bool includes2(const Triangle &T)
	{
		if (IsRight(a, b, T.a) && IsRight(b, c, T.a) && IsRight(c, a, T.a))
		{
			if (IsRight(a, b, T.b) && IsRight(b, c, T.b) && IsRight(c, a, T.b))
			{
				if (IsRight(a, b, T.c) && IsRight(b, c, T.c) && IsRight(c, a, T.c))
				{
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool includes3(const Point &A)
	{
		if (IsRight(a, b, A) && IsRight(b, c, A) && IsRight(c, a, A))
		{
			//std::cout << "Yes, include" << std::endl;
			return true;
		}
		//std::cout << "No" << std::endl;
		return false;
	}
};

int Triangle::count = 0;

bool IsRight(Point A, Point B, Point C)
{
	float D = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
	return D <= 0 ? true : false;
}

int main()
{

	Triangle Tr1(Point(0, 0), Point(0, 100), Point(20, 0));
	Tr1.see_triangle();
	Triangle Tr2(Point(20, 0), Point(30, 50), Point(40, 25));
	Tr2.see_triangle();
	Triangle Tr3(Point(0, 0), Point(0, 20), Point(20, 0));
	Tr3.see_triangle();

	if (Tr2.includes(Tr1))
		cout << "Triangle number " << Tr2.get_number() << " includes Triangle number " << Tr1.get_number() << endl;

	if (Tr2.includes2(Tr1))
		cout << "Triangle number " << Tr2.get_number() << " includes Triangle number " << Tr1.get_number() << endl;

	if (Tr1.includes(Tr3))
		cout << "Triangle number " << Tr1.get_number() << " includes Triangle number " << Tr3.get_number() << endl;

	if (Tr1.includes2(Tr3))
		cout << "Triangle number " << Tr1.get_number() << " includes Triangle number " << Tr3.get_number() << endl;

	if (Tr1.includes3(Tr3.get_point('a')))
		cout << "Triangle number " << Tr3.get_number() << " point a "  << " include Triangle number " << Tr1.get_number() << endl;

	return 0;
}