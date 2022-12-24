/// @file
/// @brief Файл с реализацией основного потока приложения

#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <vector>
#include "print_ip.h"

int main()
{
    try
    {
        std::cout << print_ip(char(-1)) << '\n';
        std::cout << print_ip(short(0)) << '\n';
        std::cout << print_ip(int(2130706433)) << '\n';
        std::cout << print_ip(long(8875824491850138409)) << '\n';

        std::cout << print_ip(std::string("192.168.0.1")) << '\n';
        std::cout << print_ip(std::vector<unsigned char>{172, 16, 254, 1}) << '\n';
        std::cout << print_ip(std::list<short>{216, 3, 128, 12}) << '\n';

        std::cout << print_ip(std::make_tuple(char(-1), short(0), char(1))) << '\n';
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
