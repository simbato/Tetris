#include "playstate.h"
#include "game.h"
#include <iostream>

PlayState::PlayState(Game *pGame) : GameState(pGame) {
    mBoard.setSpeed(pGame->mGameSpeed);
}

void PlayState::start(){
    mBoard.clearState();
    mBoard.setSpeed(mpGame->mGameSpeed);

    mScore.clearState();
    mBoard.spawnPiece();
}

void PlayState::handleEvents(sf::Event event){

    if (event.type == sf::Event::KeyPressed){
            if(event.key.code==sf::Keyboard::Left)
                mBoard.update(-1,0);
            if(event.key.code==sf::Keyboard::Right)
                mBoard.update(1,0);
            if(event.key.code==sf::Keyboard::Up)
                mBoard.update(0,0);
            if(event.key.code==sf::Keyboard::Space)
                {
                    mBoard.update(0,2);
                    mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
                    mScore.update();
                }
    }
}

void PlayState::update(){
    mBoard.update(0,1);
    mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
    mScore.update();
    mpGame->mGameScore = mScore.getScore();
   if (mBoard.isGameOver()){
       mpGame->mGameScore = mScore.getScore();
       mpGame->setState(Speed);
   }
}

void PlayState::render(){
    mpGame->getWindow()->draw(mBoard);
    mpGame->getWindow()->draw(mScore);
}


