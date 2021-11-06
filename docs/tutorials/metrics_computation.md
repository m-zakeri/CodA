# Source code metrics computation


A practical approach to compute such metrics is static analysis of program source code. Again this analysis can be performed by using compilers. The idea is to create a symbol table for the program under analysis and extract desired metrics. In this section, we demonstrate the use of ANTLR to compute two essential design metrics, FANIN, and FANOUT, which affect the testability of a module. 

FANIN and FANOUT can be simply computed from UML class diagrams. In the case of source code, we require to extract a class diagram from the source code. We begin with constructing a simple symbol table to hold the required entities, e.g., classes and their relationships.  Similar to Section 1, the ANTLR listener mechanism is utilized to build the symbol table. The structure of our symbol table is shown in Figure 1.



