# Hopscotch

## A C++/SFML platformer matching game

<img width="1436" alt="hopsImg" src="https://github.com/user-attachments/assets/feb53879-c0f7-497c-9d79-404c8eea09e0">

### ABOUT THE PROJECT

A large percentage of the games I made while learning C++ were geared towards my very small children. This game puts the matching concept of the great vintage game Oxyd into platformer style. The title of the game derives from the fact that I, as a child, had a favorite teddy bear named "Scotch", and Scotch is the little character that "hops" around to match the "oxyds".

This game is one of many projects that I undertook in the early days of my programming self-teaching. The projects of this period were motivated primarily by the desire to know if I could "solve" the challenge of bringing this or that mechanic or concept into being through programming language, largely without consulting any other sources to see how it was done. The projects are characterized by a lack of concern for code organization, best practices, readability, or maintainability, because my free time was very limited and my chief objective was the satisfaction of knowing I got the idea to work. Most of the time, when I achieved that much of the goal, I was ready to move on to the next logical challenge rather than pore over the details of making a well-rounded product fit for public consumption. 
In this game in particular, I am far from satisfied with the implementation of sprite collision physics, but again, I was essentially trying to reason it out in my head rather than referencing established patterns, and I saw soon enough that well-executed collision detection and the physics that result from it is no superficial exercise, and it wasn't the time and place for me to focus on mastering that one programming aspect rather than exposing myself to others. I hope in the future to make a more complex version of this game, and at that point I will not be above looking up existing successful sprite physics approaches. 
  
I've taken a little time to restructure some things before posting the code here; nonetheless, much about the program remains primitive or suboptimal as it was originally written. Most notably, I hardcoded my graphics to the size of the screen I worked on at the time, and have had to write some extra code to make them display acceptably on different screen sizes. 

### FILE DESCRIPTIONS
* **sfmlApp:**  Implements `main()`, an SFML window and the abstract app
* **hopscotch:**  Implements primary graphical elements; physics; game logic
* **objects:**  Small structs representing objects and entities in the game
* **zsprite:**  A base class that extends the functionality of SFML's Sprite class
* **vsprite:**  A ZSprite that uses velocity
* **fusemanager:**  An an object to manage timed events like fuses and daemons 
* **jwz:**  C++ utility functions/#defines, shortcuts
* **jwzsfml:**  Like above, but SFML-specific

### BUILDING INSTRUCTIONS
TBA

### TECHNICAL NOTES
I wrote the program on an Intel Mac, where the game is meant to be displayed fullscreen and not in a system window. However, it seems to be confirmed that as of SFML 2.6.1, ARM/Silicon Macs such as the one I am now working on are unable to use fullscreen mode. It sounds like this may be fixed when SFML 2.6.2 is released, but in the meantime, the game will have to run in a system window if being played on an ARM Mac. 
