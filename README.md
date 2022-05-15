# CSCI 3081 Homework 4 - Celebrity Bots Extension
Team DDrill/Collaborators:<br>
Ben Vang <br>
Renee Liu <br>
Roby Thomas <br>
Donald Tan <br>

## Getting Started

Here is a quick overview of how to run the visualization (These steps are similar in each build environment.  See below for environment details.):

    ```bash
    # Go to the project directory
    cd /path/to/repo/project

    # Build the project
    make -j

    # Run the project (./build/web-app <port> <web folder>)
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```
Open up two browser tabs:<br>
1. Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips. <br>
    a. Enter a name and click on <strong>only</strong> two locations on the 
    google maps image. Then click schedule.<br>
    b. Switch to the browser tab with the URL below. <br>
2. Navigate to http://127.0.0.1:8081 and you should see a visualization.  You can move and pan the camera with left and right mouse buttons.  <br>
    a. At the top right you can select an entity (drones or robots) that the camera will focus on during the simulation.<br>
    b. After first scheduling a trip, the drone should move towards the robot.<br>

## Description of Project and Refactored files
Over the course of the entire semester, we learned to understand and refactor existing code to implement the larger ideas learned in class. The given code included all of the front end and most of the back end. <br><br>
The goal of the final project was to refactor the drone taxi simulation to do something "interesting". Our team decided to use the decorator design pattern to create a "Wallet" for the robot that will pay for the drone taxi system. Below are the changes we made to the given code:<br>
1. /project/libs/transit/src/WalletDecorator.cc
2. /project/libs/transit/include/WalletDecorator.h
3. Multiple changes to the 4 strategy .cc and .h files
4. Changes in drone.cc and drone.hh to call the Robot's Pay() methods<br>

To see our changes, you can view the print statements in the terminal during the scheduling and drone simulation. Drones are generated with 

## Sprint Retrospective
We had meetings even if we couldn't meet in person thanks to discord.
The J4 sprint board was a good way to organize tasks at the beginning,
even if we ended up not using it much.

We weren't able to stick closely to the sprint because the project didn't have
too many moving parts.

What we could do better if there was another sprint would be to fully utilize the J4
board. Which would require us to work individually more.

What we've learned is a lot of practice with C++ and the intricacies of inheriting and debugging.
Learned more of how to refactor code and make our own decorator pattern.
Sprints for really big projects take a lot of communication.

## Disclaimer/Bugs
If you would like to restart the simulation you must first refresh the simulation browser tab and <strong>then</strong> the schedule.html tab. Otherwise, multiple bugs arise including the robots acting as drones
Our current implementation works for the beeline strategy when scheduling using schedule.html, but there may be some bugs in the other strategies.
