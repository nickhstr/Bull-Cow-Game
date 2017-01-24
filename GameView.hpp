//
//  GameView.hpp
//  BullCowGame
//
//  Created by Nicholas Hester on 1/24/17.
//  Copyright © 2017 Nick Hester. All rights reserved.
//

#ifndef GameView_hpp
#define GameView_hpp

#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

#endif /* GameView_hpp */
