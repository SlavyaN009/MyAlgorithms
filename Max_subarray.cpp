#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<char> v1(n);
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        v1[i] = num + '0';
    }
    int m;
    cin >> m;
    vector<char> v2(m);
    for(int i = 0; i < m; ++i){
        int num;
        cin >> num;
        v2[i] = num + '0';
    }
    //vector<vector<char>> table(n, vector<char>(m)); // too much memory
    unordered_map<int, unordered_map<int, int>> hash_map;
    int max_val = 0, max_ind = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if (v1[i] == v2[j]){
                hash_map[i][j] = (i == 0 || j == 0)
                    ? 1
                    : hash_map[i - 1][j - 1] + 1;
                if (hash_map[i][j] > max_val){
                    max_val = hash_map[i][j];
                    max_ind = i;
                }
            }
        }
    }
    cout << max_val;
    /*   print subarray
    for(int i = 0; i < max_val; ++i){
        cout << v1[max_ind + 1 - max_val + i] << ' ';
    }
    */
    return 0;
}
