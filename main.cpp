//
//  main.cpp
//  BullCowGame
//
//  Created by Nicholas Hester on 1/17/17.
//  Copyright © 2017 Nick Hester. All rights reserved.
//

// Import game logic and view
#include "FBullCowGame.hpp"
#include "GameView.hpp"
 
// Entry point for application
int main()
{
    do
    {
        PrintIntro();
        PlayGame();
    }
    while (AskToPlayAgain());
    // Exit the application
    return 0;
}
