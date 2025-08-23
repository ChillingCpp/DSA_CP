struct Circle
{
    ll    radius;
    Point p;
    Circle() = default;
    Circle(ll r, const Point& p)
    : radius(r)
    , p(p)
    {
    }
    bool contain(const Point& b)
    {
        Vector pb(p, b);
        return hypot(pb.x, pb.y) <= radius;
    }
    bool intersect(const Segment& b)
    {

    }
    bool intersect(const Line& b)
    {
        
    }
};
