#include "mouse.hpp"

#include <iostream>
using namespace std;

ostream& operator<<(ostream &out, Vec2 pos)
{
    out << "Vec2 (" << pos.x << ", " << pos.y << ")";
    return out;
}

int main(void)
{
    Mouse mouse;

    cout << mouse.getPosition() << endl;

    return 0;
}
