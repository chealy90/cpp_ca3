#include <iostream>
#include <string>
#include <vector>

#include "Crawler.cpp"

using namespace std;

void runMenu(int& menuChoice) {
    cout << " ---Bugs Life ---" << endl
    << "---Menu---" << endl
    << "1: Initialise Bug Board (load from file)" << endl
    << "2: Display all Bugs." << endl
    << "3: Find a bug (Given an ID)." << endl
    << "4: Tap the Bug Board (cause all to move, fight, eat)." << endl
    << "5: Display Life history of all Bugs (path taken)." << endl
    << "6: Display all Cells listing their Bugs." << endl
    << "7: Run simulation (generates a tap every 10th of a second)." << endl
    << "8: Exit (write life history of all Bugs to file)." << endl
    << "Your Choice: ";

    string temp;
    std::getline(cin, temp);
    menuChoice = stoi(temp);
}


void displayAllBugs(vector<Crawler*> bugs) {
    for (Crawler* pCrawler: bugs) {
        pCrawler->toString();
    }

}

void initialiseSimulation() {

}

void runSimulationLoop() {

}

void recordSimulationResults() {

}




int main() {





    return 0;
}