struct Edge {
    int start, end, w;
    Edge(int start, int end, int w) : start(start), end(end), w(w) {};
    
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};