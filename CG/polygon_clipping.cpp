#include <stdio.h>

struct Vertice {
	int x, y;
	Vertice(int x, int y){
		this.x = x;
		this.y = y;
	}
};

struct Polygon {
	int count;
	Vertice vertices;
	Polygon(int count){
		this.count = count;
		vertices = new Vertice(count);
	}
	void setVertice(int i, int x, int y){
		Vertice vertice = new Vertice(x, y);
		vertices[i] = vertice;
	}
	Vertice getVertice(int i){
		return vertices[i];
	}
	int getCount(){
		return count;
	}
};

void input(Polygon &polygon, Vertice &vmin, Vertice &vmax){
	std::cout << "Enter Vertices of clipping window" << std::endln;
	std::cout << "Enter number of vertices in polygon: ";
	int count;
	std::cin >> count;
	polygon = new Polygon(count);
	for (int i = 0; i < count; i++){
		int x, y;
		std::cin >> x >> y;
		polygon.setVertice(i, x, y);
	}
}

int main(){
	Vertice vmin, vmax;
	Polygon polygon;
	void input(&vmin, &vmax, &polygon);
	
	return 0;
}
