# CSCI 3081 Homework 4 - Celebrity Bots Extension
Team DDrill:
Ben Vang - vang2756
Renee Liu - liu0070
Roby Thomas - thom5141
Donald Tan - tanxx705

## Names and Paths of added files
1. /project/libs/transit/src/WalletDecorator.cc
2. /project/libs/transit/include/WalletDecorator.h
3. Multiple changes to the 4 strategies and their .h files
4. Changes in drone.cc and drone.hh to call the Robot's Pay() methods

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

## Getting Started

Here is a quick overview of how to run the visualization (These steps are similar in each build environment.  See below for environment details.):

    ```bash
    # Go to the project directory
    cd /path/to/repo/project

    # Build the project
    make -j

    # Run the tests
    ./build/test-app

    # Run the project (./build/web-app <port> <web folder>)
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```

Navigate to http://127.0.0.1:8081 and you should see a visualization.  You can move a drone around by using the arrow keys and wsda.  
Navigate to http://127.0.0.1:8081/schedule.html and you should see a a page to schedule the trips.

## Disclaimer/Bugs

Our current implementation works for the beeline strategy, but other strategies still have bugs.
