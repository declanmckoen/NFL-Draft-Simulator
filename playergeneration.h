#include <iostream>
#include <fstream>
#include "player.h"
#pragma once
using namespace std;


class PlayerGenerator {
    ifstream firstNamesFile;
    ifstream lastNamesFile;

    vector<string> firstNames;
    vector<string> lastNames;

public:
    PlayerGenerator();
    PlayerGenerator(string fNamesFile, string lNamesFile);

    string GenerateRandomName();
    int GenerateAge();
    int GenerateGamesPlayed();
    float GenerateHeight();
    float GenerateWeight();

    QuarterBack GenerateQB();
    RunningBack GenerateRB();
    WideReceiver GenerateWR();
    TideEnd GenerateTE();
    OffensiveLine GenerateOL();
    DefensiveLine GenerateDL();
    LineBacker GenerateLB();
    DefensiveBack GenerateDB();
};
