#include "../Libs/bitmap_image.hpp"
#include "../Libs/Cell.cpp"
#include <queue>
#include <chrono>

using namespace std;

const double infty = __DBL_MAX__;
priority_queue<Cell> pq = {};
vector<Cell> cellArray = {};

int start;
int goal;

//function declaration

void Dijkstra(string, int, int);

void checkNeighbours(int, int, int);

void loadMap(string, int, int);
void exportMap(int, int);

//--------------functions--------------------------


void Dijkstra(string bmpmap, int WIDTH, int HEIGHT){
    cout << "DIJKSTRA'S ALGORITHM:\n";
    cellArray.resize(WIDTH * HEIGHT);

    loadMap(bmpmap,  WIDTH, HEIGHT);

    cout << "Starting Dijkstra's algorithm:\n";
    auto starttime = chrono::high_resolution_clock::now();
    bool reachedEnd = false;
    while(!pq.empty() && !reachedEnd){
        Cell next = pq.top();
        pq.pop();
        if(next.getPos() == goal){reachedEnd = true;}

        if(!cellArray[next.getPos()].isVisited()){
            cellArray[next.getPos()].visit();
            checkNeighbours(next.getPos(), WIDTH, HEIGHT);
        }
    }

    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Path found in: " << duration.count() << " microseconds.\n";

    exportMap(WIDTH, HEIGHT);
    cout << "All done\n\n";
    return;
}


//--------------Helper Functions-------------------


void checkNeighbours(int pos, int WIDTH, int HEIGHT){
    double currentDistance = cellArray[pos].getDist() + 1;
    
    if(pos % WIDTH != WIDTH - 1){
        
        if(cellArray[pos + 1].getDist() > currentDistance){
            cellArray[pos + 1].setDist(currentDistance);
            cellArray[pos + 1].setParent(pos);
            
            Cell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos + 1);
            pq.push(newCell);
        }
    }

    if(pos % WIDTH != 0){
        if(cellArray[pos - 1].getDist() > currentDistance){
            cellArray[pos - 1].setDist(currentDistance);
            cellArray[pos - 1].setParent(pos);

            Cell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos - 1);
            pq.push(newCell);
        }
    }

    if(pos > WIDTH){
        if(cellArray[pos - WIDTH].getDist() > currentDistance){
            cellArray[pos - WIDTH].setDist(currentDistance);
            cellArray[pos - WIDTH].setParent(pos);
            
            Cell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos - WIDTH);
            pq.push(newCell);
        }
    }

    if(pos < WIDTH * (HEIGHT - 1)){
        if(cellArray[pos + WIDTH].getDist() > currentDistance){
            cellArray[pos + WIDTH].setDist(currentDistance);
            cellArray[pos + WIDTH].setParent(pos);
            
            Cell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos + WIDTH);
            pq.push(newCell);
        }
    }
    return;
}


//--------------Image Related Functions------------


void loadMap(string bmpfile,int WIDTH, int HEIGHT){
    cout << "Starting load of bitmap\n";
    bitmap_image DijkstraMaze(bmpfile);

    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            rgb_t color = DijkstraMaze.get_pixel(i,j);
            Cell tempCell;
            tempCell.unvisit();
            tempCell.setPos(i + j * WIDTH);
            tempCell.setDist(infty);

            //start node, has distance 0
            if(color.red == 0 && color.blue == 0 && color.green == 255){
                start = i + j * WIDTH;
                tempCell.setDist(0);
                pq.push(tempCell);

            //goal node
            }else if(color.red == 255 && color.blue == 0 && color.green == 0){
                goal = i + j * WIDTH;

            //all wall nodes (always returns infinity as distance)
            }else if(color.red == 0 && color.blue == 0 && color.green == 0){
                tempCell.setWall();
            }
            cellArray[i + j * WIDTH] = tempCell;
        }
    }
    return;
}


void exportMap( int WIDTH, int HEIGHT){
    cout << "Starting export of bitmap\n";
    bitmap_image DijkstraSolved(WIDTH, HEIGHT);

    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            if(cellArray[i + j * WIDTH].isWall()){
                DijkstraSolved.set_pixel(i, j, 0, 0, 0);
            }
            else if(cellArray[i + j * WIDTH].isVisited()){
                DijkstraSolved.set_pixel(i, j, 0, 100, 200);
            }
            else{
                DijkstraSolved.set_pixel(i, j, 255, 255, 255);
            }
        }
        
    }

    int previousInPath = goal;
    int length = 0;
    while(previousInPath != start){
        DijkstraSolved.set_pixel(previousInPath % WIDTH, previousInPath / WIDTH, 0, 0, 255);
        previousInPath = cellArray[previousInPath].getParent();
        ++length;
    }

    cout << "path to end is of length: " << length << endl;

    DijkstraSolved.set_pixel(start % WIDTH, start / WIDTH, 0, 255, 0);
    DijkstraSolved.set_pixel(goal % WIDTH, goal / WIDTH, 255, 0, 0);

    DijkstraSolved.save_image("./Bitmaps/Solved/DijkstraSolved.bmp");
    return;
}