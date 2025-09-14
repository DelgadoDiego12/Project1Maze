Diego Delgado, 008320631,

All parts of this project belong to me. The only question I asked chatGPT was 
if my code would work when ran with the specific terminal code. I learned that
when the input file was in the same place as my main it would work for blue and
when it was in my cmake it would work on clion on the console. 

I implemented many functions that were all a part of a maze class. findStart will 
find the start of the maze looking on the boundaries. isOpen check to see if the 
space is a walkable path and isBoundary checks if a certain point is a boundary of 
the maze. findPath will traverse the maze and by using backtracking algorithm will
output the path to the end. It makes use of other functions to complete the task.
A data type I used to achieve this was tuple for the pair of coordinates for the maze,
row and column. empty function is used to check if the maze is empty, this is utilized in
error checks. loadFromFile reads the file as characters and changes them to ints and
builds a 2D vector from the input. 

When testing my code in clion is works when the input file is in the cmake folder. When
running it on the terminal making sure the main and input file are in the same place will
allow it to run correctly. My code will print output the maze with blanks in place of the path. 
It will also output the coordinates of the path for readability. 