//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Nicholas Hester on 1/18/17.
//  Copyright © 2017 Nick Hester. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

// Constructor
FBullCowGame::FBullCowGame()
{
    Reset();
}

// Initial values
void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "plane";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
    return WordLengthToMaxTries[GetHiddenWordLength()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) // If the guess is not isogram, return error
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)) // If guess is not lowercase, return error
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) // If guess length is wrong, return error
    {
        return EGuessStatus::Wrong_Length;
    }
    else // Otherwise, return ok
    {
        return EGuessStatus::OK;
    }
}

// Receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); // Assuming same length as guess
    
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            if (Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // Treat 0 and 1 letter words as isogram
    if (Word.length() < 2) {return true;}
    
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        
        if (LetterSeen[Letter])
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }
    
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (Letter != tolower(Letter))
        {
            return false;
        }
    }
    
    return true;
}
