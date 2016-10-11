#include <iostream>
#include "utils.h"


int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Enter the image path as argument." << endl;
    }
    auto image = load_color(argv[1]);
    display_and_block(image);

    return 0;
}