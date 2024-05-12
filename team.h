#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <random>
#include "player.h"
#pragma once
using namespace std;


class Team {
public:
    vector<float> currentStates;

    const int rosterLimit = 53;
    int rosterSize;
    int numDraftPicks;

    double teamValue;
    bool onTheClock;

    string name;
    string city;

    vector<Player*> qbs;
    vector<Player*> rbs;
    vector<Player*> wrs;
    vector<Player*> tes;
    vector<Player*> ol;
    vector<Player*> dl;
    vector<Player*> lbs;
    vector<Player*> dbs;
    vector<pair<double, string>> rosterNeeds;
    vector<Player*> currentDraftedPlayers;
    vector<int> draftPicks;
    string draftGrade;

    Team();
    Team(string name, string city);
    Team& operator=(const Team& other);
    ~Team();

    void SetName(string& newName);
    bool AddPlayer(Player* player);
    bool CutPlayer(string playerName);
    bool RandomlyCutPlayer();
    void CalculateRosterNeeds();
    void PrintRosterNeeds();
    void PrintRoster();
    string CalculateDraftGrade();
    double CalculateTeamValue();
    void SortPositions();
    void PrintTeam();
    bool PlayerExists(string& player);
    void PrintPlayer(string& player);

    // During the draft
    void ToggleOnTheClock();
    string ChooseDraftOrTrade();
    string SelectPosition();
    void Trade();
    void DisplayRosterNeeds();
    void AddToDraftPlayers(Player* player);
    void DisplayCurrentlyDraftedPlayers();


    bool operator>(const Team& other) const;
    bool operator<(const Team& other) const;
    bool operator>=(const Team& other) const;
    bool operator<=(const Team& other) const;
    bool operator==(const Team& other) const;
    bool operator!=(const Team& other) const;

    bool PlayerPlayerTrade(vector<Player*> out, vector<Player*> in);
    bool PlayerPickTrade(vector<Player*> out, vector<int> in);
    bool PickPlayerTrade(vector<int> out, vector<Player*> in);
    bool PickPickTrade(vector<int> out, vector<int> in);
};
