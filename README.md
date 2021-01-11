## UMD-Grades

## Introduction

The C command-line script reads in points to be deducted, number of assignment drops, 
and whether or not if they want statistical information. Users will then 
put in grades according to assignment number, test score, weight, and 
days late. It will then prompt the numeric score and whether or not 
they want to choose to view statistical information.

## How to Run Code Using GCC (GNU Compiler Collection):
You must have a C compiler installed and execute the following command in the terminal:
- gcc -Wall -std=gnu99 -o a.out source_file.c -lm
<br>
The user must stdin values for penalty points per day, number of dropped assignments, and whether to generate statistical information on the first line.
On the second line, users must stdin value for number of assignments.
Finally, on the third line, users must stdin values for assignment number, assignment score, assignment weight, and number of days late and repeat the progress for the number of assigments they input.

## Command-line Interface:

![UMD-Grades script](https://github.com/DiegoAmores/UMD-Grades/blob/main/images/command-line%20arguments.PNG) <br>
The necessary stdin values for 6 assigments with a 10 point penality, 0 number of dropped assignments, and whether they want statistical information (Y/N).

![UMD-Grades output](https://github.com/DiegoAmores/UMD-Grades/blob/main/images/command-line%20output.PNG)
Once the user has inputted successful values, they are granted with the proper output.


