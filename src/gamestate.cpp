#include "gamestate.h"
#include "game.h"
#include <iostream>

// Vaš kod dolazi ovdje.

WelcomeState::WelcomeState(Game *pGame) : GameState(pGame) {
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu uèitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText1.setScale(2,2);
    mText2.setScale(1,1);
    mText1.setPosition(200,400);
    mText2.setPosition(300,500);
    mText1.setString("Tetris clone by S.Batovic");
    mText2.setString("Press any key to continue");
}

void WelcomeState::handleEvents(sf::Event event){
    if (event.type == sf::Event::KeyPressed)
        mpGame->setState(Playing);
}

void WelcomeState::update(){
}

void WelcomeState::render(){
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
}

SpeedState::SpeedState(Game *pGame) : GameState(pGame){
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu uèitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mText0.setFont(mFont); mText1.setFont(mFont);
    mText2.setFont(mFont); mText3.setFont(mFont);

    mText0.setScale(1.5f,1.5f); mText1.setScale(1.5f,1.5f);
    mText2.setScale(1.5f,1.5f); mText3.setScale(1.5f,1.5f);

    mText0.setPosition(400,300); mText1.setPosition(280,380);
    mText2.setPosition(100,460); mText3.setPosition(340,540);

    mText0.setString("Score = " + std::to_string(mpGame->mGameScore));
    mText1.setString("Current speed = " + std::to_string(mpGame->mGameSpeed));
    mText2.setString("Use keys Up and Down to change the speed");
    mText3.setString("Enter to continue");
}

void SpeedState::handleEvents(sf::Event event){
    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Up)
            mpGame->mGameSpeed += 0.10f;
        if (event.key.code == sf::Keyboard::Down)
            if (mpGame->mGameSpeed > 1.1f)
                mpGame->mGameSpeed -= 0.10f;
        if (event.key.code == sf::Keyboard::Return)
            mpGame->setState(Playing);
    }
}
void SpeedState::update(){
    mText0.setString("Score = " + std::to_string(mpGame->mGameScore));
    mText1.setString("Current speed = " + std::to_string(mpGame->mGameSpeed));
}
void SpeedState::render(){
    mpGame->getWindow()->draw(mText0);
    mpGame->getWindow()->draw(mText1);
    mpGame->getWindow()->draw(mText2);
    mpGame->getWindow()->draw(mText3);
}
