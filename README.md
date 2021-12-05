## CS F222: Discrete Structures for Computer Science

This repository contains the programming assignment of the course **CS F222: Discrete Structures for Computer Science**.

[Problem Statement](problem/problem.pdf)

## Task

In this assignment, you have to write a program that can answer some user queries based on the input relation data. The program will display various menus as shown. The user provides the option number as an input and the appropriate result is shown to the user.

The program takes a `.csv` file as an input. It contains data about websites and the links each website has along with the labels. If a website with label **A** has a link to website with label **B** then there is `1` present in the cell corresponding to the row of A and column of B, otherwise `0`.

For the consistency in the output of the programs, please note the following: -

1. For the queries which has a simple binary output **Yes/No**, print a single string **Yes** or **No** in a new line. If you need to open a new menu after it, print that menu or else print the same menu again.

2. For displaying the results of queries which involve displaying the website name/names print a space separated string/strings in a single line.

3. For displaying/visualising the graph, you can use the function already implemented in the [visualiser.c](visualiser.c) file. You need to represent your relation in a matrix format and write that to a `.csv` file. Then you can pass the name of your `.csv` file as an argument to the function `plot`. Please read the installation guide carefully in order to successfully run the function on your systems.

> Note: Please refrain from using algorithms that fall outside the domain of this course. Also if you have learnt multiple algorithms for a problem, use the most optimised algorithm in your program.

Also please observe the `SampleInput.csv` File provided with this assignment. You must take input in the same format and also produce `.csv` files in the same format whenever you want to display it using the plot function.


### Instructions to run

To compile on your own system, run
```bash
cd src
gcc assignment.c
```
To view already compiled executable, run
```bash
cd bin
./disco
```
Please ensure you have `Python3` installed on your system along with all other dependencies in `requirements.txt` file.

### Team
- [Dhruv Rawat](https://github.com/thedhruvrawat) (2019B3A70537P)
- [Hardik Jain](https://github.com/nepython) (2019A8PS0318P)
- [Mridul Bhatia](https://github.com/mridul-25) (2019B3A70410P)