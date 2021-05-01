#include "../Libs/bitmap_image.hpp"
#include <iostream>
#include <set>
#include <array>
#include <random>
#include <chrono>

using namespace std;

set<int> visited;

bitmap_image RBMaze;

void recursiveBacktrack(int x, int y, int WIDTH, int HEIGHT);

void generateRecursiveMaze(int WIDTH, int HEIGHT){
    cout << "\nRECURSIVE BACKTRACK GENERATOR:\n";
    auto starttime = chrono::high_resolution_clock::now();
    srand(time(NULL));
    //generate random seed
    cout << "Starting maze generation \n";

    //initialise bitmap
    RBMaze.setwidth_height(WIDTH, HEIGHT);

    int x,y;
    for(x = 0; x < WIDTH; ++x){
        for(y = 0; y < HEIGHT; ++y){
            RBMaze.set_pixel(x, y, 0, 0, 0);
        }
    }
    cout << "Bitmap initialised\n";

    //create a set of visited cells, will be saves as x + y * width in the set
    recursiveBacktrack(1, 1, WIDTH, HEIGHT);

    //place start and finish
    RBMaze.set_pixel(1, 0, 0, 255, 0);
    RBMaze.set_pixel(WIDTH - 2, HEIGHT - 1, 255, 0, 0);

    RBMaze.save_image("Bitmaps/Mazes/RecursiveBacktrackMaze.bmp");
    auto stoptime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stoptime - starttime);
    cout << "Execution done in: " << duration.count() << " microseconds.\n";
    cout << "All done\n\n";

    RBMaze.clear();
    visited.~set();
    return;
}

void recursiveBacktrack(int x, int y, int WIDTH, int HEIGHT){
    //adds this cell to the list of visited cells
    RBMaze.set_pixel(x, y, 255, 255, 255);
    visited.insert(x + y * WIDTH);

    //cout << "checking RBMaze at " << x <<", " << y << endl;
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
                RBMaze.set_pixel(x + 1, y, 255, 255, 255);
            }
            else if(x > i % WIDTH){
                RBMaze.set_pixel(x - 1, y, 255, 255, 255);
            }
            else if(y < i / HEIGHT){
                RBMaze.set_pixel(x, y + 1, 255, 255, 255);
            }
            else{
                RBMaze.set_pixel(x, y - 1, 255, 255, 255);
            }
            RBMaze.set_pixel(i % WIDTH, i / WIDTH, 255, 255, 255);
            recursiveBacktrack(i % WIDTH, i / WIDTH, WIDTH, HEIGHT);
        }
    }
    neighbours.clear();
    return;
}