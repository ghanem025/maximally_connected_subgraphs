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
input: 
# FromNodeId	ToNodeId
0	1
0	2
0	8
3	4
3	9
6	5
10	2
8	7
output:
2
3
6
there are 3 maximally connected subgraphs
```
in this case the maximally connected subgraphs are {0,1,2,8,10,7} , {3,4,9} and {6,5}. hence why it returns 6, 3, 2.
I have other graphs like graph2.txt and web-google.txt you can use to test as well.
If you have any questions you can message me on teams or send me an email at ghanemg@uwindsor.ca