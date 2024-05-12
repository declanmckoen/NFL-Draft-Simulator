#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#pragma once
using namespace std;


// Parent class (ABC)
class Player {
public:
    double value;

    // Weight and height are in SI units (m and kg)
    int age;
    int gamesPlayed;
    double height;
    double weight;
    string name;

    Player() {}
    Player(int age, int gamesPlayed, double height, double weight, string name) {
        this->age = age;
        this->gamesPlayed = gamesPlayed;
        this->height = height * 0.0254;
        this->weight = weight * 0.453592;
        this->name = name;
    }

    string GetInfo() {
        return (name + ", " + to_string(age) + " years old, " + GetPosition() + ", Value: " + to_string(CalculateValue()).substr(0, 5));
    }

    void PrintInfo() {
        cout << name << ", " << age << " years old, " << GetPosition() << ", Value: " << CalculateValue() << endl;
    }

    bool operator>(const Player& other) const {return this->value > other.value;}
    bool operator<(const Player& other) const {return this->value < other.value;}
    bool operator>=(const Player& other) const {return this->value >= other.value;}
    bool operator<=(const Player& other) const {return this->value <= other.value;}

    virtual double CalculateValue() = 0;
    virtual string GetPosition() = 0;
    virtual void GetStats() = 0;
    virtual ~Player() {};
};


// Child classes
class QuarterBack : public Player {
    int touchdowns;
    int interceptions;
    int passingYards;
    float qbr;

public:
    QuarterBack(string nm, int ag, int gp, float ht, float wt, int tds,
                int ints, float py, float r) : Player(ag, gp, ht, wt, nm),
                                   touchdowns(tds), interceptions(ints), passingYards(py), qbr(r) {}

    double CalculateValue() override {
        // Define weights for each factor

        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 7.0 * ((height * weight) - 100.0f);
        const double touchdownsFunction = (8.0f / gamesPlayed) * touchdowns;
        const double interceptionsFunction = (-10.0f / gamesPlayed) * interceptions;
        const double yardsFunction = (10.0f / gamesPlayed) * passingYards;
        const double quarterbackRatingFunction = 15.0f * qbr;

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             touchdownsFunction +
                             interceptionsFunction +
                             yardsFunction +
                             quarterbackRatingFunction;

        // Normalize to a scale between 0 and 10
        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("QuarterBack");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Touchdowns: " << touchdowns << endl;
        cout << "-Interceptions: " << interceptions << endl;
        cout << "-Passing Yards: " << passingYards << endl;
        cout << "-Quarterback rating: " << qbr << endl;
    }
};


class RunningBack : public Player {
    int touchdowns;
    int fumbles;
    int rushingYards;

public:
    RunningBack(string nm, int ag, int gp, float ht, float wt, int tds, int fmb,
                int ry) : Player(ag, gp, ht, wt, nm),
                                   touchdowns(tds), fumbles(fmb), rushingYards(ry) {}
    double CalculateValue() override {
        const double ageFunction = 110.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 6.0 * ((height * weight) - 100.0f);
        const double touchdownsFunction = (30.0f / gamesPlayed) * touchdowns;
        const double fumblesFunction = (-8.0f / gamesPlayed) * fumbles;
        const double yardsFunction = (25.0f / gamesPlayed) * rushingYards;

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             touchdownsFunction +
                             fumblesFunction +
                             yardsFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("RunningBack");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Touchdowns: " << touchdowns << endl;
        cout << "-fumbles: " << fumbles << endl;
        cout << "-Rushing Yards: " << rushingYards << endl;
    }
};


class WideReceiver : public Player {
    int touchdowns;
    int drops;
    int receivingYards;

public:
    WideReceiver(string nm, int ag, int gp, float ht, float wt, int tds, int drps,
                 int ry) : Player(ag, gp, ht, wt, nm),
                             touchdowns(tds), drops(drps), receivingYards(ry) {}
    double CalculateValue() override {
        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 6.0 * ((height * weight) - 100.0f);
        const double touchdownsFunction = (30.0f / gamesPlayed) * touchdowns;
        const double dropsFunction = (-10.0f / gamesPlayed) * drops;
        const double yardsFunction = (30.0f / gamesPlayed) * receivingYards;

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             touchdownsFunction +
                             dropsFunction +
                             yardsFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("WideReceiver");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Touchdowns: " << touchdowns << endl;
        cout << "-Drops: " << drops << endl;
        cout << "-Receiving Yards: " << receivingYards << endl;
    }
};


