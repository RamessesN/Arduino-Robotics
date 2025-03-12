//
//  05_格雷码.cpp
//  05_格雷码
//
//  Created by 赵禹惟 on 2025/3/12.
//

#include <iostream>
#include <cstring>

using namespace std;

void decimal2Binary(int n, int k, int binary_arr[]) {
    for(int i = n-1; i >= 0; i--) {
        binary_arr[i] = k % 2;
        k /= 2;
    }
}

void binary2Gray(int n, int binary_arr[], int gray_arr[]) {
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            gray_arr[i] = binary_arr[i];
        } else {
            if(binary_arr[i] == binary_arr[i-1]) {
                gray_arr[i] = 0;
            } else {
                gray_arr[i] = 1;
            }
        }
    }
}

void printGray(int n, int gray_arr[]) {
    for(int i = 0; i <= n-1; i++)
        printf("%d", gray_arr[i]);
    printf("\n");
}

int main(void) {
    int n, k;
    scanf("%d%d", &n, &k);
    
    int binary_arr[20] = {0};
    int gray_arr[20] = {0};
    
    decimal2Binary(n, k, binary_arr);
    binary2Gray(n, binary_arr, gray_arr);
    printGray(n, gray_arr);
    
    return 0;
}
