# dijkstra-using-different-heaps
Implementing Dijkstra's algorithm which is used to find single source shortest path in both directed and un-directed graphs and comparing performance when implemented with fibonacci, binomial and binary heaps.<br>

<i>Refer AA_report.pdf for dataset and implementation details</i>

<h3>Steps to execute</h3>
<ul>
  <li> g++ main.cpp fibo.cpp binomial.cpp binary.cpp</li>
  <li> ./a.out < input.txt </li>
</ul>
large - contains code for New York city's road network(ny.txt)
<ul>
		<li>g++ main.cpp my_binary.cpp
		<li>./a.out < ny.txt > output.txt
</ul>

<h3>Results</h3>
<ul>
  <li>Time taken to execute using fibonacci heap on input.txt - 0.126 msec.</li>
  <li>Time taken to execute using binomial heap on input.txt -  0.145 msec.</li>
  <li>Time taken to execute using binary heap on input.txt -  0.055 msec.</li>
</ul>
Time taken to execute using binary heap on ny.txt - 1006.82 msec.<br>
<i>Detailed Results in AA_report.pdf</i>

<h3>Conclusion</h3>
We are able to show that for a small input graph dijkstra’s
algorithm has provided performance boost when implemented
using binary heap as compared to binomial and fibonacci
heaps.
