#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& out, const set<vector<int>>& s){
    for(const auto& v : s){
        for(int i : v){
            out << i << ' ';
        }
        out << '\n';
    }
    return out;
}

set<vector<int>> FindFourElements(const vector<int>& input, int n, int S)
{
    unordered_map<long, pair<int, int> > mp;
    set<vector<int>> result;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            mp[input[i] + input[j]] = { i, j };
            
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long sum = input[i] + input[j];
            if (mp.find(S - sum) != mp.end()) {
                pair<int, int> p = mp[S - sum];
                if (p.first != i && p.first != j
                    && p.second != i && p.second != j) {
                    vector<int> v = {input[i], input[j], input[p.first], input[p.second]};
                    sort(v.begin(), v.end());
                    result.insert(v);
                }
            }
        }
    }
    return result;
}

int main()
{
    int n, S;
    cin >> n >> S;
    vector<int> input(n);
    for(int i = 0; i < n; ++i){
        cin >> input[i];
    }
    sort(input.begin(), input.end());
    set<vector<int>> result = FindFourElements(input, n, S);
    cout << result.size() << '\n';
    cout << result << '\n';
    return 0;
}
