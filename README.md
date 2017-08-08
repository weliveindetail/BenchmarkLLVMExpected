# BenchmarkLLVMExpected
Benchmarks for llvm::Expected vs. std::error_code

```
$ ./BenchmarkExpected 
Run on (4 X 2300 MHz CPU s)
2017-08-08 13:30:10
-----------------------------------------------------------------------------------------
Benchmark                                                  Time           CPU Iterations
-----------------------------------------------------------------------------------------
BM_Int_NoErrors_ErrorCode/manual_time                     57 ns        186 ns   11720577
BM_Int_NoErrors_Expected/manual_time                      58 ns        184 ns   11676388
BM_UniquePtr_NoErrors_ErrorCode/manual_time              196 ns        482 ns    3626108
BM_UniquePtr_NoErrors_Expected/manual_time               189 ns        475 ns    3699592
BM_Vector_NoErrors_ErrorCode/manual_time                 120 ns        301 ns    5684176
BM_Vector_NoErrors_Expected/manual_time                  125 ns        310 ns    5280341
BM_Int_SuccessAlways_ErrorCode/manual_time                59 ns        188 ns   11618720
BM_Int_Success2outOf3_ErrorCode/manual_time               58 ns        188 ns   11228040
BM_Int_Success1outOf3_ErrorCode/manual_time               59 ns        188 ns   12442557
BM_Int_SuccessNever_ErrorCode/manual_time                 59 ns        189 ns   11960964
BM_Int_SuccessAlways_Expected/manual_time                 59 ns        197 ns   12308816
BM_Int_Success2outOf3_Expected/manual_time                74 ns        231 ns    8967682
BM_Int_Success1outOf3_Expected/manual_time               101 ns        296 ns    6800167
BM_Int_SuccessNever_Expected/manual_time                 153 ns        427 ns    4643682
BM_UniquePtr_SuccessAlways_ErrorCode/manual_time         176 ns        435 ns    3987093
BM_UniquePtr_Success2outOf3_ErrorCode/manual_time        180 ns        442 ns    3923399
BM_UniquePtr_Success1outOf3_ErrorCode/manual_time        180 ns        440 ns    3829364
BM_UniquePtr_SuccessNever_ErrorCode/manual_time          340 ns        472 ns    2096942
BM_UniquePtr_SuccessAlways_Expected/manual_time          211 ns        493 ns    3831412
BM_UniquePtr_Success2outOf3_Expected/manual_time         186 ns        458 ns    3944365
BM_UniquePtr_Success1outOf3_Expected/manual_time         193 ns        496 ns    3556494
BM_UniquePtr_SuccessNever_Expected/manual_time           450 ns        765 ns    1493735
BM_Vector_SuccessAlways_ErrorCode/manual_time            122 ns        308 ns    5946384
BM_Vector_Success2outOf3_ErrorCode/manual_time           119 ns        301 ns    5836963
BM_Vector_Success1outOf3_ErrorCode/manual_time           119 ns        299 ns    5899873
BM_Vector_SuccessNever_ErrorCode/manual_time             170 ns        298 ns    3937576
BM_Vector_SuccessAlways_Expected/manual_time             125 ns        309 ns    5426091
BM_Vector_Success2outOf3_Expected/manual_time            126 ns        316 ns    5685136
BM_Vector_Success1outOf3_Expected/manual_time            126 ns        315 ns    5529131
BM_Vector_SuccessNever_Expected/manual_time              283 ns        594 ns    2618512
```
