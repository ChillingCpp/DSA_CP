struct Circle
{
    double    radius;
    Point p;
    Circle() = default;
    Circle(double r, const Point& p)
    : radius(r)
    , p(p)
    {
    }
    Circle(const Point& a, const Point& b, const Point& c)
    {
        Point m1 = { (a.x + b.x) / 2, (a.y + b.y) / 2 };
        Point m2 = { (c.x + b.x) / 2, (c.y + b.y) / 2 };
        
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
