#include "PA4.h"

//Constructor Destructorlar:(Sýrasý ile)
DispWindow::DispWindow(int n_main, int m_main)
{
	n = n_main;
	m = m_main;
	pArray = new char*[m];
	for (int i = 0; i < m; i++)
	{
		pArray[i] = new char[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			pArray[i][j] = ' ';
		}
	}
	//pArray = new char*[1];
}
Dot::Dot(Point p)
{
	current_p = p;
	setc(current_p);
	setne(current_p);
	setn(current_p);
	setnw(current_p);
	sets(current_p);
	setse(current_p);
	setsw(current_p);
}
Line::Line(Point p1, Point p2)
{
	current_p = p1;
	future_p = p2;
	if (current_p.getY() < future_p.getY())
	{
		if (future_p.getX() > current_p.getX()) {
			Point c_set((future_p.getX() - current_p.getX()) / 2 + current_p.getX(), (future_p.getY() - current_p.getY()) / 2 + current_p.getY());
			setc(c_set);
		}
		else if (future_p.getX() < current_p.getX()) {
			Point c_set((current_p.getX() - future_p.getX()) / 2 + future_p.getX(), (future_p.getY() - current_p.getY()) / 2 + current_p.getY());
			setc(c_set);
		}
		setne(current_p);
		setn(current_p);
		setnw(current_p);
		sets(future_p);
		setse(future_p);
		setsw(future_p);
	}
	else if (current_p.getY() > future_p.getY())
	{
		if (future_p.getX() > current_p.getX()) {
			Point c_set((future_p.getX() - current_p.getX()) / 2 + current_p.getX(), (current_p.getY() - future_p.getY()) / 2 + future_p.getY());
			setc(c_set);
		}
		else if (future_p.getX() < current_p.getX()) {
			Point c_set((current_p.getX() - future_p.getX()) / 2 + future_p.getX(), (current_p.getY() - future_p.getY()) / 2 + future_p.getY());
			setc(c_set);
		}
		setne(future_p);
		setn(future_p);
		setnw(future_p);
		sets(current_p);
		setse(current_p);
		setsw(current_p);
	}
}
Rectangle::Rectangle(Point p1, Point p2)
{
	current_p = p1;
	future_p = p2;
	Point ne_set(future_p.getX(), current_p.getY());
	Point n_set((future_p.getX() - current_p.getX()) / 2 + current_p.getX(), current_p.getY());
	Point w_set(current_p.getX(), (future_p.getY() - current_p.getY()) / 2 + current_p.getY());
	Point c_set((future_p.getX() - current_p.getX()) / 2 + current_p.getX(), (future_p.getY() - current_p.getY()) / 2 + current_p.getY());
	Point e_set(future_p.getX(), (future_p.getY() - current_p.getY()) / 2 + current_p.getY());
	Point sw_set(current_p.getX(), future_p.getY());
	Point s_set((future_p.getX() - current_p.getX()) / 2 + current_p.getX(), future_p.getY());
	setne(ne_set);
	setn(n_set);
	setnw(current_p);
	setw(w_set);
	setc(c_set);
	sete(e_set);
	setsw(sw_set);
	sets(s_set);
	setse(future_p);
}
DispWindow::~DispWindow()
{
	//Memory ' i serbest birakiyorum:
	for (int i = 0; i <m; i++)
	{
		delete[] pArray[i];

	}
	delete[] pArray;
}
//GET BUFFER FONKSIYONUM:
void DispWindow::getBuffer(int x, int y)
{
	pArray[y][x] = '*';
}
void DispWindow::getBuffer(Point p)
{
	pArray[p.y][p.x] = '*';
}
//KOORDINATLARI ESITLIYORUM:
void DispWindow::getFutureCoordinate(Point future_p)
{
	p = future_p;
}
//Pozisyon Fonksiyonlarý:
Point DispWindow::current()
{
	return p;
}
Point DispWindow::current(Point p_cur)
{
	this->p = p_cur;
	return p;
}
Point Point::right(int n)
{
	x += n;
	return *this;
}
Point Point::down(int n)
{
	y += n;
	return *this;
}
Point Point::up(int n)
{
	y -= n;
	return *this;
}
Point Point::left(int n)
{
	x -= n;
	return *this;
}
//Yer Kontrolu Fonksiyonu:
bool Dot::enoughSpaceDot(DispWindow& w)
{
	if (getCoordinateX() >= w.getn()|| getCoordinateY() >= w.getm())
		return false;
	else if (getCoordinateX() < w.getn() && getCoordinateY() < w.getm())
		return true;
}
bool Line::enoughSpaceLine(DispWindow& w)
{
	if (getXCurLine() < w.getn() && getYCurLine() < w.getm() && getXFutLine() < w.getn() && getYFutLine() < w.getm())
		return true;
	else
		return false;
}
bool Rectangle::enoughSpaceRec(DispWindow& w)
{
	if (getXCurLine() < w.getn() && getYCurLine() < w.getm())
		return true;
	else
		return false;
}
//Draw Fonksiyonlarý:
void DispWindow::draw(Line d)
{
	d.draw(*this);
}
void DispWindow::draw(Dot d)
{
	d.draw(*this);
}
void DispWindow::draw(Rectangle d)
{
	d.draw(*this);
}
void Dot::draw(DispWindow& w)
{
	if (enoughSpaceDot(w))
	{
		if (current_p.getX() < w.getn() && current_p.getY() < w.getm() && current_p.getX() >= 0 && current_p.getY() >= 0) {
			w.getBuffer(current_p.getX(), current_p.getY());
		}
		w.getFutureCoordinate(current_p);
	}
}
void Line::draw(DispWindow& w)
{
	int d_x, d_y, i;
	int error, inch1, inch2;
	int inchx, inchy;
	int x, y;

	d_x = future_p.getX() - current_p.getX();
	d_y = future_p.getY() - current_p.getY();

	if (d_x < 0) d_x *= -1;
	if (d_y < 0) d_y *= -1;

	inchx = 1;
	if (future_p.getX() < current_p.getX()) inchx = -1;

	inchy = 1;
	if (future_p.getY() < current_p.getY())
		inchy = -1;

	x = current_p.getX();
	y = current_p.getY();



	if (d_x > d_y)
	{
		if (x<w.getn() && y<w.getm() && x>=0 && y>=0)
			w.getBuffer(x, y);
		error = 2 * d_y - d_x;
		inch1 = 2 * (d_y - d_x);
		inch2 = 2 * d_y;
		for (i = 0; i < d_x; i++)
		{
			if (error >= 0)
			{
				y += inchy;
				error += inch1;
			}
			else
				error += inch2;
			x += inchx;
			if (x<w.getn() && y<w.getm() && x >= 0 && y >= 0)
				w.getBuffer(x, y);
		}
	}
	else
	{
		if (x<w.getn() && y<w.getm() && x >= 0 && y >= 0)
			w.getBuffer(x, y);
		error = (2 * d_x - d_y);
		inch1 = 2 * (d_x - d_y);
		inch2 = 2 * d_x;
		for (i = 0; i < d_y; i++)
		{
			if (error >= 0)
			{
				x += inchx;

				error += inch1;
				y += inchy;

			}
			else
			{
				if (current_p.getX()>future_p.getX())
				{
					if (x<w.getn() && y<w.getm() && x >= 0 && y >= 0)
						w.getBuffer(x + 1, y);
				}
				if (current_p.getX()<future_p.getX())
				{
					if (x<w.getn() && y<w.getm() && x >= 0 && y >= 0)
						w.getBuffer(x - 1, y);
				}
				error += inch2;
				y += inchy;

			}
			if (x<w.getn() && y<w.getm() && x >= 0 && y >= 0)
				w.getBuffer(x, y);
		}


	}
	w.getFutureCoordinate(future_p);
}
void Rectangle::draw(DispWindow& w)
{
	if (enoughSpaceRec(w)) {
		for (int i = current_p.getY(); i <= future_p.getY(); i++)
		{
			for (int j = current_p.getX(); j <= future_p.getX(); j++)
			{
				if (i == current_p.getY())
				{
					if (i < w.getm() && j < w.getn() && i >= 0 && j >= 0) {
						w.getBuffer(j, i);
					}
				}
				else if (i == (future_p.getY()))
				{

					if (i < w.getm() && j < w.getn() && i >= 0 && j >= 0) {
						w.getBuffer(j, i);
					}

				}
				else if (i != current_p.getY())
				{
					if (i < w.getm() && current_p.getX() < w.getn() && i >= 0 && j >= 0) {
						w.getBuffer(current_p.getX(), i);
					}
					if (i < w.getm() && future_p.getX() < w.getn() && i >= 0 && j >= 0) {
						w.getBuffer(future_p.getX(), i);
					}
				}
			}

		}
	}
	w.getFutureCoordinate(future_p);
}
//Show Fonksiyonu:
void DispWindow::show()
{
	if (pArray)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << pArray[i][j];
			}
			cout << endl;
		}
	}
}
//SHAPE NOKTA FONKSIYONLARI (RECTANGLE ICIN):
Point Rectangle::ne()
{
	return getne();
}
Point Rectangle::n()
{
	return getn();
}
Point Rectangle::nw()
{
	return getnw();
}
Point Rectangle::w()
{
	return getw();
}
Point Rectangle::c()
{
	return getc();
}
Point Rectangle::e()
{
	return gete();
}
Point Rectangle::sw()
{
	return getsw();
}
Point Rectangle::s()
{
	return gets();
}
Point Rectangle::se()
{
	return getse();
}
//SHAPE NOKTA FONKSIYONLARI (LINE ICIN):
Point Line::ne()
{
	return getne();
}
Point Line::n()
{
	return getn();
}
Point Line::nw()
{
	return getnw();
}
Point Line::w()
{
	return getw();
}
Point Line::c()
{
	return getc();
}
Point Line::e()
{
	return gete();
}
Point Line::sw()
{
	return getsw();
}
Point Line::s()
{
	return gets();
}
Point Line::se()
{
	return getse();
}

