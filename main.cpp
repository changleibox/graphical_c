#include <iostream>
#include "src/graphical.h"

int main() {
    const char *json = cornerPath(100, 100, 8, 8, 8, false);
    std::cout << json << endl;
    return 0;
}
