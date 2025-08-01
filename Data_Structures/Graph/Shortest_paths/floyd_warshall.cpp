void floyd(vector<vector<int>>& a)
{
    int V = dist.size();
    for (int k = 0; k < V; k++) {

        for (int i = 0; i < V; i++) {

            for (int j = 0; j < V; j++) {

                /// dist[i][j] = 1e8 means there is no edge connect i to j
                if(dist[i][k] != 1e8 && dist[k][j] != 1e8)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
