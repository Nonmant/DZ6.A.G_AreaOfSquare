//https://contest.yandex.ru/contest/27844/problems/G/

#include "funcs.h"
#include <bits/stdc++.h>

//! @brief Index of last true. If everything is false return 0
template<typename F1, typename F2>
unsigned long long binSearchLowerBound(F1 valueGenerate,
                           F2 valueCheck,
                                       unsigned long long left, unsigned long long right){
    while (left<right){
        unsigned long long cur = (left + right + 1)/2;
        auto value = valueGenerate(cur);
        if(valueCheck(value)){
            left = cur;
        } else {
            right = cur-1;
        }
    }
    return right;
}

unsigned long long roadArea(
        unsigned long long n,
        unsigned long long m,
        unsigned long long squareArea,
        unsigned long long d
        ){
    unsigned long long centralM = 2*d>=m ? 0 : m-2*d;
    unsigned long long centralN = 2*d>=n ? 0 : n-2*d;
    auto centralArea = centralM*centralN;
    auto roadArea = squareArea - centralArea;
    return roadArea;
}

void parseFile(std::istream & input, std::ostream & output){

    unsigned long long n, m, t;
    input >> n >> m >> t;

    unsigned long long squareArea = n*m;

    unsigned long long left = 0, right = std::min(n,m)/2;
    auto d = binSearchLowerBound(
            [](unsigned long long d){return d;},
                [&n, &m, &squareArea, &t](unsigned long long d){
                    return roadArea(n,m,squareArea,d) <= t;
                },
                    left, right);
    output << d;
}
