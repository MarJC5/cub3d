# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    maze_map.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/26 14:16:08 by jmartin           #+#    #+#              #
#    Updated: 2022/08/28 16:39:15 by jmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import inquirer #pip install inquirer
from random import shuffle, randrange, randint, choice

# Set a random map size
map_w = randrange(3, 16)
map_h = randrange(3, 20)

if map_w <= 0:
    map_w = 16
if map_h <= 0:
    map_h = 8

# Create || open file to save futher map details
file = open("maps/maze.cub", 'w')
file.truncate(0)

# Request a spites theme
questions_sprites = [
    inquirer.List('sprites',
                      message="Pleaser select map sprites",
                      choices=['Normal', 'Wolfenstein 3d'],
                      default=['Normal']
                      ),
]

# Save theme user selection
wall = inquirer.prompt(questions_sprites)['sprites'].replace(" ", "").lower()
file.write(''.join("NO ./assets/" + wall + "_north.xpm\n"))
file.write(''.join("SO ./assets/" + wall +"_south.xpm\n"))
file.write(''.join("WE ./assets/" + wall +"_west.xpm\n"))
file.write(''.join("EA ./assets/" + wall +"_east.xpm\n\n"))

# Resquet BG colors
questions_colors = [
    inquirer.List('colors',
                  message="Pleaser select map sprites",
                  choices=['Random', 'White', 'Black', 'Red', 'Green', 'Yellow', 'Blue'],
                  default=['White']
                  ),
]

def set_color(get_color):
    r = randrange(0, 255)
    g = randrange(0, 255)
    b = randrange(0, 255)
    if get_color == 'black':
        return "0,0,0"
    elif get_color == 'white':
        return "255,255,255"
    elif get_color == 'red':
        return "255, 63, 52"
    elif get_color == 'green':
        return "5, 196, 107"
    elif get_color == 'yellow':
        return "255, 211, 42"
    elif get_color == 'blue':
        return "15, 188, 249"
    elif get_color == 'random':
        return ''.join(str(r) + ',' + str(g) + ',' + str(b))

color = inquirer.prompt(questions_colors)['colors'].replace(" ", "").lower()
floor = set_color(color)
color = inquirer.prompt(questions_colors)['colors'].replace(" ", "").lower()
ceilling = set_color(color)

file.write(''.join("F " + floor + "\n"))
file.write(''.join("C " + ceilling + "\n\n"))

# Generate map && place user into it
def make_maze(w = map_w, h = map_h):
    vis = [[0] * w + [1] for _ in range(h)] + [[1] * (w + 1)]
    ver = [["1000"] * w + ['1'] for _ in range(h)] + [[]]
    hor = [["1111"] * w + ['1'] for _ in range(h + 1)]

    def walk(x, y):
        vis[y][x] = 1

        d = [(x - 1, y), (x, y + 1), (x + 1, y), (x, y - 1)]
        shuffle(d)
        for (xx, yy) in d:
            if vis[yy][xx]: continue
            if xx == x: hor[max(y, yy)][x] = "1000"
            if yy == y: ver[y][max(x, xx)] = "0000"
            walk(xx, yy)

    walk(randrange(map_w), randrange(map_h))

    player_pos = ["N", "W", "S", "E"]
    ver_tab = randrange(1, len(ver) - 1)
    var_arr = randrange(1, len(ver[ver_tab]) - 1)
    var_char = randrange(0, len(ver[ver_tab][var_arr]))
    while ver[ver_tab][var_arr][var_char] != '0':
        var_char = randrange(0, len(ver[ver_tab][var_arr]))
    shuffle(player_pos)
    if ver[ver_tab][var_arr][var_char] == '0':
        ver[ver_tab][var_arr] = ver[ver_tab][var_arr].replace('0', choice(player_pos), 1)
    index = 0
    for (a, b) in zip(hor, ver):
        index += 1
        if index < len(ver):
            file.write(''.join(a + ['\n'] + b + ['\n'] ))
        else:
            file.write(''.join(a + ['\n'] + b + ['\0']))

# Run above map generation
make_maze()

file.close()

# Clear terminal after generation
cls = lambda: os.system('cls' if os.name=='nt' else 'clear')
cls()