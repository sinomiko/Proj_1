#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <windows.h>
std::vector<std::string> shift_right(std::vector<std::string>& picture,
    std::string::size_type n = 4)
{
    // all error/bounds-checking is omitted for brevity
    const std::string& first = picture[0];
    const std::string::size_type size = first.size();
    const char border = first[0];
    const std::string spaces(n, ' ');

    for (std::string::size_type i = 0; i < (picture.size() - 1); ++i)
        picture[i] = border + spaces + picture[i].substr(1, size - n - 2) + border;

    return picture;
}

void print(const std::vector<std::string>& picture)
{
    std::cout << '\n';
    for (const auto& line : picture) std::cout << line << '\n';
    std::cout << '\n';
}

int main()
{
    //http://patorjk.com/software/taag/#p=testall&f=Graffiti&t=miko
    /*
    std::vector<std::string> picture =
    {
        R"(#######################################################)",
        R"(#           _                                         #)",
        R"(#         -=\\`\\                                     #)",
        R"(#     |\\ ____\\_\\__                                 #)",
        R"(#   -=\\c`""""""" "`)                                 #)",
        R"(#      `~~~~~/ /~~`\                                  #)",
        R"(#        -==/ /                                       #)",
        R"(#                                                     #)",
        R"(#######################################################)"
    };
    */
    std::vector<std::string> picture =
    {

        R"(    _        ____    ____   U  ___ u   _   _   _   _     _____         ____ U _____ u _   _     _____  U _____ u   ____       )",
        R"(U  /"\  u U /"___|U /"___|   \/"_ \/U |"|u| | | \ |"|   |_ " _|     U /"___|\| ___"|/| \ |"|   |_ " _| \| ___"|/U |  _"\ u    )",
        R"( \/ _ \/  \| | u  \| | u     | | | | \| |\| |<|  \| |>    | |       \| | u   |  _|" <|  \| |>    | |    |  _|"   \| |_) |/    )",
        R"( / ___ \   | |/__  | |/__.-,_| |_| |  | |_| |U| |\  |u   /| |\       | |/__  | |___ U| |\  |u   /| |\   | |___    |  _ <      )",
        R"(/_/   \_\   \____|  \____|\_)-\___/  <<\___/  |_| \_|   u |_|U        \____| |_____| |_| \_|   u |_|U   |_____|   |_| \_\     )",
        R"( \\    >>  _// \\  _// \\      \\   (__) )(   ||   \\,-._// \\_      _// \\  <<   >> ||   \\,-._// \\_  <<   >>   //   \\_    )",
        R"((__)  (__)(__)(__)(__)(__)    (__)      (__)  (_")  (_/(__) (__)    (__)(__)(__) (__)(_")  (_/(__) (__)(__) (__) (__)  (__)   )",
        R"(                                                                                                                              )"
    };
       
    print(picture);                                                                                                                      

    for (int i = 0; i < 16; ++i)
    {
        Sleep(1000);
        print(shift_right(picture, 8));
    }
    return 0;
}