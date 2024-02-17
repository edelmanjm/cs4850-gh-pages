# Game Components and Scene

# Description

For this portion of the assignment you may continue the 'follow along exercise' to get up to speed on game programming.

Some of these concepts you may be familiar with, some of these concepts you will be totally new to you depending on what program you are coming from. So once again, we will be going through a full course in order to get you up to speed.

## Components and Scenes

The major revisions that are coming for this iteration of the assignment are to have a component system setup. The idea being that components provide us more flexibility with our game objects. It can be hard to see the power of components until we abstract out per game object the ability to 'script them' (i.e. a ScriptableObject' in a game engine) -- but we're almost there.

The second major revision that you will be adding is to start generating a 'Scene' class for which we can populate all of our GameObjects for the Game Application Loop to process. In part, a 'Scene Class' also makes resource management easier as we 'chunk' or game into different levels or regions in the game world.

**Note** You can follow along the videos which will be published by **Feb. 18, 2024** EOD, or otherwise add your own abstraction.

## Deliverable

- You will complete all of the videos in the 'Components' and 'Scenes' section of the SDL course on courses.mshah.io.
  - The main features of your engine will include:
    - A Component-based system (i.e. We should see some class/struct for 'Component'.
    - A way to 'win' the game (i.e. Your game should be winnable)
    - A way to 'load data' to create differente scenes (i.e. Your application should have the ability to load and populate entities from a configuration file to setup the game)
- Please upload the source code of your game.

## F.A.Q.

1. Question: - How should I follow along the videos?
    - Type as I type, experiment, try things out, and experiment.
    - Just watching the videos on 2X will not be enough to absorb material, it's important to perform *active learning* by trying the examples.
		- In most cases for the vidoes, I will leave my mistakes in so you can also see how I fix things, think, debug, etc.
    - **IMPORTANT**: I have provided source code for most of the videos as they progress. Take the time now to follow along the videos and experiment -- if you simply copy & paste, it may become hard later on to understand how to create your own original works.
