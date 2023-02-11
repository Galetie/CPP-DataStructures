#include <iostream>
#include "LinkedList.h"

int main()
{
    LinkedList<int> list;
    
    list.insertEnd(500);
    for (int i = 0; i < 10; i++) {
        list.insertStart(i * 2);
    }
    list.insertEnd(800);
    list.remove(18);
    list.insertStart(99);

    std::cout << list.toString();

    return 0;
}
