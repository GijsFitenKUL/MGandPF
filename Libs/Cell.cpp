class Cell{
    double dist= __DBL_MAX__;
    int parent;
    bool wall = false;
    bool visited = false;

    public:
        Cell(){}

        void setWall(){wall = true;}
        bool isWall(){return wall;}

        void visit(){visited = true;}
        bool isVisited(){return visited;}

        void setDist(double newDist){
            dist = newDist;
        }

        
        double getDist(){
            if(wall){return __DBL_MAX__;}
            return dist;
        }

        

        void setParent(int parentPos){
            parent = parentPos;
        }

        int getParent(){return parent;}
};