#include <iostream>
#include <random>
#include <chrono>
#include <format>
#include "team.h"
#include "tradehistory.h"
#include "player.h"
#include "draft.h"
#include "playergeneration.h"
using namespace std;


int main() {
    Draft draft;
    draft.AssignPlayers();
    draft.DetermineDraftOrder();
    draft.AddProspects();

    cout << "Welcome to NFL Draft Simulation!" << endl;

    bool proceed = true;
    bool startDraft = false;
    do {
        string optionString;
        int option;
        while (true) {
            cout << "\nPlease choose a number below:" << endl;
            cout << "1. Begin draft simulation\n2. View overall team values\n3. Print draft order\n"
                    "4. Print a team's roster\n5. Print a player's stats\n6. View Prospects\n7. Print a prospect's stats"
                    "\n8. View a team's drafted players\n9. Exit\n";
            cout << "Option: ";
            getline(cin, optionString);
            try {
                option = stoi(optionString);
                break;
            }
            catch (invalid_argument& e) {
                cout << "Please enter a valid number!" << endl << endl;
            }
        }

        if (option == 1) {
            startDraft = true;

            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            struct std::tm* currentTime = std::localtime(&time);
            int currentYear = currentTime->tm_year + 1900;

            std::cout << "\nWelcome to the " << currentYear << " NFL draft!" << std::endl;
            cout << "How would you like to proceed?" << endl;
            cout << "1. Pause after each draft selection\n2. Sim to end of the round\n3. Sim to end of the draft\n";
            string choiceString;
            int choice;
            while (true) {
                cout << "Option: ";
                getline(cin, choiceString);
                try {
                    choice = stoi(choiceString);
                    if (choice > 3 || choice < 1) {
                        cout << "Please enter a valid option!" << endl;
                        continue;
                    }
                    break;
                }
                catch(invalid_argument& e) {
                    cout << "Please enter a valid number!" << endl;
                }
            }
            draft.RandomlyCutPlayers();
            for (int i = 0; i < 7; ++i) {
                for (int j = 0; j < 32; ++j) {
                    if (choice == 1) {
                        draft.StartDraft(i, j);
                        cout << "\nPress '1' to continue to the next pick.\nPress '2' to sim to the end of the round\n"
                                "Press '3' to sim to the end of the draft\n";
                        while (true) {
                            cout << "Option: ";
                            getline(cin, choiceString);
                            try {
                                choice = stoi(choiceString);
                                if (choice > 3 || choice < 1) {
                                    cout << "Please enter a valid option!" << endl;
                                    continue;
                                }
                                break;
                            }
                            catch(invalid_argument& e) {
                                cout << "Please enter a valid number!" << endl;
                            }
                        }
                    }
                    else if (choice == 2) {
                        draft.StartDraft(i, j, "EndOfRound");
                    }
                    else if (choice == 3) {
                        draft.StartDraft(i, j, "EndOfDraft");
                    }
                }
                if (choice == 2) {
                    cout << "\nPress '1' to continue to the next pick.\nPress '2' to sim to the end of the round\n"
                            "Press '3' to sim to the end of the draft\nPress '4' to view a team's selection(s)\n";
                    while (true) {
                        cout << "Option: ";
                        getline(cin, choiceString);
                        try {
                            choice = stoi(choiceString);
                            if (choice > 4 || choice < 1) {
                                cout << "Please enter a valid option!" << endl;
                                continue;
                            }
                            if (choice == 4) {
                                cout << "Which team would you like to view?" << endl;
                                string team;
                                while (true) {
                                    cout << "Team: ";
                                    getline(cin, team);
                                    if (draft.TeamExists(team)) {
                                        draft.teams.at(team).DisplayCurrentlyDraftedPlayers();
                                        break;
                                    }
                                    cout << "You did not enter a valid team name. Please try again." << endl;
                                }
                                cout << "\nPress '1' to continue to the next pick.\nPress '2' to sim to the end of the round\n"
                                        "Press '3' to sim to the end of the draft\n";
                                while (true) {
                                    cout << "Option: ";
                                    getline(cin, choiceString);
                                    try {
                                        choice = stoi(choiceString);
                                        if (choice > 3 || choice < 1) {
                                            cout << "Please enter a valid option!" << endl;
                                            continue;
                                        }
                                        break;
                                    }
                                    catch(invalid_argument& e) {
                                        cout << "Please enter a valid number!" << endl;
                                    }
                                }
                            }
                            break;
                        }
                        catch(invalid_argument& e) {
                            cout << "Please enter a valid number!" << endl;
                        }
                    }
                }
            }
        }
        else if (option == 2) {
            cout << endl;
            draft.PrintTeams();
        }
        else if (option == 3) {
            cout << endl;
            draft.PrintDraftOrder();
        }
        else if (option == 4) {
            cout << "Which team would you like to view? Please enter the full NFL team name (i.e. Green Bay Packers)." << endl;
            while (true) {
                cout << "Team: ";
                string team;
                getline(cin, team);
                if (draft.TeamExists(team)) {
                    cout << "\n" << team << " roster:\n\n";
                    draft.PrintTeam(team);
                    break;
                }
                cout << "You did not enter a valid team name. Please try again." << endl;
            }
        }
        else if (option == 5) {
            cout << "\nPress 'q' if you know the name of the player. Press any other button if you need to view a team's roster." << endl;
            string choice;
            getline(cin, choice);
            if (choice == "q") {
                while (true) {
                    cout << "\nWhich player would you like to view?" << endl;
                    cout << "Player: ";
                    string player;
                    getline(cin, player);
                    transform(player.begin(), player.end(), player.begin(), ::toupper);
                    if (draft.PlayerExists(player)) {
                        draft.PrintPlayer(player);
                        break;
                    }
                    cout << "Please enter a valid player name!" << endl << endl;
                }
            }
            else {
                cout << "Which team is the player on?" << endl;
                string team;
                while (true) {
                    cout << "Team: ";
                    getline(cin, team);
                    if (draft.TeamExists(team)) {
                        cout << "\n" << team << " roster:\n\n";
                        draft.PrintTeam(team);
                        break;
                    }
                    cout << "You did not enter a valid team name. Please try again." << endl;
                }
                cout << "\nPlayer: ";
                while (true) {
                    cout << "\nWhich player would you like to view?" << endl;
                    cout << "Player: ";
                    string player;
                    getline(cin, player);
                    transform(player.begin(), player.end(), player.begin(), ::toupper);
                    if (draft.PlayerExists(player)) {
                        cout << endl;
                        draft.PrintPlayer(player, team);
                        break;
                    }
                    cout << "Please enter a valid player name!" << endl << endl;
                }
            }
        }
        else if (option == 6) {
            cout << "How many prospects would you like to view? Enter a number between 1 and 224 inclusive." << endl;
            string numberString;
            int number;
            while (true) {
                cout << "Number: ";
                getline(cin, numberString);
                try {
                    number = stoi(numberString);
                    if (number < 1) {
                        cout << "Please enter a number greater than 0!" << endl;
                        continue;
                    }
                    break;
                }
                catch (invalid_argument& e) {
                    cout << "Please enter a valid number!" << endl;
                }
            }
            cout << "\nThe top " << number << " prospects in the draft are:" << endl;
            draft.PrintProspects(number);
        }
        else if (option == 7) {
            cout << "\nWhich prospect would you like to view?" << endl;
            bool stay = true;
            while (stay) {
                cout << "Prospect: ";
                string prospect;
                getline(cin, prospect);
                transform(prospect.begin(), prospect.end(), prospect.begin(), ::toupper);
                for (int i = 0; i < draft.prospects.size(); ++i) {
                    if (draft.prospects[i]->name == prospect) {
                        cout << endl;
                        draft.prospects[i]->GetStats();
                        stay = false;
                        break;
                    }
                }
                if (stay)
                    cout << "Please enter a valid prospect name!" << endl;
            }
        }
        else if (option == 8) {
            if (!startDraft) {
                cout << "\nYou have not simulated a draft yet!" << endl;
            }
            else {
                cout << "\nWhich team would you like to view?" << endl;
                string team;
                while (true) {
                    cout << "Team: ";
                    getline(cin, team);
                    if (draft.TeamExists(team)) {
                        draft.teams.at(team).DisplayCurrentlyDraftedPlayers();
                        break;
                    }
                    cout << "You did not enter a valid team name. Please try again." << endl;
                }
            }
        }
        else if (option == 9) {
            proceed = false;
        }
        else {
            cout << "Please enter a valid option!" << endl << endl;
        }
    } while (proceed);
}
