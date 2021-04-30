class AstarCell{
    public:
    
    double dist;
    int parent;
    int pos;

    int goal;
    int WIDTH;

    bool wall = false;
    bool visited = false;

    AstarCell(){}

    void setWall(){wall = true;}
    bool isWall(){return wall;}

    void visit(){visited = true;}
    void unvisit(){visited = false;}
    bool isVisited(){return visited;}

    void setDist(double newDist){
        dist = newDist;
    }
    
    double getDist(){
        if(wall){return __DBL_MAX__;}
        else{return dist;}
    }

    void setPos(int position){
        pos = position;
    }

    int getPos(){return pos;}

    void setParent(int parentPos){
        parent = parentPos;
    }

    int getParent(){return parent;}

    void setGoal(int newgoal){goal = newgoal;}
    void setWidth(int newWidth){WIDTH = newWidth;}

    bool operator <(const AstarCell c2) const
    {
        return abs(goal % WIDTH - pos % WIDTH) + abs(goal / WIDTH - pos / WIDTH) >= abs(goal % WIDTH - c2.pos % WIDTH) + abs(goal / WIDTH - c2.pos / WIDTH);
    }
};