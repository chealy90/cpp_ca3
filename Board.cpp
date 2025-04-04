//
// Created by favou on 02/04/2025.
//

#include "Board.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cctype>
#include <thread>

using namespace std;

Board::Board() {
    srand(time(NULL));
}

Board::~Board() { // https://en.cppreference.com/w/cpp/language/destructor
    for (Crawler* bug : crawlers) {
        delete bug;
    }
}

bool Board::initialiseBoard(const std::string &filename) {
    ifstream fin("crawler-bugs.txt");
    if (!fin) {
        cout << "\nFile not found !" << endl;
        return false;
    }

    string line;
    while (getline(fin, line)) {
        if (line.length() > 0) {
            char type;
            int id, x, y, direction, size;

            stringstream ss(line);
            string temp;

            getline(ss, temp, ',');
            type = temp[0];

            getline(ss, temp, ',');
            id = stoi(temp);

            getline(ss, temp, ',');
            x = stoi(temp);

            getline(ss, temp, ',');
            y = stoi(temp);

            getline(ss, temp, ',');
            direction = stoi(temp);
            Direction dir;
            if (direction == 1) {
                dir = Direction::NORTH;
            } else if (direction == 2) {
                dir = Direction::EAST;
            } else if (direction == 3) {
                dir = Direction::SOUTH;
            } else if (direction == 4) {
                dir = Direction::WEST;
            } else {
                cout << "Invalid direction ! - going NORTH" << endl;
                dir = Direction::NORTH;
            }

            getline(ss, temp, ',');
            size = stoi(temp);

            Position position;
            position.x = x;
            position.y = y;
            Crawler *bug = new Crawler(id, position, dir, size);
            crawlers.push_back(bug);
            cells[x][y].push_back(bug);
        }
    }
    fin.close();
    return true;
}

void Board::displayAllBugs() const {
    cout << left
         << "=========== BUGS ===========\n"
         << setw(8) << "ID"
         << setw(15) << "Type"
         << setw(14) << "Position"
         << setw(10) << "Size"
         << setw(12) << "Direction"
         << setw(10) << "Status"
         << "\n-------------------------------------------------------------------"
         << endl;

    for (Crawler* bug : crawlers) {
        Position position = bug->getPosition();
        string pos = "(" + to_string(position.x) + ", " + to_string(position.y) + ")";

        string direction;
        if (bug->getDirection() == Direction::NORTH) {
            direction = "NORTH";
        }
        else if (bug->getDirection() == Direction::EAST) {
            direction = "EAST";
        }
        else if (bug->getDirection() == Direction::SOUTH) {
            direction = "SOUTH";
        }
        else if (bug->getDirection() == Direction::WEST) {
            direction = "WEST";
        }

        string status = bug->isAlive() ? "Alive" : "Dead";

        cout << left
             << setw(8) << bug->getId()
             << setw(15) << "Crawler"
             << setw(14) << pos
             << setw(10) << bug->getSize()
             << setw(12) << direction
             << setw(10) << status
             << endl;
    }
    // cout << endl;
}

void Board::findBug(int id) const {
    bool bugFound = false;

    for (Crawler* bug : crawlers) {
        if (bug->getId() == id) {
            cout << "Bug Found !" << endl;
            cout << "ID :: " << bug->getId() << endl;
            cout << "Position :: (" << bug->getPosition().x << "," << bug->getPosition().y << ")" << endl;

            string direction;
            if (bug->getDirection() == Direction::NORTH) {
                direction = "NORTH";
            }
            else if (bug->getDirection() == Direction::EAST) {
                direction = "EAST";
            }
            else if (bug->getDirection() == Direction::SOUTH) {
                direction = "SOUTH";
            }
            else if (bug->getDirection() == Direction::WEST) {
                direction = "WEST";
            }
            cout << "Direction :: " << direction << endl;
            cout << "Size :: " << bug->getSize() << endl;
            cout << "Status :: " << (bug->isAlive() ? "Alive" : "Dead") << endl;
            bugFound = true;
            break;
        }
    }
    if (!bugFound) {
        cout << "Bug {" << id << "} not found" << endl;
    }
}

