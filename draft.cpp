#include "draft.h"
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;


Draft::Draft() {
    TradeHistory tradeHistoryObj;
    for (int i = 1; i <= 7; ++i) {
        tradeHistory.emplace(i, tradeHistoryObj);
        tradeHistory[i].SetRoundNumber(i);
    }

    vector<string> tmsStrings = {
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

    Team teamObj;
    for (int i = 0; i < 32; ++i) {
        teams.emplace(tmsStrings[i], teamObj);
        teams[tmsStrings[i]].SetName(tmsStrings[i]);
    }

    draftOrder.reserve(7);
}

Draft::~Draft() {
    for (int i = 0; i < prospects.size(); ++i) {
        delete prospects[i];
    }
}

bool Draft::PlayerPlayerTrade(int round, std::string team1, std::string team2, vector<Player*> team1ToTeam2,
                              vector<Player*> team2ToTeam1) {
    if (!teams[team1].PlayerPlayerTrade(team1ToTeam2, team2ToTeam1) || !teams[team2].PlayerPlayerTrade(team2ToTeam1, team1ToTeam2))
        return false;

    string details;
    details += "Trade between the " + team1 + " and " + team2 + ":\n\n";
    details += team1 + " receive:\n";
    for (Player* player : team2ToTeam1)
        details += "--" + player->GetInfo() + "\n";
    details += "\n" + team2 + " receive:\n";
    for (Player* player : team1ToTeam2)
        details += "--" + player->GetInfo() + "\n";

    tradeHistory[round].AddTrade(team1, team2, details);
    return true;
}

bool Draft::PlayerPickTrade(int round, std::string team1, std::string team2, vector<Player*> team1ToTeam2,
                            vector<int> team2ToTeam1) {
    if (!teams[team1].PlayerPickTrade(team1ToTeam2, team2ToTeam1) || !teams[team2].PickPlayerTrade(team2ToTeam1, team1ToTeam2))
        return false;

    string details;
    details += "Trade between the " + team1 + " and " + team2 + ":\n\n";
    details += team1 + " receive picks:\n";
    for (int num : team2ToTeam1)
        details += "--" + to_string(num) + "\n";
    details += "\n" + team2 + " receive:\n";
    for (Player* player : team1ToTeam2)
        details += "--" + player->GetInfo() + "\n";

    tradeHistory[round].AddTrade(team1, team2, details);
    return true;
}

bool Draft::PickPlayerTrade(int round, std::string team1, std::string team2, vector<int> team1ToTeam2,
                            vector<Player*> team2ToTeam1) {
    if (!teams[team1].PickPlayerTrade(team1ToTeam2, team2ToTeam1) || !teams[team2].PlayerPickTrade(team2ToTeam1, team1ToTeam2))
        return false;

    string details;
    details += "Trade between the " + team1 + " and " + team2 + ":\n\n";
    details += team1 + " receive:\n";
    for (Player* player : team2ToTeam1)
        details += "--" + player->GetInfo() + "\n";
    details += "\n" + team2 + " receive picks:\n";
    for (int num : team1ToTeam2)
        details += "--" + to_string(num) + "\n";

    tradeHistory[round].AddTrade(team1, team2, details);
    return true;
}

bool Draft::PickPickTrade(int round, std::string team1, std::string team2, vector<int> team1ToTeam2,
                          vector<int> team2ToTeam1) {
    if (!teams[team1].PickPickTrade(team1ToTeam2, team2ToTeam1) || !teams[team2].PickPickTrade(team2ToTeam1, team1ToTeam2))
        return false;

    string details;
    details += "Trade between the " + team1 + " and " + team2 + ":\n\n";
    details += team1 + " receive picks:\n";
    for (int num : team2ToTeam1)
        details += "--" + to_string(num) + "\n";
    details += "\n" + team2 + " receive picks:\n";
    for (int num : team1ToTeam2)
        details += "--" + to_string(num) + "\n";

    tradeHistory[round].AddTrade(team1, team2, details);
    return true;
}

void Draft::AddProspect(Player* player) {
    prospects.push_back(player);
}

void Draft::AddProspects() {
    for (int i = 0; i < 28; ++i) {
        QuarterBack* player = new QuarterBack(playerGenerator.GenerateQB());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        RunningBack* player = new RunningBack(playerGenerator.GenerateRB());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        WideReceiver* player = new WideReceiver(playerGenerator.GenerateWR());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        TideEnd* player = new TideEnd(playerGenerator.GenerateTE());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        OffensiveLine* player = new OffensiveLine(playerGenerator.GenerateOL());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        DefensiveLine* player = new DefensiveLine(playerGenerator.GenerateDL());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        LineBacker* player = new LineBacker(playerGenerator.GenerateLB());
        player->CalculateValue();
        prospects.push_back(player);
    }
    for (int i = 0; i < 28; ++i) {
        DefensiveBack* player = new DefensiveBack(playerGenerator.GenerateDB());
        player->CalculateValue();
        prospects.push_back(player);
    }

    sort(prospects.begin(), prospects.end(), [](const Player* current, const Player* other) {
        return (current->value > other->value);
    });
}

void Draft::AssignPlayers() {
    vector<Player*> players;
    for (int i = 0; i < 96; ++i) {
        QuarterBack* player = new QuarterBack(playerGenerator.GenerateQB());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
    }

    for (int i = 0; i < 96; ++i) {
        RunningBack* player = new RunningBack(playerGenerator.GenerateRB());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
    }

    for (int i = 0; i < 128; ++i) {
        WideReceiver* player = new WideReceiver(playerGenerator.GenerateWR());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
    }

    for (int i = 0; i < 96; ++i) {
        TideEnd* player = new TideEnd(playerGenerator.GenerateTE());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
        iter->second.AddPlayer(players[0]);
        players.erase(players.begin());
    }

    for (int i = 0; i < 320; ++i) {
        OffensiveLine* player = new OffensiveLine(playerGenerator.GenerateOL());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        for (int j = 0; j < 10; ++j) {
            iter->second.AddPlayer(players[0]);
            players.erase(players.begin());
        }
    }

    for (int i = 0; i < 320; ++i) {
        DefensiveLine* player = new DefensiveLine(playerGenerator.GenerateDL());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        for (int j = 0; j < 10; ++j) {
            iter->second.AddPlayer(players[0]);
            players.erase(players.begin());
        }
    }

    for (int i = 0; i < 320; ++i) {
        LineBacker* player = new LineBacker(playerGenerator.GenerateLB());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        for (int j = 0; j < 10; ++j) {
            iter->second.AddPlayer(players[0]);
            players.erase(players.begin());
        }
    }

    for (int i = 0; i < 320; ++i) {
        DefensiveBack* player = new DefensiveBack(playerGenerator.GenerateDB());
        players.push_back(player);
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        for (int j = 0; j < 10; ++j) {
            iter->second.AddPlayer(players[0]);
            players.erase(players.begin());
        }
    }
}

void Draft::CalculateTeamNeeds() {
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        iter->second.CalculateTeamValue();
    }
}

