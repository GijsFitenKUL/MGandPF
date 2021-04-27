#include "Creators/RecursiveBacktrackgenerator.cpp"
#include "Solvers/Dijkstra.cpp"

using namespace std;

int main(){
    //All of the maze generators
    generateRecursiveMaze();

    //All of the maze solvers, on all generated bitmaps
    Dijkstra("this is temporary");
    return 0;
}