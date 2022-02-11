#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <string_view>
#include <algorithm>

using namespace std;

struct Node {
    vector< pair<char, Node*> > edges;
    bool end = false;
    vector<int> ids;
};

void Delete(Node* root){
    for (int i = 0; i < root->edges.size(); ++i){
        Delete(root->edges[i].second);
    }
    delete root;
}

Node* FindNext(Node* root, char c){
    Node* next = nullptr;
    for (const auto& [edge_c, node] : root->edges){
        if(edge_c == c){
            next = node;
            break;
        }
    }
    return next;
}

Node* AddPattern(Node* root, const string& str, int ind){
    Node* current_node = root;
    for (char c : str){
        Node* next = FindNext(current_node, c);
        if(!next){
            next = new Node();
            current_node->edges.push_back({c, next});
        }
        current_node = next;
    }
    current_node->end = true; // flag that word ends here
    current_node->ids.push_back(ind); // what word ends here
    return current_node;
}

// not used here, inverse solution
int FindPattern(const string& text, Node* root){
    for (int i = 0; i < text.size(); ++i){
        Node* current_node = root;
        int offset = 0;
        bool mismatch_not_found = true;  
        while (mismatch_not_found && i + offset < text.size()){
            char c = text[i + offset];
            Node* next = FindNext(current_node, c);
            if (next) {
                current_node = next;
                if (current_node->end){
                    return i;
                }
                ++offset;
            } else {
                mismatch_not_found = false;
            }
        }
    }
    return -1;
}

Node* FindNode(const string& pattern, Node* root){
    Node* current_node = root;
    for (int i = 0; i < pattern.size(); ++i){
        Node* next = FindNext(current_node, pattern[i]);
        if (next) {
            current_node = next;
        } else {
            current_node = nullptr;
            break;
        }
    }
    return current_node;
}

void AddString(vector<string_view>& sw, Node* node, const vector<string>& base){
    if (node->end){
        for(int id : node->ids){
            sw.push_back(base[id]);
        }
    }
    for (const auto& [c, v] : node->edges){
        AddString(sw, v, base);
    }
}

int main()
{
    string s;
    getline(cin, s);
    int n = stoi(s); // number of words in CamelCase
    vector<string> words(n);
    Node* root = new Node();
    for(int i = 0; i < n; ++i){
        getline(cin, words[i]);
        string caps;
        for(char c : words[i]){
            if ( (c >= 'A') && (c <= 'Z') ){
                caps.push_back(c);
            }
        }
        AddPattern(root, caps, i);
    }
    
    getline(cin, s);
    int m = stoi(s); // number of queries
    for(int i = 0; i < m; ++i){
        getline(cin, s);
        Node* node = FindNode(s, root);
        vector<string_view> ans;
        if (node) {
            AddString(ans, node, words);
            sort(ans.begin(), ans.end()); // if needed
            for (const auto& str : ans){
                cout << str << '\n';
            }
        } else {
            cout << '\n'; // or something like "No results"
        }
    }
    
    Delete(root); // if no garbage collectors
    return 0;
}
