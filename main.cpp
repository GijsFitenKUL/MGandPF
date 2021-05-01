#include "Creators/RecursiveBacktrackgenerator.cpp"
#include "Solvers/Dijkstra.cpp"

using namespace std;
const int WIDTH = 101;
const int HEIGHT = 101;

void generateTestMap();

int main(){
    //All of the maze generators
    generateRecursiveMaze(WIDTH, HEIGHT);
    //generateTestMap();

    //All of the maze solvers, on all generated bitmaps
    Dijkstra("./Bitmaps/Mazes/RecursiveBacktrackMaze.bmp", WIDTH, HEIGHT);
    //Dijkstra("./Bitmaps/test.bmp", WIDTH, HEIGHT);
    return 1;
}

void generateTestMap(){
    cout << "Starting export of bitmap\n";
    bitmap_image testMap(WIDTH, HEIGHT);

    for(int i = 0; i < WIDTH * HEIGHT; ++i){
        testMap.set_pixel(i % WIDTH, i / WIDTH, 255, 255, 255);
    }
    
    testMap.set_pixel(WIDTH / 2, HEIGHT / 2, 0, 255, 0);
    testMap.set_pixel(WIDTH - 1, HEIGHT / 2, 255, 0, 0);

    testMap.save_image("./Bitmaps/test.bmp");
    return;
}