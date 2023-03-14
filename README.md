## Group members: Ghanem Ghanem, Usman Farooqui
# How to run the program
```bash
[A3_submission]$ make
gcc a3.c -o graph.out
[A3_submission]$ make run
./graph.out
```
this should then give a list of all the maximally connectesd subgraphs and how many vertices are in each one.
at the bottom it should tell you the total amount of maximally connected subgraphs as well.

also in my program on line 113 there is this line here
```C
char const* filename = "web-Google.txt";
```
changing this will allow you to test my code with other files. for example graph.txt

```bash
0 1
0 2
3 2
4 5
```
this should return 2 since there are only 2 maximally connected subgraphs here.

If you have any questions you can message me on teams or send me an email at ghanemg@uwindsor.ca