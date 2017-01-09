// Spreading the News
// UVa ID: 924
// Verdict: Accepted
// Submission Date: 2016-01-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

struct pack
{
    int index, day;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    vector<int> edges[2600];
    int visited[2600], boom[2600];

    int employees, friends, cases, index, source;

    while (cin >> employees)
    {
        for (int i = 0; i < employees; i++)
            edges[i].clear();
        
        for (int i = 0; i < employees; i++)
        {
            cin >> friends;
            for (int j = 1; j <= friends; j++)
            {
                cin >> index;
                edges[i].push_back(index);
            }
        }
        
        cin >> cases;
        for (int c = 1; c <= cases; c++)
        {
            cin >> source;
            
            memset(visited, 0, sizeof(visited));
            memset(boom, 0, sizeof(boom));
            
            queue<pack> unvisited;
            unvisited.push((pack){source, 0});
            visited[source] = 1;

            while (!unvisited.empty())
            {
                pack current = unvisited.front();
                unvisited.pop();

                boom[current.day]++;
                
                for (auto next : edges[current.index])
                    if (!visited[next])
                    {
                        visited[next] = 1;
                        unvisited.push((pack){next, current.day + 1});
                    }
            }
            
            int maximum = 0, first = 1;
            for (int i = 1; i <= employees; i++)
            {
                if (boom[i] > maximum)
                {
                    maximum = boom[i];
                    first = i;
                }
            }
            
            if (maximum == 0) cout << "0\n";
            else cout << maximum << ' ' << first << '\n';
        }
    }

    return 0;
}
