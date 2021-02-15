#include "NetworkInterfaces.h"
#include <getopt.h>
#include <iostream>

int main(int argc, char *argv[]) {
    char *ivalue = nullptr;
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

    if (ivalue == nullptr) {
        std::cout << "Interfaces get by getInterfaces():" << std::endl;
        for (auto& interface : interfaces) {
            std::cout << "Interface: " << interface.first << std::endl;
            int i = 1;
            for (auto&& ipAddress : interface.second) {
                std::cout << "\t IP Address " << i << ": " << ipAddress << std::endl;
                ++i;
            }
        }
        std::cout << std::endl << "----------------------------" << std::endl;
        std::cout << "Now interface printed from NetworkInterfaces (Class)" << std::endl;
        ni.print();
    } else {
        std::string interfaceName{ivalue};
        auto ipAddress = ni.getFirstIPAddressOfInterface(interfaceName);

        if (!ipAddress.has_value()) {
            std::cout << "No Interfaces found for " << ivalue << std::endl;
            return 0;
        }

        std::cout << "IP Address of " << interfaceName << " get by getFirstIPAddressOfInterface(" << interfaceName
                  << "): " << ipAddress.value() << std::endl;
        std::cout << std::endl << "----------------------------" << std::endl;
        std::cout << "Now ip address printed from NetworkInterfaces (Class)" << std::endl;
        ni.print(interfaceName);
    }

    return 0;
}
