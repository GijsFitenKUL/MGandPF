#include "../Libs/bitmap_image.hpp"
#include "../Libs/AStarCell.cpp"
#include <queue>
#include <chrono>

using namespace std;

const double aStarInfty = __DBL_MAX__;
priority_queue<AstarCell> aStarPQ = {};
vector<AstarCell> aStarCellArray = {};

int aStarStart;
int aStarGoal;

//function declaration

void Astar(string, int, int);

void aStarCheckNeighbours(int, int, int);

void aStarLoadMap(string, int, int);
void aStarExportMap(int, int);

//--------------functions--------------------------


void Astar(string bmpmap, int WIDTH, int HEIGHT){
    cout << "A* ALGORITHM:\n";
    aStarCellArray.resize(WIDTH * HEIGHT);

    aStarLoadMap(bmpmap,  WIDTH, HEIGHT);

    cout << "Starting A* algorithm:\n";
    auto aStarStarttime = chrono::high_resolution_clock::now();
    bool reachedEnd = false;
    while(!aStarPQ.empty() && !reachedEnd){
        AstarCell next = aStarPQ.top();
        aStarPQ.pop();
        if(next.getPos() == aStarGoal){reachedEnd = true;}

        if(!aStarCellArray[next.getPos()].isVisited()){
            aStarCellArray[next.getPos()].visit();
            aStarCheckNeighbours(next.getPos(), WIDTH, HEIGHT);
        }
    }

    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - aStarStarttime);
    cout << "Path found in: " << duration.count() << " microseconds.\n";

    aStarExportMap(WIDTH, HEIGHT);
    cout << "All done\n\n";
    return;
}


//--------------Helper Functions-------------------


void aStarCheckNeighbours(int pos, int WIDTH, int HEIGHT){
    double currentDistance = aStarCellArray[pos].getDist() + 1;

    if(pos % WIDTH != WIDTH - 1){
        
        if(aStarCellArray[pos + 1].getDist() > currentDistance){
            aStarCellArray[pos + 1].setDist(currentDistance);
            aStarCellArray[pos + 1].setParent(pos);
            
            AstarCell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos + 1);
            newCell.setGoal(aStarGoal);
            newCell.setWidth(WIDTH);
            aStarPQ.push(newCell);
        }
    }

    if(pos % WIDTH != 0){
        if(aStarCellArray[pos - 1].getDist() > currentDistance){
            aStarCellArray[pos - 1].setDist(currentDistance);
            aStarCellArray[pos - 1].setParent(pos);

            AstarCell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos - 1);
            newCell.setGoal(aStarGoal);
            newCell.setWidth(WIDTH);
            aStarPQ.push(newCell);
        }
    }

    if(pos > WIDTH){
        if(aStarCellArray[pos - WIDTH].getDist() > currentDistance){
            aStarCellArray[pos - WIDTH].setDist(currentDistance);
            aStarCellArray[pos - WIDTH].setParent(pos);
            
            AstarCell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos - WIDTH);
            newCell.setGoal(aStarGoal);
            newCell.setWidth(WIDTH);
            aStarPQ.push(newCell);
        }
    }

    if(pos < WIDTH * (HEIGHT - 1)){
        if(aStarCellArray[pos + WIDTH].getDist() > currentDistance){
            aStarCellArray[pos + WIDTH].setDist(currentDistance);
            aStarCellArray[pos + WIDTH].setParent(pos);
            
            AstarCell newCell;
            newCell.setDist(currentDistance);
            newCell.setPos(pos + WIDTH);
            newCell.setGoal(aStarGoal);
            newCell.setWidth(WIDTH);
            aStarPQ.push(newCell);
        }
    }
    return;
}


//--------------Image Related Functions------------


void aStarLoadMap(string bmpfile,int WIDTH, int HEIGHT){
    cout << "Starting load of bitmap\n";
    bitmap_image DijkstraMaze(bmpfile);

    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            rgb_t color = DijkstraMaze.get_pixel(i,j);
            AstarCell tempCell;
            tempCell.unvisit();
            tempCell.setPos(i + j * WIDTH);
            tempCell.setDist(aStarInfty);
            tempCell.setWidth(WIDTH);

            //aStarStart node, has distance 0
            if(color.red == 0 && color.blue == 0 && color.green == 255){
                aStarStart = i + j * WIDTH;
                tempCell.setDist(0);
                aStarPQ.push(tempCell);

            //aStarGoal node
            }else if(color.red == 255 && color.blue == 0 && color.green == 0){
                aStarGoal = i + j * WIDTH;

            //all wall nodes (always returns infinity as distance)
            }else if(color.red == 0 && color.blue == 0 && color.green == 0){
                tempCell.setWall();
            }
            aStarCellArray[i + j * WIDTH] = tempCell;
        }
    }

    for(i = 0; i < WIDTH * HEIGHT; ++i){
        aStarCellArray[i].setGoal(aStarGoal);
    }
    return;
}


void aStarExportMap( int WIDTH, int HEIGHT){
    cout << "aStarStarting export of bitmap\n";
    bitmap_image DijkstraSolved(WIDTH, HEIGHT);

    int i,j;
    for(i = 0; i < WIDTH; ++i){
        for(j = 0; j < HEIGHT; ++j){
            if(aStarCellArray[i + j * WIDTH].isWall()){
                DijkstraSolved.set_pixel(i, j, 0, 0, 0);
            }
            else if(aStarCellArray[i + j * WIDTH].isVisited()){
                DijkstraSolved.set_pixel(i, j, 0, 100, 200);
            }
            else{
                DijkstraSolved.set_pixel(i, j, 255, 255, 255);
            }
        }
        
    }

    int previousInPath = aStarGoal;
    int length = 0;
    while(previousInPath != aStarStart){
        DijkstraSolved.set_pixel(previousInPath % WIDTH, previousInPath / WIDTH, 0, 0, 255);
        previousInPath = aStarCellArray[previousInPath].getParent();
        ++length;
    }

    cout << "path to end is of length: " << length << endl;

    DijkstraSolved.set_pixel(aStarStart % WIDTH, aStarStart / WIDTH, 0, 255, 0);
    DijkstraSolved.set_pixel(aStarGoal % WIDTH, aStarGoal / WIDTH, 255, 0, 0);

    DijkstraSolved.save_image("./Bitmaps/Solved/AStarSolved.bmp");
    return;
}