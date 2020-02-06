#include <iostream>
using namespace std;

class Point;
class DispWindow;
class Shape;
class Dot;
class Line;
class Rectangle;

class Point
{
	
public:
	int x, y;
	Point(int x_main = 0, int y_main = 0)
	{
		x = x_main;
		y = y_main;
	}
	Point& operator=(Point& p)
	{
		x = p.x;
		y = p.y;
		return *this;
	};
	Point& operator+(Point p)
	{
		x += p.x;
		y += p.y;
		return *this;
	};
	
	Point right(int n = 1);
	Point down(int n = 1);
	Point up(int n = 1);
	Point left(int n = 1);
	int getX() { return x; };
	int getY() { return y; };
	void setX(int x_set) { x -= x_set; };
	void setY(int y_set) { y -= y_set; };
};

class DispWindow
{
	int n, m;
	char **pArray;
	Point p;
public:

	DispWindow(int n_main, int m_main);
	~DispWindow();
	Point current();
	Point current(Point p_cur);
	int getm() { return m; };
	int getn() { return n; };
	void getBuffer(int, int);
	void getBuffer(Point p);
	void getFutureCoordinate(Point future_p);
	void show();
	//void draw(Shape& d);
	void draw(Line d);
	void draw(Dot d);
	void draw(Rectangle d);
	
};

class Shape
{
private:
	Point _nw;
	Point _n;
	Point _ne;
	Point _w;
	Point _c;
	Point _e;
	Point _sw;
	Point _s;
	Point _se;
public:
	virtual void draw(DispWindow& w) = 0;
	Point getnw() { return _nw; };
	Point getn() { return _n; };
	Point getne() { return _ne; };
	Point getw() { return _w; };
	Point getc() { return _c; };
	Point gete() { return _e; };
	Point getsw() { return _sw; };
	Point gets() { return _s; };
	Point getse() { return _se; };
	void setnw(Point p) { _nw = p; };
	void setn(Point p) { _n = p; };
	void setne(Point p) { _ne = p; };
	void setw(Point p) { _w = p; };
	void setc(Point p) { _c = p; };
	void sete(Point p) { _e = p; };
	void setsw(Point p) { _sw = p; };
	void sets(Point p) { _s = p; };
	void setse(Point p) { _se = p; };

};

class Dot :virtual public Shape
{
	Point current_p;
public:
	Dot(Point p);
	void draw(DispWindow& w);
	int getCoordinateX() { return current_p.getX(); };
	int getCoordinateY() { return current_p.getY(); };
	bool enoughSpaceDot(DispWindow& d);
};

class Line :virtual public Shape
{
	Point current_p;
	Point future_p;
public:
	Line(Point p1, Point p2);
	void draw(DispWindow& w);
	int getXCurLine() { return current_p.getX(); };
	int getYCurLine() { return current_p.getY(); };
	int getXFutLine() { return future_p.getX(); };
	int getYFutLine() { return future_p.getY(); };
	bool enoughSpaceLine(DispWindow& d);
	Point ne();
	Point n();
	Point nw();
	Point w();
	Point c();
	Point e();
	Point sw();
	Point s();
	Point se();
};

class Rectangle :virtual public Shape
{
	Point current_p;
	Point future_p;
public:
	Rectangle(Point p1, Point p2);
	void draw(DispWindow& w);
	int getXCurLine() { return current_p.getX(); };
	int getYCurLine() { return current_p.getY(); };
	int getXFutLine() { return future_p.getX(); };
	int getYFutLine() { return future_p.getY(); };
	bool enoughSpaceRec(DispWindow& d);
	Point ne();
	Point n();
	Point nw();
	Point w();
	Point c();
	Point e();
	Point sw();
	Point s();
	Point se();
};
