#include <iostream>
#include <experimental/filesystem>

using namespace std;


int main()
{
    namespace fs = std::experimental::filesystem; // In C++17 use std::filesystem.

    try {
        fs::create_directories("path/with/directories/that/might/not/exist");
    }
    catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
        std::cout << e.what() << std::endl;
    }

//     std::error_code ec;
//     bool success = fs::create_directories("path/with/directories/that/might/not/exist", ec);
// 
//     if (!success) {
//         std::cout << ec.message() << std::endl; // Fun fact: In case of success ec.message() returns "The operation completed successfully." using vc++.
//     }

    return 0;
}