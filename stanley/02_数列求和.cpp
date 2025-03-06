//
//  02_数列求和.cpp
//  Quiz
//
//  Created by 赵禹惟 on 2025/3/5.
//

#include <iostream>

#define ERROR -1

using namespace std;

int fibonacci(int n) {
    if(n <= 0)
        return ERROR;
    if(n == 1)
        return 1;
    if(n == 2)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int MaxItems(int n) {
    int ans = 0;
    double sum = 0.0;
    
    int index = 1;
    while(true) {
        int fenzi = fibonacci(2 * index - 1); // 奇数位
        int fenmu = fibonacci(2 * index);     // 偶数位
        
        double item = (double) fenzi / fenmu;
        
        if(sum + item > n)
            break;
        sum += item;
        ans++;
        
        index++;
    }
    
    return ans;
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("Item: %d\n", MaxItems(n));
    return 0;
}