void Board::updateCell() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cells[x][y].clear();
        }
    }

    for (Crawler* bug : crawlers) {
        if (bug->isAlive()) {
            Position position = bug->getPosition();
            cells[position.x][position.y].push_back(bug);
        }
    }
}

void Board::eatFightFunction() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (cells[x][y].size() > 1) {
                // find the biggest in the cell
                Crawler* largestBug = nullptr;
                int largestSize = 0;
                vector<Crawler*> equalSizeBugs;

                for (Crawler* bug : cells[x][y]) {
                    if (bug->isAlive() && bug->getSize() > largestSize) {
                        largestSize = bug->getSize();
                        largestBug = bug;
                        equalSizeBugs.clear();
                        equalSizeBugs.push_back(bug);
                    } else if (bug->isAlive() && bug->getSize() == largestSize) { // more than 1 bug the same biggest size
                        equalSizeBugs.push_back(bug);
                    }
                }
                // bugs of same size randomly pick oen
                if (equalSizeBugs.size() > 1) {
                    int winnerIndex = rand() % equalSizeBugs.size();
                    largestBug = equalSizeBugs[winnerIndex];
                }

                // fighting bugs
                int sizeGain = 0;
                for (Crawler* bug : cells[x][y]) {
                    if (bug->isAlive() && bug != largestBug) {
                        // bigger bug eats smaller bug after fight
                        sizeGain += bug->getSize();

                        bug->setAlive(false);
                        eatenBy[bug->getId()] = largestBug->getId();
                        cout << "Crawler " << largestBug->getId() << " ate Crawler " << bug->getId()
                             << " at position (" << x << "," << y << ")" << endl;
                    }
                }

                // add tjhe eaten bug to the bigger one in fight
                if (sizeGain > 0) {
                    int newSize = largestBug->getSize() + sizeGain;
                    largestBug->setSize(newSize);
                    cout << "Crawler " << largestBug->getId() << " grew to " << newSize << endl;
                }
            }
        }
    }
}

void Board::tapBoard() {
    for (Crawler *bug : crawlers) {
        if (bug->isAlive()) {
            bug->move();
        }
    }

    // update cells and do option 7
    updateCell();
    eatFightFunction();
}

void Board::displayLifeHistoryAllBugs() const {
    cout << "=========== BUGS LIFE HISTORY ===========" << endl;

    for (Crawler *bug: crawlers) {
        cout << bug->getId();
        // cout << "Position :: (" << bug->getPosition().x << "," << bug->getPosition().y << ")" << endl;
        //
        // string direction;
        // if (bug->getDirection() == Direction::NORTH) {
        //     direction = "NORTH";
        // } else if (bug->getDirection() == Direction::EAST) {
        //     direction = "EAST";
        // } else if (bug->getDirection() == Direction::SOUTH) {
        //     direction = "SOUTH";
        // } else if (bug->getDirection() == Direction::WEST) {
        //     direction = "WEST";
        // }
        // cout << "Direction :: " << direction << endl;
        // cout << "Size :: " << bug->getSize() << endl;
        // cout << "Status :: " << (bug->isAlive() ? "Alive" : "Dead") << endl;

        cout << " Crawler Path: ";
        list<Position> path = bug->getPath();
        for (const Position &pos : path) {
            cout << "(" << pos.x << "," << pos.y << ") ";
        }
       if (bug->isAlive()) {
           cout << "Alive" << endl;
       }
        else {
            auto iter = eatenBy.find(bug->getId());
            if (iter != eatenBy.end()) {
                cout << "Eaten by " << iter->second << endl;
            }
            else {
                cout << "Dead" << endl;
            }
        }
        // cout << endl;
    }
}

