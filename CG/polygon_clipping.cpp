#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <list>

struct Vertice {
	int x, y;
	Vertice(int x, int y){
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

Vertice inputVMin(){
	std::cout << "Enter top left vertice of clipping window" << std::endl;
	return inputVertice();
}

Vertice inputVMax(){
	std::cout << "Enter bottom right vertice of clipping window" << std::endl;
	return inputVertice();
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

void draw(Vertice vmin, Vertice vmax, std::list<Vertice> &polyVertices){
	setcolor(WHITE);
	line(vmin.x, vmin.y, vmax.x, vmin.y);
	line(vmax.x, vmin.y, vmax.x, vmax.y);
	line(vmax.x, vmax.y, vmin.x, vmax.y);
	line(vmin.x, vmax.y, vmin.x, vmin.y);
	setcolor(MAGENTA);
	drawPolygon(polyVertices);
}

std::list<Vertice> clipTop(int bound, std::list<Vertice> &polyVertices){
	std::list<Vertice> clippedPoly;
	std::list<Vertice>::iterator p = polyVertices.end(); p--;
	for (std::list<Vertice>::iterator q = polyVertices.begin(); q != polyVertices.end(); ++q){
		if (q->y >= bound){ // q inside
			if (p->y >= bound){ // p inside
				clippedPoly.push_back(*q);
			} else { // Edge intersecting
				int x = p->x + (q->x - p->x)*(bound - p->y)/(q->y - p->y);
				int y = bound;
				clippedPoly.push_back(Vertice(x,y));
				clippedPoly.push_back(*q);
			}
		} else {
			if (p->y >= bound){ // p inside, Edge intersecting
				int x = p->x + (q->x - p->x)*(bound - p->y)/(q->y - p->y);
				int y = bound;
				clippedPoly.push_back(Vertice(x,y));
			}
		}
		p = q;
	}
	return clippedPoly;
}

std::list<Vertice> clipRight(int bound, std::list<Vertice> &polyVertices){
	std::list<Vertice> clippedPoly;
	std::list<Vertice>::iterator p = polyVertices.end(); p--;
	for (std::list<Vertice>::iterator q = polyVertices.begin(); q != polyVertices.end(); ++q){
		if (q->x <= bound){ // q inside
			if (p->x <= bound){ // p inside
				clippedPoly.push_back(*q);
			} else { // Edge intersecting
				int x = bound;
				int y = p->y + (q->y - p->y)*(bound - p->x)/(q->x - p->x);
				clippedPoly.push_back(Vertice(x,y));
				clippedPoly.push_back(*q);
			}
		} else {
			if (p->x <= bound){ // p inside, Edge intersecting
				int x = bound;
				int y = p->y + (q->y - p->y)*(bound - p->x)/(q->x - p->x);
				clippedPoly.push_back(Vertice(x,y));
			}
		}
		p = q;
	}
	return clippedPoly;
}

std::list<Vertice> clipBottom(int bound, std::list<Vertice> &polyVertices){
	std::list<Vertice> clippedPoly;
	std::list<Vertice>::iterator p = polyVertices.end(); p--;
	for (std::list<Vertice>::iterator q = polyVertices.begin(); q != polyVertices.end(); ++q){
		if (q->y <= bound){ // q inside
			if (p->y <= bound){ // p inside
				clippedPoly.push_back(*q);
			} else { // Edge intersecting
				int x = p->x + (q->x - p->x)*(bound - p->y)/(q->y - p->y);
				int y = bound;
				clippedPoly.push_back(Vertice(x,y));
				clippedPoly.push_back(*q);
			}
		} else {
			if (p->y <= bound){ // p inside, Edge intersecting
				int x = p->x + (q->x - p->x)*(bound - p->y)/(q->y - p->y);
				int y = bound;
				clippedPoly.push_back(Vertice(x,y));
			}
		}
		p = q;
	}
	return clippedPoly;
}

std::list<Vertice> clipLeft(int bound, std::list<Vertice> &polyVertices){
	std::list<Vertice> clippedPoly;
	std::list<Vertice>::iterator p = polyVertices.end(); p--;
	for (std::list<Vertice>::iterator q = polyVertices.begin(); q != polyVertices.end(); ++q){
		if (q->x >= bound){ // q inside
			if (p->x >= bound){ // p inside
				clippedPoly.push_back(*q);
			} else { // Edge intersecting
				int x = bound;
				int y = p->y + (q->y - p->y)*(bound - p->x)/(q->x - p->x);
				clippedPoly.push_back(Vertice(x,y));
				clippedPoly.push_back(*q);
			}
		} else {
			if (p->x >= bound){ // p inside, Edge intersecting
				int x = bound;
				int y = p->y + (q->y - p->y)*(bound - p->x)/(q->x - p->x);
				clippedPoly.push_back(Vertice(x,y));
			}
		}
		p = q;
	}
	return clippedPoly;
}

std::list<Vertice> doCLipping(Vertice &vmin, Vertice &vmax, std::list<Vertice> &polyVertices){
	// clipRight(Vertice(vmax.x, vmin.y), Vertice(vmax.x, vmax.y), polyVertices);
	std::list<Vertice> clippedPoly = clipTop(vmin.y, polyVertices);
	clippedPoly = clipRight(vmax.x, clippedPoly);
	clippedPoly = clipBottom(vmax.y, clippedPoly);
	return clipLeft(vmin.x, clippedPoly);
}

int main(){
	Vertice vmin = inputVMin();
	Vertice vmax = inputVMax();
	std::list<Vertice> polyVertices = inputPolygon();

	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);

	draw(vmin, vmax, polyVertices);
	getch();
	std::list<Vertice> clippedPoly = doCLipping(vmin, vmax, polyVertices);
	cleardevice();
	draw(vmin, vmax, clippedPoly);
	getch();
	closegraph();

	return 0;
}