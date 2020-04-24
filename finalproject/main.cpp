#include <iostream>
#include <conio.h>
#include "accountControl.h"
#include "utility.h"
#include <algorithm>

using namespace std;

int main()
{
    tt::vector<float> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(0.15 - i);
    }

    tt::vector<float> vec2;

    vec2 = vec;

    for (int i = 0; i < vec2.size(); ++i)
        cout << vec2[i] << ' ';


    cout << '\n';
    sort(vec2.begin(), vec2.end());

    for (int i = 0; i < vec2.size(); ++i)
        cout << vec2[i] << ' ';

    return 0;
}

