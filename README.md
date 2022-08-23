# cub3d

<h1 style="text-align: center">
    <img alt="42Lausanne" title="42Lausanne" src="https://github.com/MarJC5/42/blob/main/42_logo.svg" width="140"> </br>
    Project n°8 - minishell
    <h4 style="width: 50%; margin: 2rem auto; font-weight: normal; text-align: center"> 
     This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way. 
    </h4>
</h1>

## Goals

- The program must take as a first argument a scene description file with the .cub
  extension.
- Display different wall textures (the choice is yours) that vary depending on which
  side the wall is facing (North, South, East, West).
- The program must be able to set the floor and ceiling colors to two different ones.
- The program displays the image in a window and respects the following rules:
  - The left and right arrow keys of the keyboard must allow you to look left and
  right in the maze.
  - The W, A, S, and D keys must allow you to move the point of view through
  the maze.
  - Pressing ESC must close the window and quit the program cleanly.
  - Clicking on the red cross on the window’s frame must close the window and
  quit the program cleanly.

## Steps
- [ ] Parse the map:
  - Read the map with gnl and save it.
  - Fill all the empty space space by a ``1`` to fix the map shape and avoid issue for wall creation.