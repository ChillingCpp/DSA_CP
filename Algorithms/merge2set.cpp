

set<int> a, b;

if (a.size() > b.size()) swap(a, b); // optimization
for (auto &x : b) a.insert(x);
