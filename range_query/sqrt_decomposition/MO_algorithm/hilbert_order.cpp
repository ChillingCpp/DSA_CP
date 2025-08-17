ll hilbert_order(int x, int y, int pow)
{
    ll  res = 0;
    int rot = 0;

    for (int p = pow; p > 0; --p)
    {
        int hp  = 1 << (p - 1);
        int seg = (x < hp ? 1 : 0) ^ (y < hp ? 1 : 2);

        static const int rotateDelta[4] = { 3, 0, 0, 1 };

        rot = (rot + rotateDelta[seg]) & 3;

        int nx = x & (hp - 1), ny = y & (hp - 1);
        res += seg * (1ll << (2 * p - 2));
        switch (seg)
        {
            case 0:
                x = ny;
                y = nx;
                break;
            case 3:
                x = hp - ny - 1;
                y = hp - nx - 1;
                break;
            default:
                x = nx;
                y = ny;
                break;
        }
    }
    return res;
}