#include "team.h"
using namespace std;


Team::Team() {
    rosterSize = 0;
    numDraftPicks = 0;
    onTheClock = false;
    currentStates = {1.0, 0.0};
}

Team::Team(std::string name, std::string city) {
    this->name = name;
    this->city = city;
    rosterSize = 0;
    numDraftPicks = 0;
    onTheClock = false;
    currentStates = {1.0, 0.0};
}

Team& Team::operator=(const Team& other) {
    this->name = other.name;
    this->city = other.city;
    rosterSize = other.rosterSize;
    numDraftPicks = other.numDraftPicks;
    onTheClock = other.onTheClock;
    currentStates = other.currentStates;

    this->teamValue = other.teamValue;
    for (Player* player : other.qbs)
        this->qbs.push_back(player);
    for (Player* player : other.rbs)
        this->rbs.push_back(player);
    for (Player* player : other.wrs)
        this->wrs.push_back(player);
    for (Player* player : other.tes)
        this->tes.push_back(player);
    for (Player* player : other.ol)
        this->ol.push_back(player);
    for (Player* player : other.dl)
        this->dl.push_back(player);
    for (Player* player : other.lbs)
        this->lbs.push_back(player);
    for (Player* player : other.dbs)
        this->dbs.push_back(player);
    this->rosterNeeds = other.rosterNeeds;
    this->currentDraftedPlayers = other.currentDraftedPlayers;
    this->draftPicks = other.draftPicks;
    this->draftGrade = other.draftGrade;

    return (*this);
}

Team::~Team() {
    for (int i = 0; i < qbs.size(); ++i) {
        delete qbs[i];
    }
    for (int i = 0; i < rbs.size(); ++i) {
        delete rbs[i];
    }
    for (int i = 0; i < wrs.size(); ++i) {
        delete wrs[i];
    }
    for (int i = 0; i < tes.size(); ++i) {
        delete tes[i];
    }
    for (int i = 0; i < ol.size(); ++i) {
        delete ol[i];
    }
    for (int i = 0; i < dl.size(); ++i) {
        delete dl[i];
    }
    for (int i = 0; i < lbs.size(); ++i) {
        delete lbs[i];
    }
    for (int i = 0; i < dbs.size(); ++i) {
        delete dbs[i];
    }
}

bool Team::operator>(const Team& other) const {
    return this->teamValue > other.teamValue;
}

bool Team::operator<(const Team& other) const {
    return this->teamValue < other.teamValue;
}

bool Team::operator>=(const Team& other) const {
    return this->teamValue >= other.teamValue;
}

bool Team::operator<=(const Team& other) const {
    return this->teamValue <= other.teamValue;
}

bool Team::operator==(const Team& other) const {
    return this->teamValue == other.teamValue;
}

bool Team::operator!=(const Team& other) const {
    return this->teamValue != other.teamValue;
}

void Team::SetName(string& newName) {
    this->name = newName;
}

bool Team::AddPlayer(Player* player) {
    if (rosterSize < rosterLimit) {
        if (player->GetPosition() == "QuarterBack") {
            qbs.push_back(player);
        }
        else if (player->GetPosition() == "RunningBack") {
            rbs.push_back(player);
        }
        else if (player->GetPosition() == "WideReceiver") {
            wrs.push_back(player);
        }
        else if (player->GetPosition() == "TideEnd") {
            tes.push_back(player);
        }
        else if (player->GetPosition() == "OffensiveLine") {
            ol.push_back(player);
        }
        else if (player->GetPosition() == "DefensiveLine") {
            dl.push_back(player);
        }
        else if (player->GetPosition() == "LineBacker") {
            lbs.push_back(player);
        }
        else if (player->GetPosition() == "DefensiveBack") {
            dbs.push_back(player);
        }
        rosterSize++;
        return true;
    }
    return false;
}

