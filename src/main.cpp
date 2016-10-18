#include <iostream>
#include "utils.h"
#include "oai/image_view.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cerr << "Enter the image path as argument." << endl;
    }
    auto image = load_color(argv[1]);
    oai::ImageView view(image);
    view.display();

    return 0;
}