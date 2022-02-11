#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{ 
   int n;
   cin >> n; // number of dinners
   vector<int> cost(n);
   vector<int> max_cupon(n);
   int cupon = 0;
   for(int i = 0; i < n; ++i){
       cin >> cost[i];
       max_cupon[i] = cupon;
       if(cost[i] > 500){ // earning a cupon after 500
           ++cupon;
       }
   }
   vector<int> dp(cupon+1);
   vector<int> dp_buf(cupon+1);
   vector<vector<int>> dp_cup(cupon+1);
   vector<vector<int>> dp_buf_cup(cupon+1);
   dp[0] = cost[n-1];
   for(int i = 1; i <= cupon; ++i){
       dp_cup[i].push_back(n-1);
   }
   for(int i = n-2; i >= 0; --i){ // reversing filling
       for(int j = 0; j <= max_cupon[i]; ++j){
           if(cost[i] > 500){
               if (j == 0){
                   dp_buf[j] = dp[j+1] + cost[i];
                   dp_buf_cup[j] = dp_cup[j+1];
               } else {
                   if(dp[j+1] + cost[i] < dp[j-1]){
                       dp_buf[j] = dp[j+1] + cost[i];
                       dp_buf_cup[j] = dp_cup[j+1];
                   } else {
                       dp_buf[j] = dp[j-1];
                       dp_buf_cup[j] = dp_cup[j-1];
                       dp_buf_cup[j].push_back(i);
                   }
               }
           } else {
               if (j == 0){
                   dp_buf[j] = dp[j] + cost[i];
                   dp_buf_cup[j] = dp_cup[j];
               } else {
                   if(dp[j] + cost[i] < dp[j-1]){
                       dp_buf[j] = dp[j] + cost[i];
                       dp_buf_cup[j] = dp_cup[j];
                   } else {
                       dp_buf[j] = dp[j-1];
                       dp_buf_cup[j] = dp_cup[j-1];
                       dp_buf_cup[j].push_back(i);
                   }
               }
           }
       }
       swap(dp, dp_buf);
       swap(dp_cup, dp_buf_cup);
   }
   cout << dp[0] << ' ' << dp_cup[0].size() << '\n';
   for(auto it = dp_cup[0].rbegin(); it != dp_cup[0].rend(); ++it){
       cout << *it+1 << ' '; // if needed аscending sort in output
   }
   return 0;
}
