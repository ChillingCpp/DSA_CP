struct Segment
{
    Point a, b;

    Segment() = default;
    Segment(Point& a, Point& b)
    : a(a)
    , b(b)
    {
    }

    bool contain(Point& c)
    {
        Vector ab(a, b);
        Vector ac(a, c);
        Vector ca(c, a);
        Vector cb(c, b);
        return ab.cross(ac) == 0 && ca.dot(cb) <= 0;
    }
    bool intersect(Segment& c)
    {
        Vector ab(a, b);
        Vector ac(a, c.a);
        Vector ad(a, c.b);
        Vector cd(c.a, c.b);
        Vector ca(c.a, a);
        Vector cb(c.a, b);


        ll abac = ab.cross(ac);
        ll abad = ab.cross(ad);
        ll cdca = cd.cross(ca);
        ll cdcb = cd.cross(cb);
        if (abac == 0 || abad == 0 || cdca == 0 || cdcb == 0)
        {
            if (contain(c.a) || contain(c.b) || c.contain(a) || c.contain(b))
                return true;
            return false;
        }
        return (abac * abad < 0 && cdca * cdcb < 0);
    }
};
