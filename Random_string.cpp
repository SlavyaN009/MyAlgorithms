#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>

using namespace std;

unsigned long GetHash(const string& s, int m, int a){
    unsigned n = s.size();
    unsigned long hash = static_cast<int>(s[0]) % m;
    for(unsigned i = 1; i < n; ++i){
        hash = (hash * a + static_cast<int>(s[i])) % m;
    }
    return hash;
}

void Shuffle(string& s){
    int size = rand()%996 + 3;
    s.resize(size);
    for(unsigned i = 0; i < size; ++i){
        s[i] = char(rand()%25 + 'a');
    }
}

int main()
{
    int a = 1000, m = 123987123;
    unordered_map<unsigned long, string> table;
    string str = "aaa"s;
    unsigned long hash = GetHash(str, m, a);
    while(!table.count(hash)){
        table[hash] = str;
        Shuffle(str);
        hash = GetHash(str, m, a);
    }
    cout << str << '\n';
    cout << table.at(hash) << '\n';
    cout << hash << '\n';
    return 0;
}
