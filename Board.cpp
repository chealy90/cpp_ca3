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
            Crawler *crawler = new Crawler(id, position, dir, size);
            crawlers.push_back(crawler);
            cells[x][y].push_back(crawler);
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

}

void Board::tapBoard() {

}

void Board::displayLifeHistoryAllBugs() const {

}

void Board::displayAllCells() const {

}

void Board::runSimulation() {

}

void Board::writeLifeHistoryToFile() const {

}

bool Board::isLastBugStanding() {

}

void Board::updateCell() {

}

void Board::eatFunction() {

}