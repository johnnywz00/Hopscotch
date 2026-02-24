# Hopscotch

## C++/SFML platformer matching game

<img width="1728" height="1117" alt="Screenshot 2026-02-23 at 10 01 15 PM" src="https://github.com/user-attachments/assets/3b27ce3c-a161-42a6-bb7e-54b191ac2f94" />

### CODE REVIEWER NOTE!!
This codebase is some of my earliest work, which I am posting here in a sort of complementary fashion, even though the code is a fright of inefficiency and disorganization. If you prefer to look at code that has at least had *some* effort put into it towards cleanness and correctness, please view almost any other C++/SFML repository on my user page!

Further elaboration: this is one of several projects that I undertook in that period (2019-20), all of which were motivated primarily by the desire to know if I could "solve" the challenge of bringing this or that mechanic or concept into being through programming language, largely without consulting any other sources to see how it was done (also pre-AI era). The projects are characterized by a lack of concern for code organization, best practices, readability, or maintainability, because my free time was very limited and my chief objective was the satisfaction of knowing I got the idea to work. Most of the time, I fudged things full speed ahead as long as I achieved that much of the goal, and then was ready to move on to the next logical challenge rather than pore over the details of making a well-rounded product fit for public consumption. 

I will say that earlier I had, one way or another, stumbled across a snippet that showed code adding a gravity value and a friction value per frame, and a couple of other rudimentary things like "if the sprite position is less than the screen edge, set the sprite position to the screen edge"; beyond that, this game was my attempt to "figure out" a platformer (and corresponding level editor) from scratch just using my reasoning. 

And, well, it works... but it didn't take long for me to look back on it after the dust settled and feel far from satisfied with the implementation of the sprite collision physics. I saw, however, that well-executed collision detection and the physics that result from it is no superficial exercise, and it wasn't the time and place for me to focus on mastering that one programming aspect rather than exposing myself to others. 

I hope in the future to make a new version of this game, with a more accurate, robust and extensible system of sprite interactions; I still like the idea of trying create, design and code out of my own head, but I may at least familiarize myself with some existing patterns and sprite concepts at that point.

### ABOUT THE PROJECT

A large percentage of the games I made while learning C++ were geared towards my very small children. This game puts the matching concept of the great vintage game Oxyd into platformer style. The title of the game derives from the fact that I, as a child, had a favorite teddy bear named "Scotch", and Scotch is the little character that "hops" around to match the oxyds. (Scotch was in fact one of four similar teddy bears that somehow got collectively regarded by my brother and I as "deh-dehs"; hence the name of the code class Deh.)

The game comes with an incredibly rudimentary level editor, and only a handful of pre-made levels. (The ocean level was a much later addition after sophisticating the editor a little bit.)

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
