//
// Created by raimund on 15.02.21.
//

#include "NetworkInterfaces.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <iostream>
#include <algorithm>
#include <memory>

void NetworkInterfaces::findInterfaces() {
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    std::unique_ptr<std::exception> ex;
    getifaddrs(&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            try {
                _interfaces[ifa->ifa_name].emplace_back(addr);
            }
            catch (std::exception& e) {
                // break for loop here, if an error occurred, to free ifap and then rethrow error
                freeifaddrs(ifap);
                throw e;
            }
        }
    }

    freeifaddrs(ifap);
}

const std::unordered_map<std::string, std::vector<std::string>>& NetworkInterfaces::getInterfaces() {
    if (!_init) {
        // don't catch exception here, because it would only be redirected
        findInterfaces();
    }

    return _interfaces;
}

std::optional<std::vector<std::string>>
NetworkInterfaces::getIPAddressesOfInterface(const std::string& interfaceName) const {
    auto it = std::find_if(_interfaces.begin(), _interfaces.end(), [&](auto& interface) {
        return interface.first == interfaceName;
    });

    if (it != _interfaces.end()) {
        return it->second;
    }

    return {};
}

std::optional<std::string> NetworkInterfaces::getFirstIPAddressOfInterface(
        const std::string& interfaceName) const {
    auto ipAddresses = getIPAddressesOfInterface(interfaceName);

    if (!ipAddresses.has_value()) {
        return {};
    }

    try {
        return ipAddresses.value()[0];
    }
    catch (std::out_of_range& e) {
        return {};
    }

    // should never reach this point
    return {};
}

void NetworkInterfaces::print() {
    if (_interfaces.empty())
    {
        printNoInterfacesFound();
        return;
    }

    for (auto&& interface : _interfaces)
    {
        print(interface);
    }
}

void NetworkInterfaces::print(const std::string& interfaceName)
{
    auto it = std::find_if(_interfaces.begin(), _interfaces.end(), [&](auto& interface) {
        return interface.first == interfaceName;
    });

    if (it == _interfaces.end()) {
        printNoInterfacesFound();
        return;
    }

    print(*it);
}

void NetworkInterfaces::print(const std::pair<std::string, std::vector<std::string>>& interface)
{
    int i = 1;
    std::cout << "Interface: " << interface.first << std::endl;
    for (auto&& ipAddress : interface.second)
    {
        std::cout << "\t IP Address " << i << ": " << ipAddress << std::endl;
    }

    std::cout << std::flush;
}
