#include <bits/stdc++.h>


int find_quantile(std::vector<float> cdf, float quantile){
    int n = cdf.size();
    for(int i = 0; i < n; i++){
        if(cdf[i] >= quantile){
            return i;
        }
    }
    return n;
}
int main(){

    //finds quantile given a cdf
    std::vector<float> cdf = {1, 4, 8, 11, 20, 27, 30, 39, 54, 64, 67, 76, 91, 112, 125, 128, 137, 152, 173, 200, 216};
    float normalized = cdf.back();
    float quantile = 0.25;

    std::cout << find_quantile(cdf, quantile * normalized) << std::endl;
    return 0;

}
