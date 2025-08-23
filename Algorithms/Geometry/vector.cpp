
struct Point
{
    ll x, y;
};
struct Vector
{
    ll x, y;
    Vector() = default;
    Vector(Point& a, Point& b) : x(b.x - a.x), y(b.y - a.y) {} // construct vector ab

    ll dot(Vector& b)
    {
        return x * b.x + y * b.y;
    }
    ll cross(Vector& b)
    {
        return x * b.y - y * b.x;
    }
};

bool isCW(Point& a, Point& b, Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) < 0;
}
bool isCCW(Point& a, Point& b, Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) > 0;
}
bool isCollinear(Point& a, Point& b, Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) == 0;
}

