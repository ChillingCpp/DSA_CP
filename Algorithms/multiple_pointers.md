# Two pointers and its variant implementation

## Two pointers using 2 integer index $[L, R]$
## Two pointers using a queue
- pop the front element when its outside the interval or not validated anymore
## multiple pointers
- vector<int> ptr(n) : n pointers
  - ptr[i] represent the pointers of the ith element
- vector<queue<int>> q(n);
  - q[i] is the current interval when we process to the ith element
