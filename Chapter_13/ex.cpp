//
// Created by Dmytrenko Kyrylo on 07.03.2026.
//

#include "drill_ex.h"

namespace ch13::exercises {
    long long int fac_recursive(int n) {
        return n > 1 ? n*fac_recursive(n-1) : 1;
    }

    long long int fac_loop(int n) {
        long long int res = 1;

        for (int i = 1; i <=n; i++)
            res*= i <= 1 ? 1 : i;

        return res;
    }

    void ex_1() {
        const int n = 1;
        std::cout << fac_recursive(n) << endl;
        cout <<  fac_loop(n) << endl;
    }
}
