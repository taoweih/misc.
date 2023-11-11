#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <ctime>
#include <climits>

int LSI_recursion(std::vector<int>& array);
int LSI_recursion_helper(std::vector<int>& array, int i, int j);
int LSI_dynamic(std::vector<int>& array);

int main(){
    std::vector<int> array;
    array.resize(100);

    std::srand(unsigned(std::time(nullptr)));
    std::generate(array.begin(), array.end(), std::rand);
    for (int& num: array){
        num = num % 100;
    }

    auto start{std::chrono::steady_clock::now()};
    auto end{std::chrono::steady_clock::now()};
    start = std::chrono::steady_clock::now();
    int result_recursion = LSI_recursion(array);
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time{end -start};
    std::cout << "LSI recursion time: " << time.count() << "s\n";
   

    auto start2{std::chrono::steady_clock::now()};
    auto end2{std::chrono::steady_clock::now()};
    start2 = std::chrono::steady_clock::now();
        int result_dynamic = LSI_dynamic(array);
    end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time2{end2 -start2};
    std::cout << "LSI dynamic time: " << time2.count() << "s\n";

    if (result_recursion != result_dynamic){
        std::cout << "something went wrong" << std::endl;
    }

    return 0;
}

int LSI_dynamic(std::vector<int>& array){
    int n = array.size();
    array.insert(array.begin(),INT_MIN);

    std::vector<int> look_up_table(n*n);

    for (int i = 0; i < n; i++){
        look_up_table[i * n + n] = 0;
    }

    for (int j = n; j > 0; j--){
        for (int i = 0; i < j; i++){
            int keep_curr = 1 + look_up_table[j * n + j + 1];
            int skip_curr = look_up_table[i * n + j + 1];
            if (array[i] >= array[j]) {
                look_up_table[i * n + j] = skip_curr;
            } else {
                look_up_table[i * n + j] = std::max(keep_curr, skip_curr);
            }
        }
    }

    array.erase(array.begin());
    return look_up_table[1];
}

int LSI_recursion(std::vector<int>& array){
    array.insert(array.begin(),INT_MIN);
    int result = LSI_recursion_helper(array, 0, 1);
    array.erase(array.begin());
    return result;
}

int LSI_recursion_helper(std::vector<int>& array, int i, int j){
    if (i >= array.size() || j >= array.size()){
        return 0;
    }else if (array[i] >= array[j]){
        return LSI_recursion_helper(array, i , j+1);
    }else{
        return std::max(LSI_recursion_helper(array,i, j+1), 1+LSI_recursion_helper(array,j, j+1));
    }
}
