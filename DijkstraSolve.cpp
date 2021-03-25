#include "bitmap_image.hpp"
#include <set>
#include <queue>
#include <chrono>
#include <unordered_map>

using namespace std;

bitmap_image maze("maze.bmp");
const int infty = INT_MAX;
void loadMap();
void dijkstraSolve();
void dijkstraStep();

class Cell{
    public:
        int xpos;
        int ypos;
        int dist = infty;
        int parentx;
        int parenty;

    Cell(int xpos, int ypos)
    : xpos(xpos), ypos(ypos){}
};

bool operator<(const Cell& c1, const Cell& c2)
{
    return c1.dist > c2.dist;
}

priority_queue<Cell> pq = {};
set<Cell> visited = {};
set<Cell> path = {};
unordered_map<int, int> cell_map;
bool done = false;

int goalx;
int goaly;
int WIDTH;
int HEIGHT;

int main(){
    auto starttime = chrono::high_resolution_clock::now();
    loadMap();
    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Execution done in: " << duration.count() << " microseconds.\n";
    cout << "All done!";
    return 0;
}

void loadMap(){
    cout << "Starting load of bitmap\n";
    //load the maze.bmp to the maze object and intialise some global variables
    bitmap_image maze("maze.bmp");
    int WIDTH = maze.width();
    int HEIGHT = maze.height();

    //extract the graph from the bitmap and create new cells for all white pixels
    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            rgb_t color = maze.get_pixel(i,j);
            if(color.red == 0 && color.blue == 0 && color.green == 255){
                Cell c = Cell(i, j);
                c.dist = 0;
                pq.push(c);
            }else if(color.red == 255 && color.blue == 0 && color.green == 0){
                goalx = i;
                goaly = j;
            }
        }
    }
}

void dijkstraSolve(){
    while(!pq.empty() && !done){
        //do something lmao
    }
}