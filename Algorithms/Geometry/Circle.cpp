struct Circle
{
    double radius;
    Point  p;
    Circle() = default;
    Circle(double r, const Point& p)
    : radius(r)
    , p(p)
    {
    }
    Circle(const Point& a, const Point& b, const Point& c)
    {
        // consider abc is a triangle, b in the middles
        Point m1 = (a + b) / 2;
        Point m2 = (b + c) / 2;

        Line l1(a, b);
        Line l2(b, c);

        Line prep1 = l1.getprep(m1);
        Line prep2 = l2.getprep(m2);

        p = prep1.intersect(prep2);
        Vector ra(p, a);
        r = dist(ra.x, ra.y);
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
