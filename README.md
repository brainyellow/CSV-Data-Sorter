# CSV-Data-Sorter
Sorts movie data pulled from imdb

How to use:
Our program is designed to receive comma-separated values of imdb movie records through stdin, a “-c” argument to signify sorting by column, and a parameter defining the column to sort. An example command would be:
cat movie_metadata.csv | ./sorter -c movie_title
Keep in mind that the sorter.c file has to be made into an executable for the above command to work by using a command such as:
gcc -o sorter sorter.c
The sorter.c file contains the majority of the function of the program. This file takes in the movie records and stores it as an array of structs, calls the mergesort function, and outputs the sorted array of structs.
In addition to the sorter.c file, our project contains mergesort.c and sorter.h. The mergesort.c contains the necessary functions to sort movies according to the user defined value. The sorter.h is a header file that contains a struct array definition detailing how our program stores movie records. This header file also prototyped functions, such as mergesort, to be used in our program.
