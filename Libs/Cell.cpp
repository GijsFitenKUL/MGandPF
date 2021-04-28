class Cell{
    double dist;
    int parent;
    int pos;

    bool wall = false;
    bool visited = false;

    public:
        Cell(){}

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

        bool operator <(const Cell c2) const
    {
        return dist >= c2.dist;
    }
};