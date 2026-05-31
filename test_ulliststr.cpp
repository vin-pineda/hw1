#include "ulliststr.h"
#include <iostream>
#include <string>

void print_list(const ULListStr& list) {
    std::cout << "list(size=" << list.size() << "): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list.get(i);
        if (i + 1 < list.size()) {
            std::cout << " -> ";
        }
    }
    std::cout << '\n';
}

int main(int argc, char* argv[]) {
    ULListStr list;
    std::cout << "empty? " << (list.empty() ? "true" : "false") << " size=" << list.size() << "\n";

    for (int i = 0; i < 10; i++) {
        list.push_back(std::to_string(i)); 
    }
    std::cout << "after push_back 0-9\n";
    print_list(list);
    std::cout << "front = " << list.front() << " back = " << list.back() << "\n";

    list.push_front("front");
    std::cout << "after push_front(\"front\")\n";
    print_list(list);

    list.pop_back();
    list.pop_front();
    std::cout << "after pop_back() and pop_front()\n";
    print_list(list);

    if (list.size() >= 2) {
        list.set(0, "zero");
        list.set(list.size() - 1, "nine");
        std::cout << "after set(0, \"zero\") and set(last, \"nine\")\n";
        print_list(list);
    }

    list.clear();
    std::cout << "after clear() empty? " << (list.empty() ? "true" : "false") << " size=" << list.size() << "\n";

    return 0;
}
