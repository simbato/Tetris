#include "game.h"
#include "playstate.h"

#include <iostream>

Game::Game() : mWindow(sf::VideoMode(1000,1000), "Tetris"), mGameSpeed(3.00f),
               mGameScore(0)
{
    mAllStates[GameState::State::Welcome] = new WelcomeState(this);
    mAllStates[GameState::State::Playing] = new PlayState(this);
    mAllStates[GameState::State::Speed] = new SpeedState(this);
    setState(GameState::Welcome);
}

Game::~Game()
{
   // Eventualna dealokacija  
}

void Game::run(){
    sf::Clock clock;
    sf::Time  protekloVrijeme = sf::Time::Zero;
    sf::Time dt;
    while(mWindow.isOpen()){

        processEvents();
        if (mpGameState == mAllStates[GameState::State::Speed])
            dt = sf::seconds(1.0/120.0);
        else dt = sf::seconds(1.0/mGameSpeed);
        protekloVrijeme += clock.restart();
        if(protekloVrijeme >= dt)
        {
            update();
            protekloVrijeme=sf::Time::Zero;
        }
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
		}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
