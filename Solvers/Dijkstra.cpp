#include "../Libs/bitmap_image.hpp"
#include "../Libs/Cell.cpp"
#include <set>
#include <queue>
#include <chrono>
#include <unordered_map>

using namespace std;

const int infty = INT_MAX;
int start;
int goal;
int WIDTH;
int HEIGHT;
Cell closestCell;
Cell cellArray[];

string bmpmap;
bitmap_image DijkstraMaze(string bmpmap);

set<Cell> path = {};

void loadMap(string bmpmap);
void Dijkstra();

void DijkstraSolve(int pos);
void updateNeighbours(int pos);
int getClosestCell();

void Dijkstra(string bmpmap){
    bmpmap = "./Bitmaps/RecursiveBacktrackMaze.bmp";
    cout << "DIJKSTRA\n";
    auto starttime = chrono::high_resolution_clock::now();
    loadMap(bmpmap);
    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Bitmap done loading in: " << duration.count() << " microseconds.\n";

    starttime = chrono::high_resolution_clock::now();
    DijkstraSolve(start);
    stoptime = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Dijkstra done: " << duration.count() << " microseconds.\n";

    cout << "All done!";
    return;
}

void loadMap(string bmpfile){
    cout << "Starting load of bitmap\n";
    //load the DijkstraMaze.bmp to the DijkstraMazeobject and intialise some global variables
    bitmap_image DijkstraMaze(bmpfile);
    int WIDTH = DijkstraMaze.width();
    int HEIGHT = DijkstraMaze.height();

    Cell unvisited [WIDTH * HEIGHT];
    //extract the graph from the bitmap and initialise the set of cellArray nodes
    //also place the goal coordinates
    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            rgb_t color = DijkstraMaze.get_pixel(i,j);

            //start node
            if(color.red == 0 && color.blue == 0 && color.green == 255){
                start = i + j * WIDTH;
                unvisited[i + j * WIDTH].setDist(0);

            //goal node
            }else if(color.red == 255 && color.blue == 0 && color.green == 0){
                int goal = i + j * WIDTH;

            //all path nodes
            }else if(color.red == 0 && color.blue == 0 && color.green == 0){
                unvisited[i + j * WIDTH].setWall();
            }
        }
    }
}

int getClosestCell(){
    //will return the unvisited cell with the smallest distance from the start node.
    double closest = __DBL_MAX__;
    int closestCell = -1;
    for(int i = 0; i < WIDTH * HEIGHT; ++i){
        if(cellArray[i].getDist() < closest && !cellArray[i].isVisited()){
            closest = cellArray[i].getDist();
            closestCell = i;
        }
    }
    return closestCell;
}

void updateNeighbours(int pos){
    double currentDistance = cellArray[pos].getDist();

    if(pos % WIDTH != WIDTH - 1){
        if(cellArray[pos + 1].getDist() > currentDistance + 1){
            cellArray[pos + 1].setDist(currentDistance + 1);
            cellArray[pos + 1].setParent(pos);
        }
    }

    if(pos % WIDTH != 0){
        if(cellArray[pos - 1].getDist() > currentDistance + 1){
            cellArray[pos - 1].setDist(currentDistance + 1);
            cellArray[pos - 1].setParent(pos);
        }
    }

    if(pos < WIDTH){
        if(cellArray[pos - WIDTH].getDist() > currentDistance + 1){
            cellArray[pos - WIDTH].setDist(currentDistance + 1);
            cellArray[pos - WIDTH].setParent(pos);
        }
    }

    if(pos > WIDTH * (HEIGHT - 1)){
        if(cellArray[pos + WIDTH].getDist() > currentDistance + 1){
            cellArray[pos + WIDTH].setDist(currentDistance + 1);
            cellArray[pos + WIDTH].setParent(pos);
        }
    }
    return;
}

void DijkstraSolve(int pos){
    //stop solving if the goal has been reached
    if(pos == goal){return;}

    //mark this cell as visited and update neighbours
    cellArray[pos].visit();
    updateNeighbours(pos);

    //check next position
    int next = getClosestCell();
    if(next == -1){return;}

    DijkstraSolve(next);
    return;
}