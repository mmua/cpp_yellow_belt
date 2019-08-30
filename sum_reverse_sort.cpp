//
// Created by Мороз Максим on 2019-08-30.
//

#include "sum_reverse_sort.h"

#include <algorithm>

int Sum(int x, int y)
{
    return x + y;
}

string Reverse(string s)
{
    reverse(begin(s), end(s));
    return move(s);
}

void Sort(vector<int>& nums)
{
    sort(begin(nums), end(nums));
}
