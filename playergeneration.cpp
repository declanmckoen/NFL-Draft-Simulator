#include <random>
#include <chrono>
#include "playergeneration.h"
using namespace std;


PlayerGenerator::PlayerGenerator() {
    this->firstNamesFile.open("male-first-names.txt");
    this->lastNamesFile.open("last-names.txt");

    string name;

    while (getline(firstNamesFile, name)) {
        firstNames.push_back(name);
    }

    while (getline(lastNamesFile, name)) {
        lastNames.push_back(name);
    }
}

PlayerGenerator::PlayerGenerator(std::string fNamesFile, std::string lNamesFile) {
    this->firstNamesFile.open(fNamesFile);
    this->lastNamesFile.open(lNamesFile);

    string name;

    while (getline(firstNamesFile, name)) {
        firstNames.push_back(name);
    }

    while (getline(lastNamesFile, name)) {
        lastNames.push_back(name);
    }
}

string PlayerGenerator::GenerateRandomName() {
    string fullName;

    int firstNameIndex = rand() % firstNames.size();
    int lastNameIndex = rand() % lastNames.size();

    fullName += firstNames.at(firstNameIndex) + " " + lastNames.at(lastNameIndex);
    return fullName;
}

int PlayerGenerator::GenerateAge() {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(29.0,4.0);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);

    int age = round(distribution(generator));
    return age;
}

int PlayerGenerator::GenerateGamesPlayed() {
    int gamesPlayed = 1 + (rand() % 301);
    return gamesPlayed;
}

float PlayerGenerator::GenerateHeight() {
    float height = 62 + (rand() % 19);
    return height;
}

float PlayerGenerator::GenerateWeight() {
    float weight = 150 + (rand() % 251);
    return weight;
}

QuarterBack PlayerGenerator::GenerateQB() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int touchdowns = rand() % 650;
    int interceptions = rand() % 337;
    int passingYards = rand() % 90000;
    int qbr = rand() % 159;

    QuarterBack qb(name, age, gamesPlayed, height, weight, touchdowns, interceptions, passingYards, qbr);
    return qb;
}

RunningBack PlayerGenerator::GenerateRB() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int touchdowns = rand() % 176;
    int fumbles = rand() % 167;
    int rushingYards = rand() % 18356;

    RunningBack rb(name, age, gamesPlayed, height, weight, touchdowns, fumbles, rushingYards);
    return rb;
}

WideReceiver PlayerGenerator::GenerateWR() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int touchdowns = rand() % 209;
    int drops = rand() % 101;
    int receivingYards = rand() % 23000;

    WideReceiver wr(name, age, gamesPlayed, height, weight, touchdowns, drops, receivingYards);
    return wr;
}

TideEnd PlayerGenerator::GenerateTE() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int touchdowns = rand() % 117;
    int drops = rand() % 81;
    int receivingYards = rand() % 15200;
    float blockingPercentage = static_cast<float>(rand()) / static_cast <float> (RAND_MAX);

    TideEnd te(name, age, gamesPlayed, height, weight, touchdowns, drops, receivingYards, blockingPercentage);
    return te;
}

OffensiveLine PlayerGenerator::GenerateOL() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int blockingPercentage = static_cast<float>(rand()) / static_cast <float> (RAND_MAX);

    OffensiveLine ol(name, age, gamesPlayed, height, weight, blockingPercentage);
    return ol;
}

DefensiveLine PlayerGenerator::GenerateDL() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int qbPressures = rand() % 800;
    int sacks = rand() % 201;

    DefensiveLine dl(name, age, gamesPlayed, height, weight, qbPressures, sacks);
    return dl;
}

LineBacker PlayerGenerator::GenerateLB() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int sacks = rand() % 102;
    int tackles = rand() % 2100;
    int interceptions = rand() % 30;

    LineBacker lb(name, age, gamesPlayed, height, weight, sacks, tackles, interceptions);
    return lb;
}

DefensiveBack PlayerGenerator::GenerateDB() {
    string name = GenerateRandomName();
    int age = GenerateAge();
    int gamesPlayed = GenerateGamesPlayed();
    float height = GenerateHeight();
    float weight = GenerateWeight();

    int tackles = rand() % 1200;
    int interceptions = rand() % 82;
    int passBreakups = rand() % 201;

    DefensiveBack db(name, age, gamesPlayed, height, weight, tackles, interceptions, passBreakups);
    return db;
}
