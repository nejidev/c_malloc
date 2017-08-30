测试环境 ubuntu16.4 gcc 5.4 正常 

free 后的内存块，还可以被重新 malloc 


测试结果
#/test/./sram_malloc
p1 malloc ok addr:134521628

##########TraceHeap#############
index: 0 empty:0 addr:900
index: 1 empty:0 addr:800
index: 2 empty:0 addr:700
index: 3 empty:1 addr:600
index: 4 empty:1 addr:500
index: 5 empty:1 addr:400
index: 6 empty:1 addr:300
index: 7 empty:1 addr:200

##########TraceHeap#############
p2 malloc ok addr:134521428

##########TraceHeap#############
index: 0 empty:0 addr:900
index: 1 empty:0 addr:800
index: 2 empty:0 addr:700
index: 3 empty:0 addr:600
index: 4 empty:0 addr:500
index: 5 empty:1 addr:400
index: 6 empty:1 addr:300
index: 7 empty:1 addr:200

##########TraceHeap#############
p1 free

##########TraceHeap#############
index: 0 empty:1 addr:900
index: 1 empty:1 addr:800
index: 2 empty:1 addr:700
index: 3 empty:0 addr:600
index: 4 empty:0 addr:500
index: 5 empty:1 addr:400
index: 6 empty:1 addr:300
index: 7 empty:1 addr:200

##########TraceHeap#############
p3 malloc ok addr:134521828

##########TraceHeap#############
index: 0 empty:0 addr:900
index: 1 empty:1 addr:800
index: 2 empty:1 addr:700
index: 3 empty:0 addr:600
index: 4 empty:0 addr:500
index: 5 empty:1 addr:400
index: 6 empty:1 addr:300
index: 7 empty:1 addr:200

##########TraceHeap#############

##########TraceHeap#############
index: 0 empty:1 addr:900
index: 1 empty:1 addr:800
index: 2 empty:1 addr:700
index: 3 empty:1 addr:600
index: 4 empty:1 addr:500
index: 5 empty:1 addr:400
index: 6 empty:1 addr:300
index: 7 empty:1 addr:200

##########TraceHeap#############
p4 malloc err
