struct arc
{
    int u, v, capacity, residual, next;
};

class edmondsKarp
{
private:
    arc *arcs;
    int vertices, indexer, source, sink, *head, *path, *visited;

public:
    edmondsKarp(int v, int e, int s, int t)
    {
        vertices = v, indexer = 0, source = s, sink = t;
        head = new int[v], path = new int[v], visited = new int[v];
        arcs = new arc[e];
        for (int i = 0; i < v; i++) head[i] = -1;
    }

    ~edmondsKarp()
    {
        delete [] head, path, visited, arcs;
    }
    
    int maxFlow()
    {
        int netFlow = 0;

        while (true)
        {
            // 使用广度优先遍历寻找从源点到汇点的增广路。
            for (int i = 0; i < vertices; i++) visited[i] = 0, path[i] = -1;

            queue<int> unvisited;
            unvisited.push(source);
            visited[source] = 1;

            while (!unvisited.empty())
            {
                int u = unvisited.front();
                unvisited.pop();

                // 遍历以当前顶点为起点的有向弧，沿着残留容量为正的弧进行图遍历。
                for (int x = head[u]; x != -1; x = arcs[x].next)
                    if (!visited[arcs[x].v] && arcs[x].residual > 0)
                    {
                        unvisited.push(arcs[x].v);
                        visited[arcs[x].v] = 1;

                        // 注意路径记录的是有向弧的编号。
                        path[arcs[x].v] = x;
                    }
            }

            // 遍历未能到达汇点，表明不存在增广路，当前可行流已经为最大流。
            if (!visited[sink]) break;

            // 确定增广路的流量。
            int minFlow = 10000000;
            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
                minFlow = min(minFlow, arcs[x].residual);

            // 更新可行流的流量及残留网络。
            netFlow += minFlow;

            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
            {
                arcs[x].residual -= minFlow;
                arcs[x ^ 1].residual += minFlow;
            }
        }

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[indexer] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = indexer++;

        arcs[indexer] = (arc){v, u, capacity, 0, head[v]};
        head[v] = indexer++;
    }
};