class TideEnd : public Player {
    int touchdowns;
    int drops;
    int receivingYards;
    float blockingPercentage;

public:
    TideEnd(string nm, int ag, int gp, float ht, float wt, int tds, int drps,
            int ry, float bpct) : Player(ag, gp, ht, wt, nm),
                        touchdowns(tds), drops(drps), receivingYards(ry), blockingPercentage(bpct) {}
    double CalculateValue() override {
        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 10.0 * ((height * weight) - 100.0f);
        const double touchdownsFunction = (15.0f / gamesPlayed) * touchdowns;
        const double dropsFunction = (-10.0f / gamesPlayed) * drops;
        const double yardsFunction = (10.0f / gamesPlayed) * receivingYards;
        const double blockingPercentageFunction = 25.0f * (0.5f * blockingPercentage - 20.0f);

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             touchdownsFunction +
                             dropsFunction +
                             yardsFunction +
                             blockingPercentageFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("TideEnd");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Touchdowns: " << touchdowns << endl;
        cout << "-Drops: " << drops << endl;
        cout << "-Receiving Yards: " << receivingYards << endl;
        cout << "-Successful pass protection rate: " << blockingPercentage << endl;
    }
};


class OffensiveLine : public Player {
    float blockingPercentage;

public:
    OffensiveLine(string nm, int ag, int gp, float ht, float wt,
                  float bpct) : Player(ag,gp, ht, wt, nm),
                  blockingPercentage(bpct) {}
    double CalculateValue() override {
        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 15.0 * ((height * weight) - 100.0f);
        const double blockingPercentageFunction = 30.0f * (0.5f * blockingPercentage - 20.0f);

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             blockingPercentageFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("OffensiveLine");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Successful pass protection rate: " << blockingPercentage;
    }
};


class DefensiveLine : public Player {
    int qbPressures;
    int sacks;

public:
    DefensiveLine(string nm, int ag, int gp, float ht, float wt, int qbps,
                  int scks) : Player(ag, gp, ht, wt, nm),
                                          qbPressures(qbps), sacks(scks) {}
    double CalculateValue() override {
        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 6.0 * ((height * weight) - 100.0f);
        const double qbPressuresFunction = ((20.0f / gamesPlayed) * (0.1f * pow(qbPressures, 2) - 10.0f));
        const double sacksFunction = ((30.0f / gamesPlayed) * (pow(sacks, 2) - 10.0f));

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             qbPressuresFunction +
                             sacksFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("DefensiveLine");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Quarterback pressures: " << qbPressures << endl;
        cout << "-Sacks: " << sacks << endl;
    }
};


class LineBacker : public Player {
    int sacks;
    int tackles;
    int interceptions;

public:
    LineBacker(string nm, int ag, int gp, float ht, float wt, int tck,
               int ints, int scks) : Player(ag, gp, ht, wt, nm),
                                       tackles(tck), interceptions(ints), sacks(scks) {}
    double CalculateValue() override {
        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        double weightHeightFunction = 6.0 * ((height * weight) - 150.0f);
        const double tacklesFunction = ((5.0f / gamesPlayed) * tackles) - 10.0f;
        const double sacksFunction = ((5.0f / gamesPlayed) * (pow(sacks, 2) - 30.0f));
        const double interceptionsFunction = ((5.0f / gamesPlayed) * ((pow(interceptions, 2) - 30.0f)));

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             tacklesFunction +
                             sacksFunction +
                             interceptionsFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("LineBacker");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Sacks: " << sacks << endl;
        cout << "-Tackles: " << tackles << endl;
        cout << "-Interceptions: " << interceptions << endl;
    }
};


class DefensiveBack : public Player {
    int tackles;
    int interceptions;
    int passBreakups;

public:
    DefensiveBack() {};
    DefensiveBack(string nm, int ag, int gp, float ht, float wt, int tck,
                  int ints, int pbrups) : Player(ag, gp, ht, wt, nm),
                  tackles(tck), interceptions(ints), passBreakups(pbrups) {}

    double CalculateValue() override {
        const double ageFunction = 100.0f * (-0.3 * pow(age-27.0, 2) + 16);
        const double weightHeightFunction = 6.0 * ((height * weight) - 100.0f);
        const double tacklesFunction =( (20.0f / gamesPlayed) * tackles) - 10.0f;
        const double interceptionsFunction = ((100.0f / gamesPlayed) * (pow(interceptions, 2) - 10.0f));
        const double passBreakupsFunction = ((25.0f / gamesPlayed) * passBreakups) - 20.0f;

        // Calculate weighted sum
        double weightedSum = ageFunction +
                             weightHeightFunction +
                             tacklesFunction +
                             interceptionsFunction +
                             passBreakupsFunction;

        double maxValue = 100.0;
        double minValue = 0.0;
        double normalizedValue = (weightedSum / maxValue);

        // Ensure the value is within the valid range
        normalizedValue = round(std::max(minValue, std::min(maxValue, normalizedValue)) * 10) / 10;

        value = normalizedValue;
        return normalizedValue;
    }

    string GetPosition() override {
        return string("DefensiveBack");
    }

    void GetStats() override {
        cout << GetInfo() << endl;
        cout << "Stats: " << endl;
        cout << "-Tackles: " << tackles << endl;
        cout << "-Interceptions: " << interceptions << endl;
        cout << "-Pass breakups: " << passBreakups << endl;
    }
};
