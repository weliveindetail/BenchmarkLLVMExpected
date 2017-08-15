# BenchmarkLLVMExpected
Benchmarks for llvm::Expected vs. std::error_code

```
$ ./BenchmarkExpected
Run on (4 X 2300 MHz CPU s)
2017-08-15 17:45:00
-----------------------------------------------------------------------------
Benchmark                                      Time           CPU Iterations
-----------------------------------------------------------------------------
BM_Category_FastRand                           4 ns          4 ns  185514990
BM_Category_FunctionCall                       4 ns          4 ns  176132532
BM_Category_BranchInstruction                  8 ns          8 ns   87951853
BM_Category_VirtualFunctionCall               11 ns         11 ns   63829011
BM_Category_HeapAllocDealloc                 104 ns        103 ns    6653486
BM_Category_DiskAccess                     56075 ns      30906 ns      22681
BM_MinStruct_NoInline_Raw                      5 ns          5 ns  156108875
BM_MinStruct_NoInline_ExpectedSuccess          5 ns          5 ns  153644896
BM_MinStruct_NoInline_ExpectedFail           143 ns        142 ns    4749562
BM_NoRVO_OutParam                            115 ns        115 ns    6729604
BM_NoRVO_Copy                                294 ns        293 ns    2411822
BM_RVO_Raw                                   109 ns        109 ns    5994331
BM_RVO_Expected                              108 ns        107 ns    6593696
BM_NRVO_Raw                                  110 ns        110 ns    6131047
BM_NRVO_Expected                             106 ns        106 ns    6143854
BM_Rate_SuccessAlways_ErrorCode               15 ns         15 ns   48455314
BM_Rate_Success2outOf3_ErrorCode              18 ns         17 ns   40349077
BM_Rate_Success1outOf3_ErrorCode              14 ns         14 ns   51315510
BM_Rate_SuccessNever_ErrorCode                 7 ns          7 ns   89726335
BM_Rate_SuccessAlways_Expected                11 ns         11 ns   64640047
BM_Rate_Success2outOf3_Expected               61 ns         61 ns   11329611
BM_Rate_Success1outOf3_Expected              108 ns        107 ns    6957697
BM_Rate_SuccessNever_Expected                142 ns        142 ns    4671930
```
