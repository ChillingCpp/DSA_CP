
    /// these below are binary search on segment tree, we need to remember 
    template<bool (*g)(Node)>
    int max_right(int l)
    {
        return max_right(l, [](Node x) { return g(x); });
    }
    template<class G>
    int max_right(int l, G g)
    {
        if (l == _n)
            return _n;
        l += size;
        /// push all child at index l
        push1(l);
        Node sm = id_node();
        
        // binary search, the left subtree is where answer is still valid
        do
        {
            while (l % 2 == 0)
                l >>= 1;
            if (!g(op(sm, d[l])))
            {
                while (l < size)
                {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) /// check if right subtree is valid then go to right, do op to currrent node sm
                    {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template<bool (*g)(Node)>
    int min_left(int r)
    {
        return min_left(r, [](Node x) { return g(x); });
    }
    template<class G>
    int min_left(int r, G g)
    {
        if (r == 0)
            return 0;
        r += size;
        for (int i = log; i >= 1; i--)
            push((r - 1) >> i);
        Node sm = id_node();
        do
        {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!g(op(d[r], sm)))
            {
                while (r < size)
                {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) /// same as above but change l to r
                    {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }


