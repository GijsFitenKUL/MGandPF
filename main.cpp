#include "Creators/RecursiveBacktrackgenerator.cpp"
#include "Solvers/Dijkstra.cpp"

using namespace std;
const int WIDTH = 401;
const int HEIGHT = 401;

int main(){
    //All of the maze generators
    generateRecursiveMaze(WIDTH, HEIGHT);

    //All of the maze solvers, on all generated bitmaps
    DijkstraTimed("./Bitmaps/RecursiveBacktrackMaze.bmp", WIDTH, HEIGHT);
    return 1;
}