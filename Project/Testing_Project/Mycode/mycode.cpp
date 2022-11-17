// Include C++ headers
#include <iostream>
#include <string>

#include "functions.h"

using namespace std;


int main(void) {
    try {
        initialize();
        createContext();
        mainLoop();
        free();
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
        getchar();
        free();
        return -1;
    }

    return 0;
}