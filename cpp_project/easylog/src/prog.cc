#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
 
int main(int, const char**) {
    LOG(ERROR) << "Hello, world";
    return 0;
}