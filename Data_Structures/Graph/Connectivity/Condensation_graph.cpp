// we decompose a graph with cycles to a condensation graph
// A condensation graph is a Directed acyclic graph connect strongly connected componenents, which mean its a graph which Sccs are the vertices.
// condensation graph useful when we are dealing some representative value of a scc (mincost/maxcost travel)
// combine condensation graph with topo sort and dp to achive solution in O(N + M) ( topo sort is a dp technique )

// first get all sccs then connect sccs together, using tarjan algorithm