void Board::writeLifeHistoryToFile() const { // https://www.youtube.com/watch?v=M1E3roUNTMY&pp=ygUQI2xpZmVfdGltZV90cmljaw%3D%3D and https://www.youtube.com/watch?v=5VeIOAgjhE0
    time_t currentTime = time(NULL);
    tm *localTime = localtime(&currentTime);

    string filename = "bugs_life_history_" +
                  to_string(1900 + localTime->tm_year) + "-" +
                  to_string(1 + localTime->tm_mon) + "-" +
                  to_string(localTime->tm_mday) + "_" +
                  to_string(localTime->tm_hour) + "-" +
                  to_string(localTime->tm_min) + "-" +
                  to_string(localTime->tm_sec) + ".out";
    // cout << "is creating:" << filename << endl; // debug line comment out when done
    ofstream fout(filename);

    if (fout.is_open()) {
        fout << "=========== BUGS LIFE HISTORY ===========\n";
        fout << "CREATED AT :: " << asctime(localTime);

        fout << left
                << setw(8) << "\nID"
                << setw(10) << "Status"
                << setw(8) << "Size"
                << "Life History\n"
                << "----------------------------------------\n";
        for (const Crawler *bug: crawlers) {
            fout << left
                    << setw(8) << bug->getId()
                    << setw(10) << (bug->isAlive() ? "Alive" : "Dead")
                    << setw(8) << bug->getSize()
                    << "Path: ";

            for (const Position &pos: bug->getPath()) {
                fout << "(" << pos.x << "," << pos.y << ") ";
            }
            fout << endl;
        }
        fout.close();
    } else {
        cout << "Unable to create and write bug life history to file !\n";
    }
}

void Board::displayAllCells() const {
    cout << "=========== BUG BOARD CELLS ===========\n";
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cout << "(" << x << "," << y << "): ";

            if (cells[x][y].empty()) {
                cout << "empty";
            } else {
                for (const Crawler *bug: cells[x][y]) {
                    cout << "Crawler " << bug->getId() << ". ";
                }
            }
            cout << endl;
        }
    }
}

bool Board::isLastBugStanding() {
    int alive = 0;
    for (Crawler *bug: crawlers) {
        if (bug->isAlive()) {
            alive++;
        }
    }
    return alive == 1;
}

void Board::runSimulation() {
    cout << "=========== .. RUNNING SIMULATION ===========" << endl;
    int alive = 0;
    for (Crawler *bug: crawlers) {
        if (bug->isAlive()) {
            alive++;
        }
    }
    cout << "Current number of bugs alive :: " << alive << "\n" << endl;

    int totalTaps = 0;
    while ((!isLastBugStanding() && alive > 0) && totalTaps < 20) {
        // cout << "Iteration:" << totalTaps << endl;
        // tap is every 0.1 seconds until game over https://www.geeksforgeeks.org/sleep-function-in-cpp/?ref=header_outind
        this_thread::sleep_for(chrono::milliseconds(100));

        tapBoard();
        totalTaps++;

        alive = 0;
        for (Crawler *bug: crawlers) {
            if (bug->isAlive()) {
                alive++;
            }
        }
        cout << "Tap #" << totalTaps << " - " << alive << " Crawler(s) left" << endl;
    }

    if (alive == 1 && isLastBugStanding()) {
        cout << "=========== COMPLETED SIMULATION ===========\n" << endl;
        cout << "WINNER - The last bug standing :: " << endl;
        for (Crawler *bug: crawlers) {
            if (bug->isAlive()) {
                cout << "Crawler " << bug->getId() << " is the winner ! With size " << bug->getSize() << " !" << endl;
            }
        }
    }
    else if (totalTaps >= 20) {
        cout << "=========== STOPPED SIMULATION ===========\n" << endl;
        cout << "Max iterations (20) reached !" << endl;
    }
    else {
        cout << "=========== COMPLETED SIMULATION ===========\n" << endl;
        cout << ":( All the bugs are dead .. GAME OVER" << endl;
    }

    // writeLifeHistoryToFile();
}

