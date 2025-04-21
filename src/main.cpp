#include <iostream>
#include <print>
#include <string>
int main() {
    std::print("what is your name: ");
    std::string name;
    std::cin >> name;
    std::println("Hello, {}!", name);
}