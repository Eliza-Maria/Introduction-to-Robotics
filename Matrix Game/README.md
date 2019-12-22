Project name: brick breaker

Description: this game has some similarities with the well known brick breaker game, but the details and complexity of the initial game change throughout levels. The goal of the game is to break as many bricks as possible in the given time. However, as you advance in level, the difficulty changes, the brick structure is harder to reach and the ball moves faster. Also, you will have less and less time to complete the levels.

How the game meets the requirements: 
- hardware used: 8x8 led matrix, joystick, driver, lcd.
- game specifications: it has a score, the player is time pressured, there are multiple creative levels so the player doesn't get bored, the levels change in complexity and difficulty.

Guide to the game:

  The player controls a 3 led slide which can go right/left or change the position on the Y axis by one slot. This seems like plenty of freedom, however the limitations come in other places: the slide is a bit tricky.
  The main goal of the game is to catch the ball so it doesn't fall down to the bottom wall of the matrix, whereas the second one is to break as many bricks that are attached to the top wall with the said ball. 
  The direction of the ball is always diagonal and can be inverted on either axis, X and Y, depending on the collisions with the walls, slide and the bricks. The slide collision is the most tricky one because it doesn't follow the natural way like the other ones: if the ball falls on the left edge of the slide, the ball will be forced to go left, no matter the original direction; if it falls on the right edge, in a similar way, the ball will go right; if the ball falls on the center, the direction is inverted naturally.
  The game currently has 3 levels, the difficulty increasing with each level. The high score will be stored and permanently updated.

This game follows 
![Brick breaker](../brick_breaker.jpg)

Link to the game demo: https://youtu.be/m9NEFEcZw2U 
