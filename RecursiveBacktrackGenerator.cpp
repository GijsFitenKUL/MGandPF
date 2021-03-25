#include "bitmap_image.hpp"
#include <iostream>
#include <set>
#include <array>
#include <random>
#include <chrono>
using namespace std;

const int WIDTH = 5001;
const int HEIGHT = 5001;
set<int> visited;
bitmap_image maze(WIDTH, HEIGHT);

void recursiveBacktrack(int x, int y);

int main(){
    auto starttime = chrono::high_resolution_clock::now();
    srand(time(NULL));
    //generate random seed
    cout << "Starting maze gen \n";

    //initialise bitmap
    int x,y;
    for(x = 0; x < WIDTH; ++x){
        for(y = 0; y < HEIGHT; ++y){
            maze.set_pixel(x, y, 0, 0, 0);
        }
    }
    cout << "Bitmap initialised\n";

    //create a set of visited cells, will be saves as x + y * width in the set
    recursiveBacktrack(1, 1);

    //place start and finish
    maze.set_pixel(1, 0, 0, 255, 0);
    maze.set_pixel(WIDTH - 2, HEIGHT - 1, 255, 0, 0);

    maze.save_image("maze.bmp");
    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Execution done in: " << duration.count() << " microseconds.\n";
    cout << "All done";
    return 0;
}

void recursiveBacktrack(int x, int y){
    //adds this cell to the list of visited cells
    maze.set_pixel(x, y, 255, 255, 255);
    visited.insert(x + y * WIDTH);

    //cout << "checking maze at " << x <<", " << y << endl;
    //initialises a vector of neighbours
    vector<int> neighbours;

    //checks all neighbours if they are valid add them to possible neighbours
    if(x != WIDTH - 2){
        neighbours.push_back(x + 2 + y * WIDTH);
    }
    if(x != 1){
        neighbours.push_back(x - 2 + y * WIDTH);
    }
    if(y != 1){
        neighbours.push_back(x + (y - 2) * WIDTH);
    }
    if(y != HEIGHT - 2){
        neighbours.push_back(x + (y + 2) * WIDTH);
    }

    //shuffles the set of neighbours
    shuffle(neighbours.begin(), neighbours.end(), default_random_engine(rand()));

    //loop over all neighbours, but first check if they are already visited
    for(int i : neighbours){
        if(visited.find(i) == visited.end()){
            if(x < i % WIDTH){
                maze.set_pixel(x + 1, y, 255, 255, 255);
            }else if(x > i % WIDTH){
                maze.set_pixel(x - 1, y, 255, 255, 255);
            }else if(y < i / HEIGHT){
                maze.set_pixel(x, y + 1, 255, 255, 255);
            }else{maze.set_pixel(x, y - 1, 255, 255, 255);}
            maze.set_pixel(i % WIDTH, i / WIDTH, 255, 255, 255);
            recursiveBacktrack(i % WIDTH, i / WIDTH);
        }
    }
    neighbours.clear();
    return;
}