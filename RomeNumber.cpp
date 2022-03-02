#include <iostream>
#include <string>
#include <vector>

using namespace std;

int FindOnes(string& s, const vector<char>& simbols){
    int ind = s.size()-1;
    while (ind >=0 && (simbols[0] == s[ind] ||
                        simbols[1] == s[ind] ||
                        simbols[2] == s[ind])){
        --ind;
    }
    if (ind == s.size()-1) return 0;
    ++ind;
    while (ind < s.size() && s[ind] == simbols[2]){
        ++ind;
    }
    if (ind == s.size()) return 0;
    string num = s.substr(ind);
    s.resize(ind);
    vector<string> nums(10, ""s);
    for (int i = 1; i < 10; ++i){
        if (i < 4){
            nums[i] = nums[i-1] + simbols[0];
        } else if (i == 4) {
            nums[i] = nums[0] + simbols[0] + simbols[1];
        } else if (i == 5) {
            nums[i] = simbols[1];
        } else if (i < 9){
            nums[i] = nums[i-1] + simbols[0];
        } else if (i == 9){
            nums[i] = nums[0] + simbols[0] + simbols[2];
        }
    }
    for (int i = 1; i < 10; ++i){
        if (num == nums[i]) {
            return i;
        }
    }
    return -1;
}

int RomeNum(string& s){
    vector<char> simbols_1 = {'I','V','X'};
    vector<char> simbols_2 = {'X','L','C'};
    vector<char> simbols_3 = {'C','D','M'};
    vector<int> num(4);
    num[3] = FindOnes(s, simbols_1);
    num[2] = FindOnes(s, simbols_2);
    num[1] = FindOnes(s, simbols_3);
    if (s == ""s || s == "M"s || s == "MM"s || s == "MMM"s) {
        num[0] = s.size();
    } else return -1;
    int ans = 0;
    for (int i = 0; i < 4; ++i){
        if (num[i] == -1) return -1;
        ans = ans*10 + num[i];
    }
    return ans;
}

int main()
{
    string s;
    getline(cin, s);
    cout << RomeNum(s);
    return 0;
}
