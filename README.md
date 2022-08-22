42 School project

# lem-in
 Program to calculate optimal ant paths.


Specifications

• The goal of this project is to find the quickest way to get n ants across the farm.
• Quickest way means the solution with the least number of lines, respecting the
output format requested below.
• Obviously, there are some basic constraints. To be the first to arrive, ants will need
to take the shortest path (and that isn’t necessarily the simplest). They will also
need to avoid traffic jams as well as walking all over their fellow ants.
• At the beginning of the game, all the ants are in the room ##start. The goal is
to bring them to the room ##end with as few turns as possible. Each room can
only contain one ant at a time. (except at ##start and ##end which can contain
as many ants as necessary.)
• We consider that all the ants are in the room ##start at the beginning of the game.
• At each turn you will only display the ants that moved.
• At each turn you can move each ant only once and through a tube (the room at
the receiving end must be empty).
• You must to display your results on the standard output in the following format:
"
number_of_ants
the_rooms
the_links

Lx-y Lz-w Lr-o ...
"
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
w, o represents the rooms’ names.


Project was only allowed to use the following functions:

◦ malloc
◦ free
◦ read
◦ write
◦ strerror
◦ perror
◦ exit


This program used bread-first-search (BTS) algorithm to find the distance of each room from the starting room and it searches all the distances until each room has a distance value including the end room. BTS has a notation of big O.

Then it follows the lowest distance of end room's connected rooms to find the shortest paths.

For optimal solution ie. shortest amount of moves, the maxium number of ants traveling through structure is limited by the amount of neighboring rooms the starting room has since only the starting room and the end room can hold more than one ant. Therefore if starting room has for example 3 connected rooms, the ants will be only take maxium of 3 different paths. It also applies to the end room, if end room has only 2 rooms connected, the maxium number of paths is limited to 2. In a case where starting and ending rooms have multiple connection, it only makes sense to take path that is less than (distance + ants - 1).

During building of the program it was important to think about the speed since the specifications stated.

"Of course, your algorithm must render within a reasonable time, even in a case with
4000 rooms. 2 or 3 seconds is great, 9 seconds is mediocre, 15 seconds is too much. "
and
"These are maps with sometimes more than 10,000 lines, the way you
read and write data must also be fairly fast."


