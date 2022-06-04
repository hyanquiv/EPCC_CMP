#include <bits/stdc++.h>

void slow_print(const std::string &str)
{
    for (size_t i = 0; i != str.size(); ++i)
    {
        std::cout << str[i] << std::endl;
    }
}

int main()
{
    std::string exp;
    std::cout << "expresion: ";
    std::getline(std::cin, exp);
    slow_print(exp);
    return 0;
}