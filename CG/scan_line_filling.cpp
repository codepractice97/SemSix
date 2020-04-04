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

    int y_max, x_min, y_min, x, dx, dy, sum, incr;

    ActiveEdge(Vertice &v1, Vertice &v2){
        if (v1.y < v2.y) x_min = v1.x;
        else x_min = v2.x;
        if (v1.y > v2.y) {
            y_max = v1.y;
            y_min = v2.y;
        } else {
            y_max = v2.y;
            y_min = v1.y;
        }
        x = x_min;
        dx = v2.x - v1.x;
        dy = v2.y - v1.y;
        sum = dy;
        incr = (dx == 0 || dy == 0) ? 0 : (float(dx)/float(dy)) > 0 ? 1 : -1;
        dx = abs(dx); dy = abs(dy);
    }
};

bool static compareEdgeX(ActiveEdge& edge1, ActiveEdge& edge2){
    return (edge1.x < edge2.x);
}
bool static compareEdgeYmin(ActiveEdge& edge1, ActiveEdge& edge2){
    return (edge1.y_min < edge2.y_min);
}

std::list<int> getScanLines(std::list<Vertice> &polyVertices){
    std::list<int> scan_lines;
    for(auto vertice: polyVertices)
        scan_lines.push_back(vertice.y);
    scan_lines.unique();
    scan_lines.sort();
    return scan_lines;
}

std::list<ActiveEdge> createEdgeTable(std::list<Vertice> &polyVertices){
    std::list<ActiveEdge> edgeTable;
    Vertice i = polyVertices.back();
    for (auto j: polyVertices){
        ActiveEdge activeEdge(i, j);
        edgeTable.push_back(activeEdge);
        i = j;
    }
    edgeTable.sort(compareEdgeYmin);
    return edgeTable;
}

void scanLineFilling(std::list<Vertice> &polyVertices){

    std::list<int> scan_lines = getScanLines(polyVertices);
    std::list<ActiveEdge> edgeTable = createEdgeTable(polyVertices);
    std::list<ActiveEdge> activeEdges;

    for (int scan_line = scan_lines.front(); scan_line <= scan_lines.back();){
        while (!edgeTable.empty() && edgeTable.front().y_min == scan_line){
            activeEdges.push_back(edgeTable.front());
            edgeTable.pop_front();
        }
        activeEdges.sort(compareEdgeX);

        bool parity = true;
        auto edge1 = activeEdges.begin();
        for(auto edge2 = ++activeEdges.begin(); edge2 != activeEdges.end(); ++edge2){
            // Skip edge pairs if there vertice is at current scan line
            // and the edges lie on either side of scan line
            if (edge1->y_min == edge2->y_max || edge1->y_max == edge2->y_min)
                continue;
            if (parity){
                for(int px = edge1->x; px <= edge2->x; px++)
                    putpixel(px, scan_line, RED);
            }
            parity = !parity;
            edge1 = edge2;
        }

        scan_line++;

        // Remove edges not interseting next scan line
        for (auto edge = activeEdges.begin(); edge != activeEdges.end(); ++edge){
            if(edge->y_max < scan_line){
                edge = activeEdges.erase(edge);
                edge--;
            }
        }

        // Increment x values depending on slope of edge
        for (auto edge = activeEdges.begin(); edge != activeEdges.end(); ++edge){
            edge->sum += edge->dx;
            while (edge->sum > edge->dy){
                edge->x += edge->incr;
                edge->sum -= edge->dy;
            }
        }
    }
}

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

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    scanLineFilling(polyVertices);
    
    getch();
    closegraph();

    return 0;
}