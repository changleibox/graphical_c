#include "src/graphical.h"
#include "src/Incircle.h"

using namespace std;

int main() {
    cornerPath(100, 100, 8, 8, 8, false);
    Incircle_fromSize({80, 80}, 8, false);
    Incircle_fromRadians(1, 8);
    radians90();
    radians180();
    radians270();
    radians360();
    pi();
    return 0;
}
