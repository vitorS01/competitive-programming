template<typename T>
struct Point {
    T x,y;
    Point() : x(0), y(0) {};
    Point(T X, T Y) : x(X), y(Y) {};
    Point operator + (Point a) const {
        return Point(x+a.x, y+a.y);
    }
    Point operator - (Point a) const {
        return Point(x-a.x, y-a.y);
    }
    bool operator < (Point a) const {
        if (a.x==x) return y < a.y;
        return x<a.x;
    }
    T operator % (Point a) const {
        return x*a.x + y*a.y;
    }
    bool operator == (Point a) const {
        return a.x==x&&a.y==y;
    }
    T operator * (Point a) const {
        return x*a.y - y*a.x;
    }
};
