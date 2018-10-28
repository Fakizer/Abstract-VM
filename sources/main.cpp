
#include "AbstractVM.hpp"

void    file_input(int argc, char const *argv[]) {
    std::string buff;
    std::ifstream file;

    for (int i = 1; i < argc; i++) {
        file.open(argv[i], std::ios_base::in);
        while (getline(file, buff)) {
            std::cout << buff << std::endl;
        }
    }
    file.close();
}

void    terminal_input() {
    std::string buff;

    for (;;) {

        std::cin >> buff;
        std::cout << buff << std::endl;
        if (buff == ";;")
            break;
    }
}

int     main(int argc, char const *argv[])
{
    if (argc == 1)
        terminal_input();
    else
        file_input(argc, argv);
    return 0;
}
