#include "Config.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>

Config* Config::selfInstance = nullptr;

Config::Config() {
    fileAccess = false;
    correctlyLoaded = false;

    //LVL MAP
    for(int lvl = 1; lvl <= 40; lvl++) lvlXpTable.push_back((int) (500*(pow(1.11,lvl-1)-1)));
    lvlXpTable.resize(lvlXpTable.size());

    //Config Map
    config.emplace("sizeTile", 32);
    config.emplace("sizeXInTiles", 60);
    config.emplace("sizeYInTiles", 40);
    config.emplace("minIdCollision", 4);
    //Config Entity
    config.emplace("entityVelocity", 1);
    config.emplace("frameEntityExecuter", 12);
    config.emplace("entityRange", 64);
    config.emplace("sizeHeadText", 16);
    config.emplace("colorRHeadText", 60);
    config.emplace("colorGHeadText", 60);
    config.emplace("colorBHeadText", 60);
    config.emplace("colorAHeadText", (int)0.85 * 255);
    //Config Player
    config.emplace("velocity", 2);
    //settings.emplace("","");

    //-----------------

    if(fileAccess) {
        std::ifstream configFileIn("app.ini");
        if (configFileIn.is_open()) {
            correctlyLoaded = true;
            auto whiteSign = [](unsigned char sign) { return (sign == ' ' || sign == '\t'); };
            std::string line;
            while (getline(configFileIn, line)) {
                line.erase(std::remove_if(line.begin(), line.end(), whiteSign), line.end());
                if (line[0] == '#' || line.empty()) continue;
                size_t delimPos = line.find(':');
                std::string key = line.substr(0, delimPos);
                std::string value = line.substr(delimPos + 1);
                config[key] = std::stoi(value);
            }
        } else {
            std::ofstream configFileOut("app.ini");
            std::string defaultConfigFile[] = {
                    "#Map (tile: 32px)",
                    "sizeXInTiles:" + std::to_string(config.at("sizeXInTiles")),
                    "sizeYInTiles:" + std::to_string(config.at("sizeYInTiles")),
                    "minIdCollision:" + std::to_string(config.at("minIdCollision")),
                    "#Player",
                    "velocity:" + std::to_string(config.at("velocity"))
            };
            for (auto &line : defaultConfigFile)
                configFileOut << line << "\n";
            configFileOut.close();
        }
        configFileIn.close();
    }
}

Config::~Config() {
    std::map<std::string, int>().swap(config);
}

void Config::initConfig() {
    if(selfInstance == nullptr) selfInstance = new Config();
}

Config *Config::getInstance() {
    if(selfInstance == nullptr){
        std::cerr<<"ERROR: Config has not been initiated..."<<std::endl;
        exit(2);
    }
    return selfInstance;
}

void Config::destroyConfig() {
    if(selfInstance != nullptr) delete selfInstance;
    selfInstance = nullptr;
}

