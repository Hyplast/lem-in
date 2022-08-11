42 School project

# lem-in
 Program to calculate optimal ant paths.




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