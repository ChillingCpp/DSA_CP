inline ll hilbert_order(int x, int y, int pow)
{
    ll  res = 0;
    int rot = 0;
    static const int rotdel[4] = { 3, 0, 0, 1 };

    for (int p = pow; p > 0; --p)
    {
        int hp  = 1 << (p - 1); // high to low
        
        int seg = (x < hp ? 1 : 0) ^ (y < hp ? 1 : 2);
        
        rot = (rot + rotdel[seg]) & 3;

        int nx = x & (hp - 1), ny = y & (hp - 1);
        
        res += seg * (1ll << (2 * p - 2));
        if (seg == 0)
             x = ny, y = nx;
        else  if (seg == 3)
             x = hp - ny - 1, y = hp - nx - 1;
        else 
             x = nx, y = ny;
    }
    return res;
}

