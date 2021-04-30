// set colors with operator <<



#include <iostream>
#include <iomanip>
#include "example.h"

using namespace std;

int main() {
    SetColor(3);
    cout << "I'm in color!\n";

    cout << red << "red " << color(2) << "green " << blue << "blue!!" << endl;

    return 0;
}

