
/// successive shortest path, first compute johnson algorithm to convert graph to positive weight, then apply dijkstra to compute flows, O(mn + F(m log n)) where F is max flows.