#include "../Libs/bitmap_image.hpp"
#include "../Libs/Cell.cpp"
#include <chrono>

using namespace std;

const int infty = INT_MAX;
int start;
int goal;
Cell closestCell;

bitmap_image DijkstraMaze(string bmpmap);

void loadMap(string, Cell[], int, int);
void exportMap(Cell[], int, int);
void DijkstraTimed(string, int, int);

void DijkstraSolve(int, Cell[], int, int, chrono::_V2::system_clock::time_point);
void updateNeighbours(int, Cell[], int, int);
int getClosestCell(Cell[], int, int);

void DijkstraTimed(string bmpmap, int WIDTH, int HEIGHT){
    cout << "\nDIJKSTRA:\n";
    auto starttime = chrono::high_resolution_clock::now();
    Cell cellArray [WIDTH * HEIGHT];
    loadMap(bmpmap, cellArray, WIDTH, HEIGHT);
    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Bitmap done loading in: " << duration.count() << " microseconds.\n";

    cout << "\nStarting solve with Dijkstra's algorithm\n";
    starttime = chrono::high_resolution_clock::now();
    DijkstraSolve(start, cellArray, WIDTH, HEIGHT, starttime);
    cout << "All done!";

    return;
}

void loadMap(string bmpfile, Cell cellArray[], int WIDTH, int HEIGHT){
    cout << "Starting load of bitmap\n";
    //load the DijkstraMaze.bmp to the DijkstraMazeobject and intialise some global variables
    bitmap_image DijkstraMaze(bmpfile);

    //extract the graph from the bitmap and initialise the set of cellArray nodes
    //also place the goal coordinates
    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            rgb_t color = DijkstraMaze.get_pixel(i,j);

            //start node
            if(color.red == 0 && color.blue == 0 && color.green == 255){
                start = i + j * WIDTH;
                cellArray[i + j * WIDTH].setDist(0);

            //goal node
            }else if(color.red == 255 && color.blue == 0 && color.green == 0){
                goal = i + j * WIDTH;

            //all path nodes
            }else if(color.red == 0 && color.blue == 0 && color.green == 0){
                cellArray[i + j * WIDTH].setWall();
            }
        }
    }
    return;
}

void exportDijkstraMap(Cell cellArray[], int WIDTH, int HEIGHT){
    cout << "Starting export of bitmap\n";
    bitmap_image DijkstraSolved(WIDTH, HEIGHT);

    int i;
    for(i = 0; i < WIDTH * HEIGHT; ++i){
        if(cellArray[i].isWall()){
            DijkstraSolved.set_pixel(i % WIDTH, i / WIDTH, 0, 0, 0);
        }
        else if(!cellArray[i].isVisited()){
            DijkstraSolved.set_pixel(i % WIDTH, i / WIDTH, 255, 255, 255);
        }
        else if(cellArray[i].isVisited()){
            DijkstraSolved.set_pixel(i % WIDTH, i / WIDTH, 0, 0, 255);
        }
    }

    DijkstraSolved.set_pixel(start % WIDTH, start / WIDTH, 0, 255, 0);
    

    int previousInPath = goal;

    while(previousInPath != start){
        DijkstraSolved.set_pixel(previousInPath % WIDTH, previousInPath / WIDTH, 255, 0, 0);
        previousInPath = cellArray[previousInPath].getParent();
    }

    DijkstraSolved.save_image("./Bitmaps/DijkstraSolved.bmp");
    return;
}

int getClosestCell(Cell cellArray[], int WIDTH, int HEIGHT){
    //will return the unvisited cell with the smallest distance from the start node.
    double closest = __DBL_MAX__;
    int closestCell = -1;
    for(int i = 0; i < WIDTH * HEIGHT; ++i){
        if(cellArray[i].getDist() < closest && cellArray[i].isVisited() == false){
            closest = cellArray[i].getDist();
            closestCell = i;
        }
    }
    return closestCell;
}

void updateNeighbours(int pos, Cell cellArray[], int WIDTH, int HEIGHT){
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

    if(pos > WIDTH){
        if(cellArray[pos - WIDTH].getDist() > currentDistance + 1){
            cellArray[pos - WIDTH].setDist(currentDistance + 1);
            cellArray[pos - WIDTH].setParent(pos);
        }
    }

    if(pos < WIDTH * (HEIGHT - 1)){
        if(cellArray[pos + WIDTH].getDist() > currentDistance + 1){
            cellArray[pos + WIDTH].setDist(currentDistance + 1);
            cellArray[pos + WIDTH].setParent(pos);
        }
    }
    return;
}

void DijkstraSolve(int pos, Cell cellArray[], int WIDTH, int HEIGHT, chrono::_V2::system_clock::time_point starttime){
    //mark this cell as visited and update neighbours
    cellArray[pos].visit();
    updateNeighbours(pos, cellArray, WIDTH, HEIGHT);

    //check next position
    int next = getClosestCell(cellArray, WIDTH, HEIGHT);

    if(next == goal){
        cout << "path found!\n";
        auto stoptime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
        cout << "Dijkstra done: " << duration.count() << " microseconds.\n\n";
        exportDijkstraMap(cellArray, WIDTH, HEIGHT);
        return;
    }

    if(next == -1){
        cout << "No path found\n";
        return;
    }

    DijkstraSolve(next, cellArray, WIDTH, HEIGHT, starttime);
    return;
}