#include "../Libs/bitmap_image.hpp"
#include "../Libs/Cell.cpp"
#include <set>
#include <queue>
#include <chrono>
#include <unordered_map>

using namespace std;

const int infty = INT_MAX;
string bmpmap;
bitmap_image maze(string bmpmap);
priority_queue<Cell> pq = {};
set<Cell> visited = {};
set<Cell> path = {};
unordered_map<int, int> cell_map;

void loadMap(string bmpmap);
void dijkstraSolve();
void dijkstraStep();

int DijkstraSolve(){
    int WIDTH;
    int HEIGHT;
    bmpmap = "maze.bmp";

    auto starttime = chrono::high_resolution_clock::now();
    loadMap(bmpmap);
    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Execution done in: " << duration.count() << " microseconds.\n";
    cout << "All done!";
    return 0;
}

void loadMap(string bmpfile){
    cout << "Starting load of bitmap\n";
    //load the maze.bmp to the maze object and intialise some global variables
    bitmap_image maze(bmpfile);
    int WIDTH = maze.width();
    int HEIGHT = maze.height();

    //extract the graph from the bitmap and push start to priorityqueue
    //also place the goal coordinates
    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            rgb_t color = maze.get_pixel(i,j);
            if(color.red == 0 && color.blue == 0 && color.green == 255){
                Cell c = Cell(i, j);
                c.dist = 0;
                pq.push(c);
            }else if(color.red == 255 && color.blue == 0 && color.green == 0){
                int goalx = i;
                int goaly = j;
            }
        }
    }
}