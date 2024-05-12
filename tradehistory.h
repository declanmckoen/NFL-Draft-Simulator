#include <vector>
#include <string>
#include <unordered_map>
#pragma once
using namespace std;


class TradeHistory {
    int roundNumber;
    unordered_map<string, vector<pair<string, string>>> tradeHistory;

public:
    TradeHistory();
    TradeHistory(int roundNumber);
    void SetRoundNumber(int roundNumber);
    bool AddTrade(string team1, string team2, string details);
    vector<string> GetTradesNoDetails(string team);
    vector<pair<string, string>> GetTradesWithDetails(string team);
    bool TradeBetween(string team1, string team2);
};
