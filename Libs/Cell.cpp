class Cell{
    public:
        int xpos;
        int ypos;
        int dist = __INT_MAX__;
        int parentx;
        int parenty;

    Cell(int xpos, int ypos)
    : xpos(xpos), ypos(ypos){}
};

bool operator<(const Cell& c1, const Cell& c2)
{
    return c1.dist > c2.dist;
}