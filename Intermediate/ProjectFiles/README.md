# Brick Invaders

[<img src="https://img.shields.io/github/v/tag/Dergell/GFT_Spring23?sort=semver">](https://github.com/Dergell/GFT_Spring23/tags)

This is my submission for the Unreal Engine Programming Challenge at Games Job Fair Spring 2023. The prompt was to create a “Space Invaders” type of game within three weeks. I decided to take it up a notch by having the player not just shoot, but use a bouncing ball similar to classic Breakout games.

## Features
* Three visually different invader types
* Invaders will shoot if they have a clear shot, but only one invaders shoots at a time
* Occasionally a UFO will go across the top of the screen, which can be shot for bonus points
* Invaders move as a group coordinated by an InvaderManager class
* The invaders movement speed increases with every destroyed invader
* The player has three lives that only decrease when hit by an invaders shot, not by losing a ball
* The highscore will be saved on the local computer
* When all invaders are destroyed, the stage is clear and a new stage starts with the invaders starting one row lower than before
* Above the player are bunkers that get smaller when shot by invaders or hit by the ball

## How to play
* <kbd>Mouse</kbd> - Move the paddle left or right
* <kbd>Left Click</kbd> - Launch a new ball if you lost the last one

## Thanks to
The corona skybox was made by Ulukai (jonathan.denil@gmail.com), licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/

The sound effects are from https://www.classicgaming.cc/classics/space-invaders/sounds