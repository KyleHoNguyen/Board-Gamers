#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "BoardGame.h"
#include "Sorting.h"


using  namespace std;

int main()
{
    cout << "======= GAME SELECTOR v 0.1 =======" << endl;
    //cout << "uwu nyan!!!! input your choices with a number!!! owo :P";

    //creating a vector of our board game object  and filling it using File IO operations

    vector<BoardGame*> storage;
    string line = "null";
    string fileName = "BGG_data_tab.txt";
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        getline(inFile, line);

        while (getline(inFile, line))
        {
            istringstream stream(line);
            //list all variables we need
            string sid;
            string name = "null";//
            string spublishDate = "";
            string sminPlayers = "";
            string smaxPlayers = "";
            string splayTime = "";
            string sminAge = "";
            string susersRated = "";
            string sratingAvg = "";
            string sBGGrank = "";
            string scomplexity = "";
            string sownedUsers = "";
            string mechanics = "null";
            string domains = "null";

            //reading in input and storing it into buffers
            getline(stream, sid, '\t');
            getline(stream, name, '\t');
            getline(stream, spublishDate, '\t');
            getline(stream, sminPlayers, '\t');
            getline(stream, smaxPlayers, '\t');
            getline(stream, splayTime, '\t');
            getline(stream, sminAge, '\t');
            getline(stream, susersRated, '\t');
            getline(stream, sratingAvg, '\t');
            getline(stream, sBGGrank, '\t');
            getline(stream, scomplexity, '\t');
            getline(stream, sownedUsers, '\t');
            getline(stream, mechanics, '\t');
            getline(stream, domains, '\t');

            //converting string input to correct data types
            int id = stoi(sid);
            int publishDate = stoi(spublishDate);
            int minPlayers = stoi(sminPlayers);
            int maxPlayers = stoi(smaxPlayers);
            int playTime = stoi(splayTime);
            int minAge = stoi(sminAge);
            int usersRated = stoi(susersRated);
            double ratingAvg = stod(sratingAvg);
            int BGGrank = stoi(sBGGrank);
            double complexity = stod(scomplexity);
            int ownedUsers = stoi(sownedUsers);

            //create a board game object
            BoardGame* game = new BoardGame(id, name, publishDate, minPlayers, maxPlayers, playTime, minAge, usersRated, ratingAvg, BGGrank, complexity, ownedUsers, mechanics, domains);

            storage.push_back(game);
        }

    }

    else // helps us know if our code is wrong or if we are just importing the file wrong
    {
        cout << "file could not be read" << endl;
    }

    //we need a vetor to hold the board games and a vector that can be modified based on the user's preferences

    vector<BoardGame*> boardGames = storage;
    vector<BoardGame*> temp;


    cout << "Which sorting algorithm would you like to use?" << endl;
    cout << "1. Cocktail Sort" << endl << "2. Shell Sort" << endl;
    int sortchoice = 0;
    cin >> sortchoice;

    /*now we have a series of questions that allows the user to filter games by their preferences.
    Temp is filled based on whats in the board games vector alreadyand what is specified by the preferences,
    then that is copied into the vector called board games again.
    */

    cout << "How many players does your game need to account for? Enter Zero if you do not have a preference." << endl;
    int choice = 0;
    cin >> choice;

    if (choice != 0)
    {
        for (auto it = boardGames.begin(); it != boardGames.end(); it++) {
            if ((*it)->maxPlayers >= choice) {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();
    }


    cout << "How long would you like your game to be?  Enter Zero if you do not have a preference." << endl << "1. Short (0mins - 30mins)" << endl << "2. Medium (30mins - 1 hr)" << endl << "3. Long (1hr - 3 hrs)" << endl << "4. Extra Long (Multiple Days)" << endl;
    cin >> choice;
    if (choice == 1)
    {

        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->playTime <= 30)
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();

    }
    if (choice == 2)
    {
        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->playTime > 30 && (*it)->playTime <= 60)
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();

    }
    if (choice == 3)
    {
        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->playTime < 30 && (*it)->playTime <= (60 * 4))
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();
    }
    if (choice == 4)
    {
        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->playTime > (60 * 4))
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();

    }

    cout << "Do you prefer vintage games or modern games? Enter Zero if you do not have a preference." << endl << "1. Modern Games" << endl << "2. Vintage Games" << endl;
    cin >> choice;

    if (choice == 1)
    {
        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->publishDate >= 2000)
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();
    }
    if (choice == 2)
    {
        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->publishDate < 2000)
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();
    }

    cout << "On a scale of 0-5 what level of complexity would you like? You may enter number with decimals. " << endl;
    double complexityChoice;
    cin >> complexityChoice;


        for (auto it = boardGames.begin(); it != boardGames.end(); it++)
        {
            if ((*it)->complexity <= (complexityChoice + 0.5) && (*it)->complexity >= (complexityChoice - 0.5))
            {
                temp.push_back(*it);
            }
        }
        boardGames.clear();
        boardGames = temp;
        temp.clear();



    /*
    Here we are running out sorting algoritms, but they are flanked on each side by commands from the chrono header
    this allows us to time how long each sort takes and then compare them after the fact.
    */
    cout << "" << endl;
    cout << "======= TIME COMPARISON =======" << endl;
    if (sortchoice == 1) {
        auto started = std::chrono::high_resolution_clock::now();
        cocktail(boardGames);
        auto ended = std::chrono::high_resolution_clock::now();
        std::cout << "it took " << std::chrono::duration_cast<std::chrono::nanoseconds>(ended - started).count() << " nanoseconds to sort" << endl;

        auto altStart = std::chrono::high_resolution_clock::now();
        shellSort(boardGames);
        auto altEnd = std::chrono::high_resolution_clock::now();
        std::cout << "in comparison to the " << std::chrono::duration_cast<std::chrono::nanoseconds>(altEnd - altStart).count() << " nanoseconds it took for Shell sort to sort" << endl;
    }
    else {
        auto started = std::chrono::high_resolution_clock::now();
        shellSort(boardGames);
        auto ended = std::chrono::high_resolution_clock::now();
        std::cout << "it took " << std::chrono::duration_cast<std::chrono::nanoseconds>(ended - started).count() << " nanoseconds to sort" << endl;

        auto altStart = std::chrono::high_resolution_clock::now();
        cocktail(boardGames);
        auto altEnd = std::chrono::high_resolution_clock::now();
        std::cout << "in comparison to the " << std::chrono::duration_cast<std::chrono::nanoseconds>(altEnd - altStart).count() << " nanoseconds it took for Cocktail sort to sort" << endl;
    }

    // Print resutls

    cout << "" << endl;
    cout << "======= RATINGS =======" << endl;
    vector<BoardGame*> topten;
    int count = 1;
    for (auto it = boardGames.end() - 1; it != (boardGames.end() - 11); it--) {
        cout << count << ". " <<  (*it)->name << " ||  rating average is: " << (*it)->ratingAvg << endl;
        topten.push_back(*it);
        count++;
    }
    cout << endl;

    cout << "If you would like to learn more about any of these games, please enter it's ranking number! \nIf you would like to quit, please enter 0 at any time!" << endl;
    cout << "=========================================" << endl;
    cout << endl;
    int selection;
    cin >> selection;
    while (selection != 0)
    {
        cout << endl;
        cout << topten.at(selection - 1)->name << endl;
        cout << "--------------------" << endl;
        cout << "BGG ID: " << topten.at(selection-1)->id << "  ||  " << "BGG RANK: " << topten.at(selection-1)->BGGrank << endl;
        cout << topten.at(selection-1)->usersRated << " people have rated this game, giving it an average of: " << topten.at(selection-1)->ratingAvg << endl;
        cout << "Game Specs" << endl;
        cout << "Player count: " << topten.at(selection-1)->minPlayers << " - " << topten.at(selection-1)->maxPlayers << " Players" << endl;
        cout << "Play Time: " << topten.at(selection-1)->playTime << " mins" << endl;
        cout << "Published in: " << topten.at(selection-1)->publishDate << endl;
        cout << "Complexity Rating: " << topten.at(selection-1)->complexity << endl;
        cout << "Genres: " << topten.at(selection-1)->domains << endl;
        cout << "Features: " << topten.at(selection-1)->mechanics << endl;

        cout << endl;

        cin >> selection;

    }
    cout << "Hope you found a new board game to play!!" << endl;
    return 0;
}
