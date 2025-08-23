struct Point
{
    double x, y;
};
struct Vector
{
    double x, y;
    Vector() = default;
    Vector(double x, double y)
    : x(x)
    , y(y)
    {
    }
    Vector(const Point& a, const Point& b)
    : x(b.x - a.x)
    , y(b.y - a.y)
    {
    }  // construct vector ab

    double dot(const Vector& b)
    {
        return x * b.x + y * b.y;
    }
    double cross(const Vector& b)
    {
        return x * b.y - y * b.x;
    }
    Vector operator+(const Vector& b)
    {
        return { x + b.x, y + b.y };
    }
    Vector operator-(const Vector& b)
    {
        return { x - b.x, y - b.y };
    }
    Vector operator*(ll k)
    {
        return { k * x, k * y };
    }
    Vector operator/(ll k)
    {
        return { x / k, x / k };
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
