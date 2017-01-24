//
//  GameView.cpp
//  BullCowGame
//
//  Created by Nicholas Hester on 1/24/17.
//  Copyright © 2017 Nick Hester. All rights reserved.
//

#include <iostream>
#include "GameView.hpp"

using int32 = int;

FBullCowGame BCGame;

// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess;
    do {
        // Get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries()
        << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
                std::cout << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
            default:
                break;
        }
    }
    while (Status != EGuessStatus::OK);
    return Guess;
}


void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    
    return;
}

void PrintIntro()
{
    // Introduce the game
    std::cout << "\nWelcome to Bulls and Cows!\n";
    std::cout << std::endl;
    std::cout << "         }   {         ___ " << std::endl;
    std::cout << "         (o o)        (o o) " << std::endl;
    std::cout << "  /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << " / | BULL |0            0|  COW | \\  " << std::endl;
    std::cout << "*  |----- |              | -----|  *  " << std::endl;
    std::cout << "   ^      ^              ^      ^     " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE! - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
    return;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/n) ";
    FText Response = "";
    std::getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response[0] == 'Y');
}
