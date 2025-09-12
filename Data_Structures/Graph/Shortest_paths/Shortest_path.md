
shortest path some important note :

- in directed graph, call d(u, v) is shortest path from u to v when we call dijkstra(u) or spfa(u).
call d'(v, u) is shortest path from v to u in reverse graph ( a graph where each edge have opposite direction to the original graph )

then d(u, v) = d'(v, u)

- multisource shortest path bfs or dijkstra when not reset the d(u, v) after call dijkstra will result adding d(srcs, v) to d(u, v), which mean d(u, srcs) + d(srcs, v) where srcs is sources list.

