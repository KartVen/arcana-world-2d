#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include "App.h"

int main(int argc, char* argv[]) {
    srand((unsigned int) time(nullptr));
    App* appInstance = App::getApp();
    appInstance->runningApp();
    App::destroyApp();
    appInstance = nullptr;
    return 0;
}
