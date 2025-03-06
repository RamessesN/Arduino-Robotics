//
//  main.cpp
//  03_"爱"的表白
//
//  Created by 赵禹惟 on 2025/3/5.
//

#include <iostream>
#include <cstring>

using namespace std;

int numOfLove(string s) {
    int counter = 0;
    for(int i = 0; i+3 <= s.length(); i++) {
        if(s[i] == 'l' && s[i + 1] == 'o' && s[i + 2] == 'v' && s[i + 3] == 'e')
            counter++;
    }
    return counter;
}

int main(void) {
    string s;
    cin >> s;
    
    int result = numOfLove(s);
    if(result > 0) {
        printf("%d\n", numOfLove(s));
    } else {
        printf("Failure\n");
    }
    
    return 0;
}
