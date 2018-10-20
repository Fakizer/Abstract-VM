
#include "abstractVM.hpp"

void    file_input(int argc, char const *argv[]) {
    std::string buff;
    std::ifstream file;

    for (int i = 1; i < argc; i++) {
        file.open(argv[i], std::ios_base::in);
        while (getline(file, buff)) {
            std::cout << buff << std::endl;
        }
    }
}

void    terminal_input() {

}

int     main(int argc, char const *argv[])
{
    if (argc == 1)
        terminal_input();
    else
        file_input(argc, argv);
    return 0;
}
