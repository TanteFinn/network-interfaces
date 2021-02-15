//
// Created by raimund on 15.02.21.
//

#ifndef NETWORK_INTERFACES_NETWORKINTERFACES_H
#define NETWORK_INTERFACES_NETWORKINTERFACES_H

#include <vector>
#include <string>
#include <stdexcept>
#include <optional>
#include <unordered_map>
#include <iostream>

class NetworkInterfaces {
private:
    static constexpr char msgNoInterfacesFound[]{ "No Interfaces found"};

    std::unordered_map<std::string, std::vector<std::string>> _interfaces;
    bool _init{false};

    void findInterfaces();

    static void print(const std::pair<std::string, std::vector<std::string>>& interface) ;
    static void printNoInterfacesFound();
public:
    NetworkInterfaces() = default;

    explicit NetworkInterfaces(std::unordered_map<std::string, std::vector<std::string>> networkInterfaces)
    // std::move map, because it was copied when calling ctor
            : _interfaces(std::move(networkInterfaces)) {}

    // return const reference to avoid copying vector of network interfaces
    // mark method as const, to be able to call it in any const context
    const std::unordered_map<std::string, std::vector<std::string>>& getInterfaces() const;

    // make non const method as well, to be able to initialize network interfaces (which will require to modify object)
    const std::unordered_map<std::string, std::vector<std::string>>& getInterfaces();

    // return NO reference, because new vector is created within method
    // but still const, because object will not get modified
    std::optional<std::vector<std::string>> getIPAddressesOfInterface(const std::string& interfaceName) const;
    std::optional<std::string> getFirstIPAddressOfInterface(const std::string& interfaceName) const;

    void print();
    void print(const std::string& interfaceName);
};

inline const std::unordered_map<std::string, std::vector<std::string>>& NetworkInterfaces::getInterfaces() const {
    if (!_init) {
        throw std::runtime_error("NetworkInterfaces not init, yet");
    }
    return _interfaces;
}

inline void NetworkInterfaces::printNoInterfacesFound()
{
    std::cout << "No Interfaces found." << std::endl;
}

#endif //NETWORK_INTERFACES_NETWORKINTERFACES_H