bool Team::CutPlayer(std::string playerName) {
    for (int i = 0; i < qbs.size(); ++i) {
        if (qbs[i]->name == playerName) {
            qbs.erase(qbs.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < rbs.size(); ++i) {
        if (rbs[i]->name == playerName) {
            rbs.erase(rbs.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < wrs.size(); ++i) {
        if (wrs[i]->name == playerName) {
            wrs.erase(wrs.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < tes.size(); ++i) {
        if (tes[i]->name == playerName) {
            tes.erase(tes.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < ol.size(); ++i) {
        if (ol[i]->name == playerName) {
            ol.erase(ol.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < dl.size(); ++i) {
        if (dl[i]->name == playerName) {
            dl.erase(dl.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < lbs.size(); ++i) {
        if (lbs[i]->name == playerName) {
            lbs.erase(lbs.begin()+i);
            rosterSize--;
            return true;
        }
    }
    for (int i = 0; i < dbs.size(); ++i) {
        if (dbs[i]->name == playerName) {
            dbs.erase(dbs.begin()+i);
            rosterSize--;
            return true;
        }
    }
    return false;
}

bool Team::RandomlyCutPlayer() {
    if (rosterSize == 0)
        return false;
    int randIndex;
    int randNum = rand() % 9;
    switch (randNum) {
        case 1:
            if (qbs.size() > 0) {
                randIndex = rand() % qbs.size();
                qbs.erase(qbs.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 2:
            if (rbs.size() > 0) {
                randIndex = rand() % rbs.size();
                rbs.erase(rbs.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 3:
            if (wrs.size() > 0) {
                randIndex = rand() % wrs.size();
                wrs.erase(wrs.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 4:
            if (tes.size() > 0) {
                randIndex = rand() % tes.size();
                tes.erase(tes.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 5:
            if (ol.size() > 0) {
                randIndex = rand() % ol.size();
                ol.erase(ol.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 6:
            if (dl.size() > 0) {
                randIndex = rand() % dl.size();
                dl.erase(dl.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 7:
            if (lbs.size() > 0) {
                randIndex = rand() % lbs.size();
                lbs.erase(lbs.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
        case 8:
            if (dbs.size() > 0) {
                randIndex = rand() % dbs.size();
                dbs.erase(dbs.begin()+randIndex);
                rosterSize--;
                return true;
            }
            return false;
    }
    return false;
}

void Team::CalculateRosterNeeds() {
    // For each position, call CalculateValue() function
    // Assign position value as average of values for all players in that position
    // Sort rosterNeeds vector based on values
    double sum = 0;
    double val = 0;
    rosterNeeds.clear();

    for (Player* qb : qbs) {
        sum += qb->CalculateValue();
    }
    if (qbs.size() > 0)
        val = sum / qbs.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "QuarterBack"));
    sum = 0;
    val = 0;

    for (Player* rb : rbs) {
        sum += rb->CalculateValue();
    }
    if (rbs.size() > 0)
        val = sum / rbs.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "RunningBack"));
    sum = 0;
    val = 0;

    for (Player* wr : wrs) {
        sum += wr->CalculateValue();
    }
    if (wrs.size() > 0)
        val = sum / wrs.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "WideReceiver"));
    sum = 0;
    val = 0;

    for (Player* te : tes) {
        sum += te->CalculateValue();
    }
    if (tes.size() > 0)
        val = sum / tes.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "TideEnd"));
    sum = 0;
    val = 0;

    for (Player* o : ol) {
        sum += o->CalculateValue();
    }
    if (ol.size() > 0)
        val = sum / ol.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "OffensiveLine"));
    sum = 0;
    val = 0;

    for (Player* d : dl) {
        sum += d->CalculateValue();
    }
    if (dl.size() > 0)
        val = sum / dl.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "DefensiveLine"));
    sum = 0;
    val = 0;

    for (Player* lb : lbs) {
        sum += lb->CalculateValue();
    }
    if (lbs.size() > 0)
        val = sum / lbs.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "LineBacker"));
    sum = 0;
    val = 0;

    for (Player* db : dbs) {
        sum += db->CalculateValue();
    }
    if (dbs.size() > 0)
        val = sum / dbs.size();
    else
        val = 0;
    rosterNeeds.push_back(make_pair(val, "DefensiveBack"));

    sort(rosterNeeds.begin(), rosterNeeds.end(), [](const pair<double, string>& current, const pair<double, string>& other) {
        return current.first < other.first;
    });
}

void Team::PrintRosterNeeds() {
    for (int i = 0; i < rosterNeeds.size(); ++i) {
        cout << rosterNeeds[i].second << ": " << rosterNeeds[i].first << endl;
    }
}

void Team::PrintRoster() {
    cout << "QuarterBacks: " << endl;
    for (int i = 0; i < qbs.size(); ++i) {
        cout << "-" << qbs[i]->GetInfo() << endl;
    }
    cout << "\nRunningBacks: " << endl;
    for (int i = 0; i < rbs.size(); ++i) {
        cout << "-" << rbs[i]->GetInfo() << endl;
    }
    cout << "\nWide Receivers: " << endl;
    for (int i = 0; i < wrs.size(); ++i) {
        cout << "-" << wrs[i]->GetInfo() << endl;
    }
    cout << "\nTide Ends: " << endl;
    for (int i = 0; i < tes.size(); ++i) {
        cout << "-" << tes[i]->GetInfo() << endl;
    }
    cout << "\nOffensive Line: " << endl;
    for (int i = 0; i < ol.size(); ++i) {
        cout << "-" << ol[i]->GetInfo() << endl;
    }
    cout << "\nDefensive Line: " << endl;
    for (int i = 0; i < dl.size(); ++i) {
        cout << "-" << dl[i]->GetInfo() << endl;
    }
    cout << "\nLinebackers: " << endl;
    for (int i = 0; i < lbs.size(); ++i) {
        cout << "-" << lbs[i]->GetInfo() << endl;
    }
    cout << "\nDefensive Backs: " << endl;
    for (int i = 0; i < dbs.size(); ++i) {
        cout << "-" << dbs[i]->GetInfo() << endl;
    }
}

bool Team::PlayerPlayerTrade(vector<Player*> out, vector<Player*> in) {
    if ((rosterSize - out.size() < 0) || (rosterSize + in.size() > rosterLimit))
        return false;
    for (int i = 0; i < out.size(); ++i) {
        CutPlayer(out[i]->name);
        rosterSize--;
    }
    for (int i = 0; i < in.size(); ++i) {
        AddPlayer(in[i]);
        rosterSize++;
    }
    return true;
}

bool Team::PlayerPickTrade(vector<Player*> out, vector<int> in) {
    if ((rosterSize - out.size() < 0))
        return false;
    for (int i = 0; i < out.size(); ++i) {
        CutPlayer(out[i]->name);
        rosterSize--;
    }
    for (int i = 0; i < in.size(); ++i) {
        draftPicks.push_back(in[i]);
        numDraftPicks++;
    }
    sort(draftPicks.begin(), draftPicks.end());
    return true;
}

bool Team::PickPlayerTrade(vector<int> out, vector<Player*> in) {
    if ((numDraftPicks - out.size() < 0) || (rosterSize + in.size() > rosterLimit))
        return false;
    for (int i = 0; i < out.size(); ++i) {
        for (int j = 0; j < draftPicks.size(); ++j) {
            if (draftPicks[j] == out[i]) {
                draftPicks.erase(draftPicks.begin()+j);
                numDraftPicks--;
                break;
            }
        }
    }
    for (int i = 0; i < in.size(); ++i) {
        AddPlayer(in[i]);
        rosterSize++;
    }
    return true;
}

bool Team::PickPickTrade(vector<int> out, vector<int> in) {
    if (numDraftPicks - out.size() < 0)
        return false;
    for (int i = 0; i < out.size(); ++i) {
        for (int j = 0; j < draftPicks.size(); ++j) {
            if (draftPicks[j] == out[i]) {
                draftPicks.erase(draftPicks.begin()+j);
                numDraftPicks--;
                break;
            }
        }
    }
    for (int i = 0; i < in.size(); ++i) {
        draftPicks.push_back(in[i]);
        numDraftPicks++;
    }
    sort(draftPicks.begin(), draftPicks.end());
    return true;
}

double Team::CalculateTeamValue() {
    rosterNeeds.clear();
    CalculateRosterNeeds();

    double average = 0;
    for (pair<double, string> p : rosterNeeds) {
        average += p.first;
    }
    average /= 8.0f;

    this->teamValue = average;

    return average;
}

void Team::ToggleOnTheClock() {
    onTheClock = !onTheClock;
}

string Team::ChooseDraftOrTrade() {
    float probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    if (probability <= currentStates[0]) {
        return "Draft";
    }
    else {
        return "Trade";
    }
}

void Team::DisplayRosterNeeds() {
    cout << name << " top 3 roster needs:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i+1 << ". " << rosterNeeds[i].second << endl;
    }
}

string Team::SelectPosition() {;
    float probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    if (probability <= 0.6) {
        // Choose first need
        return rosterNeeds[0].second;
    }
    else if (probability <= 0.9) {
        // Choose second need
        return rosterNeeds[1].second;
    }
    else {
        // Choose third need
        return rosterNeeds[2].second;
    }
}

void Team::SortPositions() {
    sort(qbs.begin(), qbs.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(rbs.begin(), rbs.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(wrs.begin(), wrs.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(tes.begin(), tes.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(ol.begin(), ol.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(dl.begin(), dl.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(lbs.begin(), lbs.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
    sort(dbs.begin(), dbs.end(), [](const Player* current, const Player* other) {
        return current->value > other->value;
    });
}

void Team::PrintTeam() {
    cout << name << ", value: " << teamValue << endl;
}

bool Team::PlayerExists(string& player) {
    for (Player* p : qbs) {
        if (p->name == player)
            return true;
    }
    for (Player* p : rbs) {
        if (p->name == player)
            return true;
    }
    for (Player* p : wrs) {
        if (p->name == player)
            return true;
    }
    for (Player* p : tes) {
        if (p->name == player)
            return true;
    }
    for (Player* p : ol) {
        if (p->name == player)
            return true;
    }
    for (Player* p : dl) {
        if (p->name == player)
            return true;
    }
    for (Player* p : lbs) {
        if (p->name == player)
            return true;
    }
    for (Player* p : dbs) {
        if (p->name == player)
            return true;
    }
    return false;
}

void Team::PrintPlayer(string& player) {
    for (Player* p : qbs) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : rbs) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : wrs) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : tes) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : ol) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : dl) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : lbs) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
    for (Player* p : dbs) {
        if (p->name == player) {
            p->GetStats();
            return;
        }
    }
}

void Team::AddToDraftPlayers(Player* player) {
    currentDraftedPlayers.push_back(player);
}

void Team::DisplayCurrentlyDraftedPlayers() {
    cout << name << " have selected:" << endl;
    for (Player* player : currentDraftedPlayers) {
        cout << "-";
        player->PrintInfo();
    }
}
