#include <iostream>
#include "Stack.h"
#include <random>

int main()
{
    while (true) {

        Stack<int> q;

        for (int i = 0; i < 10000; i++) {
            q.push(rand() % 10);
        }

        while (!q.isEmpty()) {
            q.pop();
        }
        std::cout << std::endl;
    }

    return 0;
}
