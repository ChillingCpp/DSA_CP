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
    bool canintersect(const Line& ano)
    {
        return !(a == ano.a && b == ano.b);
    }
    Point intersect(const Line& ano)
    {
        // a1x + b1y = c1;
        // a2x + b2y = c2;

        // a1b2x  b1b2y = c1b2;
        // -a2b1x - b1b2y = -c2b1

        // -a1a2x - b1a2y = -c1a2;
        // a2a1x + b2a1y = c2a1

        // a2b1x - a1b2x = c2b1 - c1b2
        // b2a1y - b1a2y = c2a1 - c1a2

        // x = (c1b2 - c2b1) / (a1b2 - a2b1);
        // y = (c2a1 - c1a2) / (a1b2 - a2b1);

        double det = a * ano.b - ano.a * b;
        return { (c * ano.b - ano.c * b) / det, (ano.c * a - c * ano.a) / det };
    }
    Line getprep(const Point& p)
    {
        double na = b;
        double nb = -a;
        double nc = na * p.x + nb * p.y;
        return Line(na, nb, nc);
    }
}
