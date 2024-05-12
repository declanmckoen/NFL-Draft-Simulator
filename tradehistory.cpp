#include "tradehistory.h"
using namespace std;


TradeHistory::TradeHistory() {
    tradeHistory.reserve(32);
    vector<string> teams = {
            "Arizona Cardinals",
            "Atlanta Falcons",
            "Carolina Panthers",
            "Chicago Bears",
            "Dallas Cowboys",
            "Detroit Lions",
            "Green Bay Packers",
            "Los Angeles Rams",
            "Minnesota Vikings",
            "New Orleans Saints",
            "New York Giants",
            "Philadelphia Eagles",
            "San Francisco 49ers",
            "Seattle Seahawks",
            "Tampa Bay Buccaneers",
            "Washington Commanders",
            "Baltimore Ravens",
            "Buffalo Bills",
            "Cincinnati Bengals",
            "Cleveland Browns",
            "Denver Broncos",
            "Houston Texans",
            "Indianapolis Colts",
            "Jacksonville Jaguars",
            "Kansas City Chiefs",
            "Las Vegas Raiders",
            "Las Angeles Chargers",
            "Miami Dolphins",
            "New England Patriots",
            "New York Jets",
            "Pittsburgh Steelers",
            "Tennessee Titans"
    };
    vector<pair<string, string>> placeholder = {};
    for (int i = 0; i < 32; ++i) {
        tradeHistory.emplace(teams[i], placeholder);
    }
}

TradeHistory::TradeHistory(int round) {
    this->roundNumber = round;
    tradeHistory.reserve(32);
    vector<string> teams = {
            "Arizona Cardinals",
            "Atlanta Falcons",
            "Carolina Panthers",
            "Chicago Bears",
            "Dallas Cowboys",
            "Detroit Lions",
            "Green Bay Packers",
            "Los Angeles Rams",
            "Minnesota Vikings",
            "New Orleans Saints",
            "New York Giants",
            "Philadelphia Eagles",
            "San Francisco 49ers",
            "Seattle Seahawks",
            "Tampa Bay Buccaneers",
            "Washington Commanders",
            "Baltimore Ravens",
            "Buffalo Bills",
            "Cincinnati Bengals",
            "Cleveland Browns",
            "Denver Broncos",
            "Houston Texans",
            "Indianapolis Colts",
            "Jacksonville Jaguars",
            "Kansas City Chiefs",
            "Las Vegas Raiders",
            "Las Angeles Chargers",
            "Miami Dolphins",
            "New England Patriots",
            "New York Jets",
            "Pittsburgh Steelers",
            "Tennessee Titans"
    };
    vector<pair<string, string>> placeholder = {};
    for (int i = 0; i < 32; ++i) {
        tradeHistory.emplace(teams[i], placeholder);
    }
}

void TradeHistory::SetRoundNumber(int round) {
    this->roundNumber = round;
}

bool TradeHistory::AddTrade(std::string team1, std::string team2, string details) {
    tradeHistory[team1].push_back(make_pair(team2, details));
    tradeHistory[team2].push_back(make_pair(team1, details));
    return true;
}

vector<string> TradeHistory::GetTradesNoDetails(std::string team) {
    vector<pair<string, string>> trades = tradeHistory.at(team);
    vector<string> res;
    for (pair<string, string> trade : trades) {
        res.push_back(trade.first);
    }
    return res;
}

vector<pair<string, string>> TradeHistory::GetTradesWithDetails(std::string team) {
    return tradeHistory.at(team);
}

bool TradeHistory::TradeBetween(std::string team1, std::string team2) {
    for (pair<string, string> trade : tradeHistory.at(team1)) {
        if (trade.first == team2)
            return true;
    }
    return false;
}
