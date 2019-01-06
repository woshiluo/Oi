#!/usr/bin/env python

from cyaron import * 

for i in range(1, 2): 
    test_data = IO(file_prefix="test", data_id=i)
    n = randint(1000, 1000) 
    m = randint(n-1, n+n-1)
    s = 1 
    test_data.input_writeln(n, m, s)
    graph = Graph.UDAG(n, m, weight_limit=1000)
    test_data.input_writeln(graph) 
    test_data.output_gen("./sf") 
