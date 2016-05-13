#pragma once
#include <iostream>
#include <math.h>
#include <ostream>
#include <conio.h>
using namespace std;

const double pi = 3.14159265359;

class CMy2DPoint {
public: double m_x; double m_y;
		CMy2DPoint() {};
		CMy2DPoint(double x, double y) : m_x(x), m_y(y) {};
		CMy2DPoint operator+(const CMy2DPoint &a) {
			return CMy2DPoint(m_x + a.m_x, m_y + a.m_y);
		}
		CMy2DPoint operator-(const CMy2DPoint &a) {
			return CMy2DPoint(m_x - a.m_x, m_y - a.m_y);
		}
		CMy2DPoint operator/(double m) {
			return CMy2DPoint(m_x / m, m_y / m);
		}
		bool operator==(const CMy2DPoint &a) {
			return ((a.m_x==m_x) && (m_y==a.m_y));
		}
		bool operator!=(const CMy2DPoint &a) {
			return !((a.m_x == m_x) && (m_y == a.m_y));
		}
		double operator*(const CMy2DPoint &a) {
			return (m_x*a.m_x+m_y*a.m_y);
		}
		CMy2DPoint operator*(double m) {
			return CMy2DPoint(m_x*m, m_y*m);
		}
		

};

class CMy2DObject {
private: CMy2DPoint m_center; double m_angle; double A; double A1; double A2; double A3;
		

public: CMy2DObject(CMy2DPoint c, double an, double AA, double AA1, double AA2, double AA3) :
	m_center(c), m_angle(an), A(AA), A1(AA1), A2(AA2), A3(AA3) {
	SetFig(c, an, AA, AA1, AA2, AA3);
};


CMy2DObject() {};
CMy2DPoint an_point[10];
double Radius; double kr_x; double kr_y;
 
public:
	void SetFig(CMy2DPoint m_c, double angle, double AA, double AA1, double AA2, double AA3) {
		if ((AA1 < AA) && (AA - AA1 / 2 > 0.2*AA3)) {
			m_center.m_x = m_c.m_x;
			m_center.m_y = m_c.m_y;
			m_angle = angle;
			A = AA;
			A1 = AA1;
			A2 = AA2;
			A3 = AA3;
			kr_x = m_center.m_x - (A / 2);
			kr_y = m_center.m_y - (A / 2);

			an_point[0].m_x = kr_x + A;
			an_point[0].m_y = kr_y;

			an_point[1].m_x = kr_x + A2;
			an_point[1].m_y = kr_y;

			an_point[2].m_x = kr_x;
			an_point[2].m_y = kr_y + A2;

			an_point[3].m_x = kr_x;
			an_point[3].m_y = kr_y + A - A3;

			an_point[4].m_x = kr_x + A3; // координаты центра скругления
			an_point[4].m_y = kr_y + A - A3;

			an_point[5].m_x = kr_x + A;
			an_point[5].m_y = kr_y + A;

			an_point[6].m_x = kr_x + A;
			an_point[6].m_y = kr_y + (A - A1) / 2 + A1;

			an_point[7].m_x = kr_x + A - A1;
			an_point[7].m_y = kr_y + (A - A1) / 2 + A1;

			an_point[8].m_x = kr_x + A - A1;
			an_point[8].m_y = kr_y + (A - A1) / 2;

			an_point[9].m_x = kr_x + A;
			an_point[9].m_y = kr_y + (A - A1) / 2;

			Radius = A3;

			for (int i(0); i < 10; i++) {
				an_point[i].m_x -= m_center.m_x;
				an_point[i].m_y -= m_center.m_y;
			};

			for (int i(0); i < 10; i++) {
				double temp;
				temp = an_point[i].m_x;
				an_point[i].m_x = temp*cos(m_angle*pi / 180) - an_point[i].m_y*sin(m_angle*pi / 180);
				an_point[i].m_y = temp*sin(m_angle*pi / 180) + an_point[i].m_y*cos(m_angle*pi / 180);
			};
			for (int i(0); i < 10; i++) {
				an_point[i].m_x += m_center.m_x;
				an_point[i].m_y += m_center.m_y;
			};
		};
	}
	
	
	const double GetA() {
		return A;
	};
	const double GetA1() {
		return A1;
	};
	const double GetA2() {
		return A2;
	};
	const double GetA3() {
		return A3;
	};
	const double GetAngle() {
		return m_angle;
	}; 
	const CMy2DPoint GetCenter() {
		return m_center;
	};

	void Move(double dx, double dy) {
		m_center.m_x += dx;
		m_center.m_y += dy;
		CMy2DPoint C(m_center.m_x, m_center.m_y);
		SetFig(C, m_angle, A, A1, A2, A3);
	};

	void Move(const CMy2DPoint &delta) {
		m_center.m_x += delta.m_x;
		m_center.m_y += delta.m_y;
	};

	void Rotate(double dAngle) {
		m_angle += dAngle;
		SetFig(m_center, m_angle, A, A1, A2, A3);
	};

	bool IsInside(const CMy2DPoint &point) {
		if (((point.m_x > kr_x) && (point.m_x<A + kr_x) && (point.m_y>kr_y) && (point.m_y < A + kr_y)) // внешний
		    && !((point.m_x>kr_x+A-A1) && (point.m_x<kr_x+A) && (point.m_y>kr_y+A/2-A1/2) && (point.m_y<kr_y+A/2+A1/2)) // маленький
			&& !((point.m_x>kr_x) && (point.m_y>kr_y) && (point.m_y<-point.m_x+kr_x+kr_y+A2))  //треугольник
			&& !((point.m_x>kr_x) && (point.m_y<kr_y+A) && (point.m_x<kr_x+A3) && (point.m_y>kr_y+A-A3) && // окружность 
				((point.m_x*point.m_x+point.m_y*point.m_y) < A3*A3))) 
			return true;
		else return false;
	};
	bool IsInside(double x, double y) {
		CMy2DPoint P;
		P.m_x = x;
		P.m_y = y; 
		return IsInside(P);
	};


	void Draw(CDC &dc) {
		dc.MoveTo(an_point[0].m_x, an_point[0].m_y);
		for (int i(0); i < 4; i++) {
			dc.LineTo(an_point[i].m_x, an_point[i].m_y);
		}
		dc.AngleArc(an_point[4].m_x, an_point[4].m_y, A3, 180-m_angle, 90);
		for (int i(5); i < 10; i++) {
			dc.LineTo(an_point[i].m_x, an_point[i].m_y);
		}
		dc.LineTo(an_point[0].m_x, an_point[0].m_y);
	};

};