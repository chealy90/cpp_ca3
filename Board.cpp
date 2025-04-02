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
#include <algorithm>
#include <cctype>

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
         << "\n=========== BUGS ===========\n"
         << setw(10) << "ID"
         << setw(12) << "Type"
         << setw(14) << "Position"
         << setw(12) << "Size"
         << setw(12) << "Direction"
         << setw(10) << "Status"
         << "\n-----------------------------------------------"
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
             << setw(10) << bug->getId()
             << setw(12) << "Crawler"
             << setw(14) << pos
             << setw(12) << bug->getSize()
             << setw(12) << direction
             << setw(10) << status
             << endl;
    }
    cout << endl;
}

void Board::findBug(int id) const {
    bool bugFound = false;

    for (Crawler* bug : crawlers) {
        if (bug->getId() == id) {
            cout << "Bug found !" << endl;
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
    //  need to finish
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
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
    cout << "\n=========== BUGS LIFE HISTORY ===========\n" << endl;

    for (Crawler *bug: crawlers) {
        cout << "ID :: " << bug->getId() << endl;
        cout << "Position :: (" << bug->getPosition().x << "," << bug->getPosition().y << ")" << endl;

        string direction;
        if (bug->getDirection() == Direction::NORTH) {
            direction = "NORTH";
        } else if (bug->getDirection() == Direction::EAST) {
            direction = "EAST";
        } else if (bug->getDirection() == Direction::SOUTH) {
            direction = "SOUTH";
        } else if (bug->getDirection() == Direction::WEST) {
            direction = "WEST";
        }
        cout << "Direction :: " << direction << endl;
        cout << "Size :: " << bug->getSize() << endl;
        cout << "Status :: " << (bug->isAlive() ? "Alive" : "Dead") << endl;

        cout << "\nCrawler Path: ";
        list<Position> path = bug->getPath();
        for (const Position &pos : path) {
            cout << "(" << pos.x << "," << pos.y << ")" << endl;
        }
        cout << (bug->isAlive() ? "Alive" : "Dead") << endl; // need proper format
    }
}

void Board::writeLifeHistoryToFile() const { // https://www.youtube.com/watch?v=M1E3roUNTMY&pp=ygUQI2xpZmVfdGltZV90cmljaw%3D%3D and https://www.youtube.com/watch?v=5VeIOAgjhE0
    time_t currentTime = time(NULL);
    tm *localTime = localtime(&currentTime);

    ofstream fout("bugs_life_history_" +
                  to_string(1900 + localTime->tm_year) + "-" +
                  to_string(1 + localTime->tm_mon) + "-" +
                  to_string(localTime->tm_mday) + "_" +
                  to_string(localTime->tm_hour) + "-" +
                  to_string(localTime->tm_min) + "-" +
                  to_string(localTime->tm_sec) + ".out");

    if (fout) {
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
        }
        fout.close();
    } else {
        cout << "Unable to write bug life history to file !\n";
    }
}

void Board::displayAllCells() const {

}

void Board::runSimulation() {

}



bool Board::isLastBugStanding() {

}