

/// this is mean we can process each bit one by one from MSB downto LSB
/// constraint : if bit can be solved indenpendently for all n integers
/// time complexity : O(30 * n)
/// if we not use bit contribution then time complexity is O(n^2) or more

const int bitsize = 30; /// for 1e9
const int n = 1e5;
vector<vector<int>> a(30, vector<int>(n));

for (int bit = bitsize; bit >= 0; --bit)
{
    /// do something in here, calculate
    for (int i = 0; i < n; ++i)
    {
        
    }
}
