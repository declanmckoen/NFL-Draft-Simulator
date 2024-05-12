#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <chrono>
#include <thread>
#include "team.h"
#include "tradehistory.h"
#include "player.h"
#include "playergeneration.h"
#pragma once
using namespace std;


class Draft {
public:
    const int rounds = 7;
    const int numTeams = 32;
    const int draftPickTotal = 224;

    PlayerGenerator playerGenerator;

    map<string, Team> teams;
    vector<vector<string>> draftOrder;
    map<int, TradeHistory> tradeHistory;
    vector<Player*> prospects;

    vector<vector<string>> tradeRequests;


    Draft();
    ~Draft();

    bool PlayerPlayerTrade(int round, string team1, string team2, vector<Player*> team1ToTeam2, vector<Player*> team2ToTeam1);
    bool PlayerPickTrade(int round, string team1, string team2, vector<Player*> team1ToTeam2, vector<int> team2ToTeam1);
    bool PickPlayerTrade(int round, string team1, string team2, vector<int> team1ToTeam2, vector<Player*> team2ToTeam1);
    bool PickPickTrade(int round, string team1, string team2, vector<int> team1ToTeam2, vector<int> team2ToTeam1);

    void AddProspect(Player* player);
    void AddProspects();
    void AssignPlayers();
    void CalculateTeamNeeds();

    void DetermineDraftOrder();
    void PrintDraftOrder();
    void PrintTeams();
    bool TeamExists(string& team);
    void PrintTeam(string& team);
    bool PlayerExists(string& player);
    void PrintPlayer(string& player, string team = "");
    void PrintProspects(int number);
    void RandomlyCutPlayers();

    void StartDraft(int round, int pick, string mode = "");
    void AddTradeRequests();
    void ParseTradeRequests(string want);
};
