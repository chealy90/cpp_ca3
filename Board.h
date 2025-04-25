//
// Created by favou on 02/04/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include "Crawler.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>


class Board {
private:
    std:: vector<Crawler*> crawlers;
    std:: vector<Crawler*> cells[10][10];
    void updateCell();
    void eatFightFunction();
    std::map<int, int> eatenBy;
public:
    Board();
    ~Board();

    bool initialiseBoard(const std::string& filename);
    void displayAllBugs() const;
    void findBug(int id) const;
    void tapBoard();
    void displayLifeHistoryAllBugs() const;
    void displayAllCells() const;
    void runSimulation();
    void writeLifeHistoryToFile() const;
    bool isLastBugStanding();

    std::vector<Crawler*> getAllBugs();
    std::vector<Crawler*> getAllAliveBugs();


};



#endif //BOARD_H
