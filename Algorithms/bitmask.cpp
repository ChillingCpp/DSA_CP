


// bitmask is used when n <= 20 ( or n <= 40 if use meet-in-the-middle)

for (int mask = 0; mask < (1 << n); ++mask)
{
    /// declare current solution
    for (int i = 0; i < n; ++i)
        if ((1 << i) & mask) /// include the  element in the  solution of the current mask

    /// verify and compute solution
}
/// output
