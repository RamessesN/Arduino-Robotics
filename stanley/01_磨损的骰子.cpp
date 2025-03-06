//
//  01_磨损的骰子.cpp
//  Quiz
//
//  Created by 赵禹惟 on 2025/3/5.
//

#include <iostream>

using namespace std;

int A[] = {1, 0, 3, 4, 5, 6};
int B[] = {1, 2, 3, 0, 5, 6};
int C[] = {1, 2, 3, 4, 0, 6};

int Total_Methods(int m) {
    int ans = 0;
    
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(A[i] + B[j] > m)
                continue;
            if(A[i] + B[j] + 6 < m)
                continue;
            for(int k = 0; k < 6; k++){
                int sum = A[i] + B[j] + C[k];
                if(sum == m)
                    ans++;
            }
        }
    }
    
    return ans;
}

int main(void) {
    int m;
    scanf("%d", &m);
    printf("Total: %d\n", Total_Methods(m));
    return 0;
}
