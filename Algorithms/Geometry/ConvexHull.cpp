// special cw implement, check even for collinear
bool isCW(const Point& a, const Point& b, const Point& c)
{
    Vector ab(a, b);
    Vector ac(a, c);
    return ab.cross(ac) <= 0;
}
struct ConvexHull
{
    vector<Point> h;
    ConvexHull() = default;
    ConvexHull(vector<Point>& p)
    {
        construct(p);
    }
    void construct(vector<Point>& p)
    {
        sort(p.begin(),
             p.end(),
             [&](const Point& a, const Point& b)
             { return a.x < b.x || (a.x == b.x && a.y < b.y); });
        int n = p.size();


        // build upper hull
        for (int i = 0; i < n; ++i)
        {
            while (h.size() >= 2 && isCW(h[h.size() - 2], h.back(), p[i]))
                h.pop_back();
            h.push_back(p[i]);
        }

        // build lower hull
        for (int i = n - 2; i >= 0; --i)
        {
            while (h.size() >= 2 && isCW(h[h.size() - 2], h.back(), p[i]))
                h.pop_back();
            h.push_back(p[i]);
        }
        h.pop_back();
    }
};
