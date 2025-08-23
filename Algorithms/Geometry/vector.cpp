struct Point
{
    ll x, y;
};
struct Vector
{
    ll x, y;
    Vector() = default;
    Vector(ll x, ll y)
    : x(x)
    , y(y)
    {
    }
    Vector(Point& a, Point& b)
    : x(b.x - a.x)
    , y(b.y - a.y)
    {
    }  // construct vector ab

    ll dot(Vector b)
    {
        return x * b.x + y * b.y;
    }
    ll cross(Vector b)
    {
        return x * b.y - y * b.x;
    }
    Vector& operator+=(Vector& b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }
    Vector operator+(Vector& b)
    {
        return { x + b.x, y + b.y };
    }
    Vector& operator-=(Vector& b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    Vector operator-(Vector& b)
    {
        return { x - b.x, y - b.y };
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
