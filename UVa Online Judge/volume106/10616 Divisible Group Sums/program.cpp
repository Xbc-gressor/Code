// Divisible Group Sums
// UVa ID: 10616
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, q;
    int d, m;
    int number[128], mod[128];
    long long group[128][16][32];
    int cases = 0;

    while (cin >> n >> q, n > 0)
    {
        cout << "SET " << ++cases << ":\n";
        
        for (int i = 1; i <= n; i++)
            cin >> number[i];
        
        for (int i = 1; i <= q; i++)
        {
            cout << "QUERY " << i << ": ";

            cin >> d >> m;
            for (int j = 1; j <= n; j++)
                mod[j] = ((number[j] % d) + d) % d;
            
            if (m > n) m = n;
            memset(group, 0, sizeof(group));
            group[0][0][0] = 1;
            for (int x = 1; x <= n; x++)
                for (int y = 1; y <= x; y++)
                    for (int z = 0; z < d; z++)
                        group[x][y][(z + mod[x]) % d] += group[x - 1][y - 1][z];

            cout << group[n][m][0] << '\n';
        }
    }
    
    return 0;
}
