#include <iostream>
#include <stdio.h>

struct Vertice {
	int x, y;
	Vertice(int x, int y){
		this->x = x;
		this->y = y;
	}
};

struct Polygon {
	int vCount;
	Vertice ** vertices;
	Polygon(int vCount){
		this->vCount = vCount;
		vertices = new Vertice*[vCount];
	}
	void setiVertice(int i, Vertice * vertice){
		vertices[i] = vertice;
	}
	Vertice * getVertice(int i){
		return vertices[i];
	}
	int getvCount(){
		return vCount;
	}
};

Vertice* inputVertice(){
	int x, y;
	std::cout << "X: ";
	std::cin >> x;
	std::cout << "Y: ";
	std::cin >> y;
	return new Vertice(x, y);
}

Vertice inputVMin(){
	std::cout << "Enter top left vertice of clipping window" << std::endl;
	return *inputVertice();
}

Vertice inputVMax(){
	std::cout << "Enter bottom right vertice of clipping window" << std::endl;
	return *inputVertice();
}

Polygon inputPolygon(){
	std::cout << "Enter number of vertices in polygon: ";
	int vCount;
	std::cin >> vCount;
	Polygon polygon(vCount);
	for (int i = 0; i < vCount; i++){
		std::cout << "Enter vertice " << i + 1 << std::endl;
		polygon.setiVertice(i, inputVertice());
	}
	return polygon;
}

void doClipping(){

}

int main(){
	Vertice vmin = inputVMin();
	Vertice vmax = inputVMax();
	Polygon polygon = inputPolygon();

	
	return 0;
}
