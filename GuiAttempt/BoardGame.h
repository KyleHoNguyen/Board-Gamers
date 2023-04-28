#pragma once

#include <string>
using namespace std;

class BoardGame {

public:
    //all the columns from the txt file
    int id;
    string name;
    int publishDate;
    int minPlayers;
    int maxPlayers;
    int playTime;
    int minAge;
    int usersRated;
    double ratingAvg;
    int BGGrank;
    double complexity;
    int ownedUsers;
    string mechanics;
    string domains;

    //constructor for BoardGame Class BoardGame()
    BoardGame(int id, string name, int publishDate, int minPlayers, int maxPlayers, int playTime, int minAge, int usersRated, double ratingAvg, int BGGrank, double complexity, int ownedUsers, string mechanics, string domains)
    {
        this->id = id;
        this->name = name;
        this->publishDate = publishDate;
        this->minPlayers = minPlayers;
        this->maxPlayers = maxPlayers;
        this->playTime = playTime;
        this->minAge = minAge;
        this->usersRated = usersRated;
        this->ratingAvg = ratingAvg;
        this->BGGrank = BGGrank;
        this->complexity = complexity;
        this->ownedUsers = ownedUsers;
        this->mechanics = mechanics;
        this->domains = domains;

    }
    BoardGame(BoardGame *temp)
    {
        id = temp->id;
        name = temp->name;
        publishDate = temp->publishDate;
        minPlayers = temp->minPlayers;
        maxPlayers = temp->maxPlayers;
        playTime = temp->playTime;
        minAge = temp->minAge;
        usersRated = temp->usersRated;
        ratingAvg = temp->ratingAvg;
        BGGrank = temp->BGGrank;
        complexity = temp->complexity;
        ownedUsers = temp->ownedUsers;
        mechanics = temp->mechanics;
        domains = temp->domains;
    }
    string getName() {
        return name;
    }
};
