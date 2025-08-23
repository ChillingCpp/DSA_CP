
struct Line  // ax + by = c
{
    double a, b, c;
    Line() = default;
    Line(double a, double b, double c)
    : a(a)
    , b(b)
    , c(c)
    {
    }
    Line(const Point& A, const Point& B)  // convert vector u(a, b) to vector n(b, -a)
    : a(B.y - A.y)
    , b(A.x - B.x)
    {
        c = a * A.x + b * A.y;
    }
    bool contain(const Point& p)
    {
        return a * p.x + b * p.y - c == 0;
    }
    Line getprep(const Point& p)
    {
        double na = b;
        double nb = -a;
        double nc = na * p.x + nb * p.y;
        return Line(na, nb, nc);
    }
}
