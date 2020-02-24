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

struct ActiveEdge {
    int y_max, x_min, dx, yx;
    ActiveEdge(Vertice &v1, Vertice &v2){
        if (v1.y < v2.y) x_min = v1.x;
        else x_min = v2.x;
        if (v1.y > v2.y) y_max = v1.y;
        else y_max = v2.y;
        dx = v2.x - v1.x;
        yx = v2.y - v1.y;
    }
};

struct GlobalEdgeTable {
    std::list<std::list<ActiveEdge>> globalEdgeTable;
    std::list<int> scan_lines;

    GlobalEdgeTable(std::list<Vertice> &polyVertices){
        // Find scan lines at polygon vertices
        for(auto vertice: polyVertices)
            scan_lines.push_back(vertice.y);
        scan_lines.unique();
        scan_lines.sort();
        // Create Active Edge Tables for scan lines
        for(auto scan_line: scan_lines){
            std::list<ActiveEdge> previousEdgeTable;
            if (globalEdgeTable.size() != 0)
                previousEdgeTable.assign(
                    globalEdgeTable.back().begin(),
                    globalEdgeTable.back().end()
                );
            std::list<ActiveEdge> activeEdgeTable;
            // Copy last active edges which still intersect with current scan line
            for (auto edge: previousEdgeTable){
                if(edge.y_max >= scan_line)
                    activeEdgeTable.push_back(edge);
            }

            // Add intersecting edges if not already present in AET
            Vertice i = polyVertices.back();
            for (auto j: polyVertices){
                if (i.y == scan_line || j.y == scan_line){
                    ActiveEdge activeEdge(i, j);
                    if(!duplicate(activeEdge, activeEdgeTable))
                        activeEdgeTable.push_back(activeEdge);
                }
                i = j;
            }

            // Sort the activate edges in increasing order of x_min
            // and add to the active edge table
            activeEdgeTable.sort(compareEdge);
            globalEdgeTable.push_back(activeEdgeTable);

            // Display the active edge table
            std::cout << "[" << scan_line << "]";
            for(auto edge: activeEdgeTable){
                std::cout << "-->" << edge.y_max << " " << edge.x_min;
            }
            std::cout << std::endl;
        }
    }

    private:
    bool static compareEdge(ActiveEdge& edge1, ActiveEdge& edge2){
        return (edge1.x_min < edge2.x_min);
    }
    bool duplicate(ActiveEdge& activeEdge, std::list<ActiveEdge>& activeEdgeTable){
        for(auto edge: activeEdgeTable){
            if (
                edge.x_min == activeEdge.x_min &&
                edge.y_max == activeEdge.y_max &&
                edge.dx == activeEdge.dx &&
                edge.yx == activeEdge.yx)
                return true;
        } return false;
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

int main(){
    std::list<Vertice> polyVertices = inputPolygon();
    GlobalEdgeTable globalEdgeTable(polyVertices);
}