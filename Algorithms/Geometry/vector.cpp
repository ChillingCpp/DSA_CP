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
    Vector(const Point& a, const Point& b)
    : x(b.x - a.x)
    , y(b.y - a.y)
    {
    }  // construct vector ab

    ll dot(const Vector& b)
    {
        return x * b.x + y * b.y;
    }
    ll cross(const Vector& b)
    {
        return x * b.y - y * b.x;
    }
    Vector& operator+=(const Vector& b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }
    Vector operator+(const Vector& b)
    {
        return { x + b.x, y + b.y };
    }
    Vector& operator-=(const Vector& b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    Vector operator-(const Vector& b)
    {
        return { x - b.x, y - b.y };
    }
};
bool isCW(const Point& a, const Point& b, const Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) < 0;
}
bool isCCW(const Point& a, const Point& b, const Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) > 0;
}
bool isCollinear(const Point& a, const Point& b, const Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) == 0;
}
