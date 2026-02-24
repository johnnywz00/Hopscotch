# Hopscotch

## C++/SFML platformer matching game

<img width="1728" height="1117" alt="Screenshot 2026-02-23 at 10 01 15 PM" src="https://github.com/user-attachments/assets/3b27ce3c-a161-42a6-bb7e-54b191ac2f94" />

### CODE REVIEWER NOTE!!
This codebase is some of my earliest work and to look back on it now, I note much that I would... but not time at the moment... submit as is.  fudged it full speed ahead if it would work

one of many projects that I undertook in the early days of my programming self-teaching. The projects of this period were motivated primarily by the desire to know if I could "solve" the challenge of bringing this or that mechanic or concept into being through programming language, largely without consulting any other sources to see how it was done. The projects are characterized by a lack of concern for code organization, best practices, readability, or maintainability, because my free time was very limited and my chief objective was the satisfaction of knowing I got the idea to work. Most of the time, when I achieved that much of the goal, I was ready to move on to the next logical challenge rather than pore over the details of making a well-rounded product fit for public consumption. 

### ABOUT THE PROJECT

A large percentage of the games I made while learning C++ were geared towards my very small children. This game puts the matching concept of the great vintage game Oxyd into platformer style. The title of the game derives from the fact that I, as a child, had a favorite teddy bear named "Scotch", and Scotch is the little character that "hops" around to match the oxyds. (Scotch was in fact one of four similar teddy bears that somehow got collectively regarded by my brother and I as "deh-dehs"; hence the name of the code class Deh.)



In this game in particular, I am far from satisfied with the implementation of sprite collision physics, but again, I was essentially trying to reason it out in my head rather than referencing established patterns, and I saw soon enough that well-executed collision detection and the physics that result from it is no superficial exercise, and it wasn't the time and place for me to focus on mastering that one programming aspect rather than exposing myself to others. I hope in the future to make a more complex version of this game, and at that point I will not be above looking up existing successful sprite physics approaches. 

LEVEL EDITOR

All the graphics were created by me in paint or pixel art programs, with the exception of the chess pieces amongst the matching images. The majority of sound effects that I use are from the public domain. 

### FILE DESCRIPTIONS
* **sfmlApp:**  Implements `main()` and the abstract app
* **hopscotch:**  Implements primary graphical elements, physics, game logic
* **deh:**  The player character class
* **oxyd:**  The matchable boxes class
* **objects:**  Map items, level structs
  
(From my "reusable modules" repo: https://github.com/johnnywz00/SFML-shared-headers)
* **jwz:**  C++ utility functions, #defines, shortcuts
* **jwzsfml:**  Like above, but SFML-specific
* **zsprite:**  Wrapper class for SFML sprite with many extra methods, particularly related to collision checking
* **vsprite:**  Subclass of ZSprite that uses velocity
* **resourcemanager:**  Static class for accessing resource files globally
* **timedeventmanager:**  Manages fuses/daemons, delayed callbacks

### BUILDING INSTRUCTIONS
Ready-made program files are available on the Releases page of this repository, with versions for MacOS, Windows, and Linux. NO INSTALLATION NECESSARY: just download and double-click. If your OS isn't supported by the pre-made versions, or if you have other reasons for building from source:
- Clone this repository, and navigate to the root folder of that clone in a terminal window.
- Run:
<pre>
   cmake -B build
   cmake --build build --parallel
</pre>
