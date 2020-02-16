#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <list>

struct Vertice {
	int x, y;
	Vertice(int x, int y){ setVertice(x, y); }
	Vertice(){}
	void setVertice(int x, int y){
		this->x = x;
		this->y = y;
	}
};

Vertice inputVertice(){
	int x, y;
	std::cout << "X: ";
	std::cin >> x;
	std::cout << "Y: ";
	std::cin >> y;
	return Vertice(x, y);
}

std::list<Vertice> inputPolygon(){
	std::cout << "Enter number of vertices in polygon: ";
	int vCount;
	std::cin >> vCount;
	std::list<Vertice> polyVertices;
	for (int i = 0; i < vCount; i++){
		std::cout << "Enter vertice " << i + 1 << std::endl;
		polyVertices.push_back(inputVertice());
	}
	return polyVertices;
}

void drawPolygon(std::list<Vertice> &polygon){
	std::list<Vertice>::iterator it = polygon.begin();
	std::list<Vertice>::iterator rit = polygon.end(); rit--;
	for (; it != rit ;){
		Vertice v1 = *it, v2 = *(++it);
		line(v1.x, v1.y, v2.x, v2.y);
	}
	Vertice v1 = *rit, v2 = *polygon.begin();
	line(v1.x, v1.y, v2.x, v2.y);
}

void draw(std::list<Vertice> &window, std::list<Vertice> &polyVertices){
	setcolor(WHITE);
	drawPolygon(window);
	setcolor(MAGENTA);
	drawPolygon(polyVertices);
}

bool inside(Vertice r, Vertice s, Vertice v){
	int x1 = r.x, y1 = r.y, x2 = s.x, y2 = s.y;
	int x = v.x, y = v.y;
	int d = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
	std::cout << d << std::endl;
	// d > 0 if point on right side of edge
	std::cout << ((d >= 0) ? "True" : "False");
	return(d >= 0);
}

Vertice intersection(Vertice p, Vertice q, Vertice r, Vertice s){
	int x1 = p.x, y1 = p.y, x2 = q.x, y2 = q.y;
	int x3 = r.x, y3 = r.y, x4 = s.x, y4 = s.y;

	int x = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) /
			((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
	int y = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) /
			((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

	return Vertice(x, y);
}

void SutherlandHodgmanPolygonClipping(Vertice r, Vertice s, std::list<Vertice> &polyVertices){
	std::list<Vertice>::iterator p = polyVertices.end(); p--;
	for (std::list<Vertice>::iterator q = polyVertices.begin(); q != polyVertices.end(); ++q){
		if (inside(r, s , *p)){
			if (!inside(r, s, *q)){ // Edge intersecting
				polyVertices.insert(q, intersection(*p, *q, r, s));
			}
		} else {
			if (inside(r, s, *q)){ // Edge intersecting
				if (p != (--polyVertices.end())){
					polyVertices.insert(q, intersection(*p, *q, r, s));
					polyVertices.erase(p);
				} else
					polyVertices.push_back(intersection(*p, *q, r, s));
			}
		}
		p = q;
	}
	std::cout << "HELL" << std::endl;
}

void doCLipping(std::list<Vertice>& window, std::list<Vertice> &polyVertices){
	Vertice r = window.back(), s;
	for (Vertice & s: window){
		SutherlandHodgmanPolygonClipping(r, s, polyVertices);
		r = s;
	}
}

int main(){
	std::cout << "Clipping window" << std::endl;
	std::list<Vertice> window = inputPolygon();
	std::cout << "Polygon to be clipped" << std::endl;
	std::list<Vertice> polyVertices = inputPolygon();

	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);

	draw(window, polyVertices);
	getch();
	doCLipping(window, polyVertices);
	cleardevice();
	draw(window, polyVertices);
	getch();
	closegraph();

	return 0;
}