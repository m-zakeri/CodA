# CodA: Source code analysis and synthesis toolkit

By: Morteza Zakeri, Ph.D. candidate

Systematic software testing and quality assurance tools can be built on top of compiler tools such as ANTLR, LLVM, JDT, and Roslyn, with techniques presented in this chapter. Compilers build a detailed model of application code as they validate the syntax and semantics of that code. While traditional compilers used such a model to build the executable output from the source code in a block box manner, the new generation of compilers provides APIs to access the internal details of this model, which can be utilized to build more reliable software. Software testing is more realistic with advanced support by compilers.

There is no practical tool to measure and compute the path coverage in unit testing. 
Most open-source and commercial tools report the statement and branch coverage as statistics for the performed tests. CodA aims to provide a measurement apparatus of the path coverage based on the concept of prime paths in unit testing. First, the control flow graph (CFG) of the unit under test is extracted. Second, the prime path is extracted. Third, the code is instrumented to capture the covered path. Finally, the test data is generated and fed to the unit under test, and the prime path coverage is measured. The main challenge is how we can match the executed path with the prime path in order to find the test effectiveness. 

The CodA contains the following modules:

* Control flow graph extractor
* Prime path extractor
* Source code instrumentor 
* Path coverage computation based on prime-path coverage
* Random test data generation


