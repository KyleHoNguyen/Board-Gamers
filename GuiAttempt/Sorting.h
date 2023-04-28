#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "BoardGame.h"

using namespace std;


//This is the cocktail sort. Code modified from https://www.geeksforgeeks.org/cocktail-sort/#
//nidufued the code by making it work with a vector<BoardGame*> rather than an interger array

void cocktail(vector<BoardGame*>& games)
{
    bool swapped = true;
    int start = 0;
    int end = games.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (games[i]->ratingAvg > games[i + 1]->ratingAvg) { //  REMEMBER TO UPDATE THIS TO games.at(i).ranks or whatever var we are testing
                swap(games.at(i), games.at(i + 1));
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i) {
            if (games[i]->ratingAvg > games[i + 1]->ratingAvg) {
                swap(games[i], games[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }

}

//This is the shell sort. Code modified from https://www.geeksforgeeks.org/shellsort/
//nidufued the code by making it work with a vector<BoardGame*> rather than an interger array

void shellSort(vector<BoardGame*>& games)
{
    int n = games.size();
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            double tempComplexity = games[i]->ratingAvg;
            BoardGame* tempGame = games[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && games[j - gap]->ratingAvg > tempComplexity; j -= gap) {
                games[j] = games[j - gap];
            }

            games[j] = tempGame;
        }
    }
}