struct Point
{
    double x, y;
    Point operator+(const Point& b)
    {
        return { x + b.x, y + b.y };
    }
    Point operator-(const Point& b)
    {
        return { x - b.x, y - b.y };
    }
    Point operator*(double k)
    {
        return { k * x, k * y };
    }
    Point operator/(double k)
    {
        return { x / k, x / k };
    }
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
    Vector operator*(double k)
    {
        return { k * x, k * y };
    }
    Vector operator/(double k)
    {
        return { x / k, x / k };
    }
};

// rotate, using point a as a center
Point rotate(const Point& a, const Point& b, double rad)
{
    Vector ab(a, b);
    Vector nab(ab.x * cos(rad) - ab.y * sin(rad), ab.x * sin(rad) + ab.y * cos(rad)); // multiply 2 matrices [x, y][cos, -sin sin, cos]
    return a + nab;
}
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
