#include "NetworkInterfaces.h"
#include <getopt.h>
#include <iostream>

int main(int argc, char *argv[]) {
    char *ivalue = NULL;
    int c;

    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
            case 'i':
                ivalue = optarg;
                break;
            case '?':
                if (optopt == 'i') {
                    std::cerr << "Option '-" << optopt << "' requires an argument." << std::endl << std::flush;
                } else if (isprint(optopt)) {
                    std::cerr << "Unknown option '-" << optopt << "'." << std::endl << std::flush;
                } else { fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt); }
                return 1;
            default:
                break;
        }
    }

    NetworkInterfaces ni{};
    auto& interfaces = ni.getInterfaces();

    for (auto& interface : interfaces)
    {

    }

}