void Draft::DetermineDraftOrder() {
    CalculateTeamNeeds();

    vector<Team*> teamValues;
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        teamValues.push_back(&iter->second);
    }

    sort(teamValues.begin(), teamValues.end(), [](const Team* current, const Team* other) {
        return current->teamValue < other->teamValue;
    });
    for (int i = 0; i < 7; ++i) {
        vector<string> round;
        for (int j = 0; j < 32; ++j) {
            round.push_back(teamValues[j]->name);
        }
        draftOrder.push_back(round);
    }
}

void Draft::PrintDraftOrder() {
    int pick = 1;
    for (int i = 0; i < 7; ++i) {
        cout << "Round " << i+1 << endl;
        for (int j = 0; j < 32; ++j) {
            cout << "Pick " << pick << ": " << draftOrder[i][j] << endl;
            pick++;
        }
    }
}

void Draft::PrintTeams() {
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        iter->second.PrintTeam();
    }
}

bool Draft::TeamExists(string& team) {
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        if (iter->first == team)
            return true;
    }
    return false;
}

void Draft::PrintTeam(string& team) {
    teams.at(team).PrintRoster();
}

bool Draft::PlayerExists(string& player) {
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        if (iter->second.PlayerExists(player))
            return true;
    }
    return false;
}

void Draft::PrintPlayer(string& player, string team) {
    if (team.length() > 0) {
        teams.at(team).PrintPlayer(player);
        return;
    }
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        if (iter->second.PlayerExists(player))
            iter->second.PrintPlayer(player);
    }
}

void Draft::PrintProspects(int number) {
    for (int i = 0; i < number; ++i) {
        cout << i+1 << ". " << prospects[i]->GetInfo() << endl;
    }
}

void Draft::RandomlyCutPlayers() {
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        int i = 0;
        while (i < 7) {
            if (iter->second.RandomlyCutPlayer()) {
                i++;
            }
        }
    }
}

void Draft::StartDraft(int round, int pick, string mode) {
    string currentTeam = draftOrder[round][pick];
    cout << endl << currentTeam << " are on the clock!" << endl;
    teams.at(currentTeam).CalculateRosterNeeds();
    teams.at(currentTeam).DisplayRosterNeeds();

    int timeToSleep;
    if (mode.length() == 0) {
        timeToSleep = rand() % 11;
    }
    else if (mode == "EndOfRound") {
        timeToSleep = rand() % 3;
    }
    else if (mode == "EndOfDraft") {
        timeToSleep = 0;
    }
    sleep_for(seconds(timeToSleep));

    string choice = teams.at(currentTeam).ChooseDraftOrTrade();

    bool drafted = false;
    if (choice == "Draft") {
        string position = teams.at(currentTeam).SelectPosition();
        for (int i = 0; i < prospects.size(); ++i) {
            if (prospects[i]->GetPosition() == position) {
                teams.at(currentTeam).AddToDraftPlayers(prospects[i]);
                teams.at(currentTeam).AddPlayer(prospects[i]);
                cout << currentTeam << " have selected" << endl;
                prospects[i]->PrintInfo();
                prospects.erase(prospects.begin()+i);
                drafted = true;
                break;
            }
        }
        if (!drafted) {
            teams.at(currentTeam).AddToDraftPlayers(prospects[0]);
            teams.at(currentTeam).AddPlayer(prospects[0]);
            cout << currentTeam << " have selected" << endl;
            prospects[0]->GetInfo();
            prospects.erase(prospects.begin());
        }
    }
    else {

    }
}

void Draft::AddTradeRequests() {
    for (auto iter = teams.begin(); iter != teams.end(); ++iter) {
        string choice = iter->second.ChooseDraftOrTrade();
        if (choice == "Trade") {
            vector<string> tradeDetails;
            string team = iter->first;
            string want = iter->second.rosterNeeds[0].second;
            string give = iter->second.rosterNeeds[iter->second.rosterNeeds.size()-1].second;
            tradeDetails = {team, want, give};
            tradeRequests.push_back(tradeDetails);
        }
    }
}

void Draft::ParseTradeRequests(string want) {
    for (int i = 0; i < tradeRequests.size(); ++i) {
        if (tradeRequests[i][2] == want) {

        }
    }
}
