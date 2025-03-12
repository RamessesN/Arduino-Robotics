//
//  04_穿越历史.cpp
//  04_穿越历史
//
//  Created by 赵禹惟 on 2025/3/12.
//

#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

bool isLeap(int year) {
    bool isLeap = false;
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        isLeap = true;
    return isLeap;
}

int getMonthDays(int year, int month) {
    int actual_days = 31;
    if(month == 2) {
        if(isLeap(year)) {
            actual_days = 29;
        } else {
            actual_days = 28;
        }
    }
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        actual_days = 30;
    }
    return actual_days;
}

int getTotalDays(int year, int month, int day) {
    int totalDays = 0;
    for(int i = 1; i < year; i++) {
        if(isLeap(i)) {
            totalDays += 366;
        } else {
            totalDays += 365;
        }
    }
    
    for(int i = 1; i < month; i++) {
        totalDays += getMonthDays(year, i);
    }
    
    totalDays += day;
    return totalDays;
}

Date getDate(int totalDays) {
    Date ans;
    ans.year = 1;
    
    while(true) {
        int days = 0;
        if(isLeap(ans.year)) {
            days = 366;
        } else {
            days = 365;
        }
        if(totalDays > days) {
            totalDays -= days;
            ans.year++;
        } else {
            break;
        }
    }
    
    ans.month = 1;
    while(true) {
        int days = getMonthDays(ans.year, ans.month);
        if(totalDays > days) {
            totalDays -= days;
            ans.month++;
        } else {
            break;
        }
    }
    
    ans.day = totalDays;
    return ans;
}

void timeTransport(string n, int m) {
    int year, month, day;
    sscanf(n.c_str(), "%d-%d-%d", &year, &month, &day);
    
    if(year <= 0 || month < 1 || month > 12 || day < 1 || day > getMonthDays(year, month))
        return;
    
    int totalDays = getTotalDays(year, month, day);
    totalDays -= m;
    
    if(totalDays <= 0)
        return;
    
    Date ans = getDate(totalDays);
    printf("%d/%d/%d\n", ans.year, ans.month, ans.day);
}

int main(void) {
    string n;
    int m;
    cin >> n >> m;
    timeTransport(n, m);
    
    return 0;
}
