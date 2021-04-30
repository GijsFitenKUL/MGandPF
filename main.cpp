#include "Creators/RecursiveBacktrackgenerator.cpp"
#include "Solvers/Dijkstra.cpp"
#include "Solvers/Astar.cpp"

using namespace std;
const int WIDTH = 1001;
const int HEIGHT = 1001;

void generateTestMap();

int main(){
    //generateTestMap();

    //All of the maze generators
    generateRecursiveMaze(WIDTH, HEIGHT);

    //All of the maze solvers, on all generated bitmaps
    Dijkstra("./Bitmaps/Mazes/RecursiveBacktrackMaze.bmp", WIDTH, HEIGHT);
    Astar("./Bitmaps/Mazes/RecursiveBacktrackMaze.bmp", WIDTH, HEIGHT);
    
    
    //Dijkstra("./Bitmaps/test.bmp", WIDTH, HEIGHT);
    //Astar("./Bitmaps/test.bmp", WIDTH, HEIGHT);
    
    return 1;
}

void generateTestMap(){
    cout << "Starting export of bitmap\n";
    bitmap_image testMap(WIDTH, HEIGHT);

    for(int i = 0; i < WIDTH * HEIGHT; ++i){
        testMap.set_pixel(i % WIDTH, i / WIDTH, 255, 255, 255);
    }
    
    testMap.set_pixel(WIDTH / 2, HEIGHT / 2, 0, 255, 0);
    testMap.set_pixel(WIDTH - 400, HEIGHT / 2 + 400, 255, 0, 0);

    /*
    for(int i = HEIGHT/4; i < 3 * HEIGHT / 4; ++i){
        testMap.set_pixel(3 * WIDTH / 4, i, 0, 0, 0);
    }
    */

    testMap.save_image("./Bitmaps/test.bmp");
    return;
}