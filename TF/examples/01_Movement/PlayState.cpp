/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include "Game.h"
#include "PlayState.h"
#include "InputManager.h"

PlayState PlayState::m_PlayState;

using namespace std;

int iBomb = 0;

void PlayState::init()
{
    player.load("data/img/Char14.png");
    //TODO: Implementar sprites para movimentos
	//player.load("data/img/bomberman/sprites.gif");
	player.setPosition(10,100);

	for (int i = 0; i< MAX_BOMB; i++){
        bombSprites[i].load("data/img/Char01.png");
        bombSprites[i].setVisible(false);
	}

	bombSprites[iBomb].setPosition(100,250);
	bombSprites[iBomb].setVisible(true);
	iBomb++;
    bombSprites[iBomb].setPosition(50,300);
    bombSprites[iBomb].setVisible(true);
    iBomb++;


	dirx = 0; // sprite direction: right (1), left (-1)
    diry = 0; // down (1), up (-1)

    im = cgf::InputManager::instance();

    im->addKeyInput("left", sf::Keyboard::Left);
    im->addKeyInput("right", sf::Keyboard::Right);
    im->addKeyInput("up", sf::Keyboard::Up);
    im->addKeyInput("down", sf::Keyboard::Down);
    im->addKeyInput("bomb", sf::Keyboard::Space);
    im->addKeyInput("quit", sf::Keyboard::Escape);
    im->addKeyInput("stats", sf::Keyboard::S);
    //im->addMouseInput("rightclick", sf::Mouse::Right);


	cout << "PlayState: Init" << endl;
}

void PlayState::cleanup()
{
	cout << "PlayState: Clean" << endl;
}

void PlayState::pause()
{
	cout << "PlayState: Paused" << endl;
}

void PlayState::resume()
{
	cout << "PlayState: Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game)
{
    sf::Event event;

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
    }

    dirx = diry = 0;

    if(im->testEvent("left"))
        dirx = -1;

    if(im->testEvent("right"))
        dirx = 1;

    if(im->testEvent("up"))
        diry = -1;

    if(im->testEvent("down"))
        diry = 1;

    if(im->testEvent("bomb"))
    {
        if (iBomb == MAX_BOMB) iBomb = 0;
        //TODO: 50 mil bombas por click
        bombSprites[iBomb].setPosition(player.getPosition().x,player.getPosition().y);
        bombSprites[iBomb].setVisible(true);
        cout << "the bomb " << iBomb << " has bem planted at coordinates ";
        cout << player.getPosition().x << ", " << player.getPosition().y << "." << endl;
        iBomb++;
    }

    if(im->testEvent("quit") /*|| im->testEvent("rightclick")*/)
        game->quit();

    if(im->testEvent("stats"))
        game->toggleStats();
}

void PlayState::update(cgf::Game* game)
{
    float x = player.getPosition().x;
    float y = player.getPosition().y;
    x += dirx*5;
    y += diry*5;
    player.setPosition(x,y);
    player.update(game->getUpdateInterval());
}

void PlayState::draw(cgf::Game* game)
{
    screen = game->getScreen();
    screen->draw(player);

    for(int i = 0; i < MAX_BOMB; i++)
    {
        {
            screen->draw(bombSprites[i]);
        }
    }
}
