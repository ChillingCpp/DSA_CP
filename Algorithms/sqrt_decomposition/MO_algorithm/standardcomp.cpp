
bool operator<(const pii& a, const pii& b)
{ 
      return a.first / S < b.first / S || (a.first / S == b.first / S && a.second < b.second);
}
