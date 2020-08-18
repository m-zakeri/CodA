/*******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Camilo Sanchez (Camiloasc1)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/
 /* Last edit: April 2020 by Morteza Zakeri */

grammar CPP14_v2;


/*Basic concepts*/
translationunit
   : declarationseq? EOF
   ;


/*Expressions*/
primaryexpression
   : literal #primaryexpression1
   | This #primaryexpression2
   | '(' expression ')' #primaryexpression3
   | idexpression #primaryexpression4
   | lambdaexpression #primaryexpression5
   ;

idexpression
   : unqualifiedid #idexpression1
   | qualifiedid #idexpression2
   ;

unqualifiedid
   : Identifier #unqualifiedid1
   | operatorfunctionid #unqualifiedid2
   | conversionfunctionid #unqualifiedid3
   | literaloperatorid #unqualifiedid4
   | '~' classname #unqualifiedid5
   | '~' decltypespecifier #unqualifiedid6
   | templateid #unqualifiedid7
   ;

qualifiedid
   : nestednamespecifier Template? unqualifiedid
   ;

nestednamespecifier
   : '::' #nestednamespecifier1
   | thetypename '::' #nestednamespecifier2
   | namespacename '::' #nestednamespecifier3
   | decltypespecifier '::' #nestednamespecifier4
   | nestednamespecifier Identifier '::' #nestednamespecifier5
   | nestednamespecifier Template? simpletemplateid '::' #nestednamespecifier6
   ;

lambdaexpression
   : lambdaintroducer lambdadeclarator? compoundstatement
   ;

lambdaintroducer
   : '[' lambdacapture? ']'
   ;

lambdacapture
   : capturedefault #lambdacapture1
   | capturelist #lambdacapture2
   | capturedefault ',' capturelist #lambdacapture3
   ;

capturedefault
   : '&' #capturedefault1
   | '=' #capturedefault2
   ;

capturelist
   : capture '...'? #capturelist1
   | capturelist ',' capture '...'? #capturelist2
   ;

capture
   : simplecapture #capture1
   | initcapture #capture2
   ;

simplecapture
   : Identifier #simplecapture1
   | '&' Identifier #simplecapture2
   | This #simplecapture3
   ;

initcapture
   : Identifier initializer #initcapture1
   | '&' Identifier initializer #initcapture2
   ;

lambdadeclarator
   : '(' parameterdeclarationclause ')' Mutable? exceptionspecification? attributespecifierseq? trailingreturntype?
   ;

postfixexpression
   : primaryexpression #postfixexpression1
   | postfixexpression '[' expression ']' #postfixexpression2
   | postfixexpression '[' bracedinitlist ']' #postfixexpression3
   | postfixexpression '(' expressionlist? ')' #postfixexpression4
   | simpletypespecifier '(' expressionlist? ')' #postfixexpression5
   | typenamespecifier '(' expressionlist? ')' #postfixexpression6
   | simpletypespecifier bracedinitlist #postfixexpression7
   | typenamespecifier bracedinitlist #postfixexpression8
   | postfixexpression '.' Template? idexpression #postfixexpression9
   | postfixexpression '->' Template? idexpression #postfixexpression10
   | postfixexpression '.' pseudodestructorname #postfixexpression11
   | postfixexpression '->' pseudodestructorname #postfixexpression12
   | postfixexpression '++' #postfixexpression13
   | postfixexpression '--' #postfixexpression14
   | Dynamic_cast '<' thetypeid '>' '(' expression ')' #postfixexpression15
   | Static_cast '<' thetypeid '>' '(' expression ')' #postfixexpression16
   | Reinterpret_cast '<' thetypeid '>' '(' expression ')' #postfixexpression17
   | Const_cast '<' thetypeid '>' '(' expression ')' #postfixexpression18
   | typeidofthetypeid '(' expression ')' #postfixexpression19
   | typeidofthetypeid '(' thetypeid ')' #postfixexpression20
   ;
/*
add a middle layer to eliminate duplicated function declarations
*/


typeidofexpr
   : Typeid_
   ;

typeidofthetypeid
   : Typeid_
   ;

expressionlist
   : initializerlist
   ;

pseudodestructorname
   : nestednamespecifier? thetypename '::' '~' thetypename #pseudodestructorname1
   | nestednamespecifier Template simpletemplateid '::' '~' thetypename #pseudodestructorname2
   | nestednamespecifier? '~' thetypename #pseudodestructorname3
   | '~' decltypespecifier #pseudodestructorname4
   ;

unaryexpression
   : postfixexpression #unaryexpression1
   | '++' castexpression #unaryexpression2
   | '--' castexpression #unaryexpression3
   | unaryoperator castexpression #unaryexpression4
   | Sizeof unaryexpression #unaryexpression5
   | Sizeof '(' thetypeid ')' #unaryexpression6
   | Sizeof '...' '(' Identifier ')' #unaryexpression7
   | Alignof '(' thetypeid ')' #unaryexpression8
   | noexceptexpression #unaryexpression9
   | newexpression #unaryexpression10
   | deleteexpression #unaryexpression11
   ;

unaryoperator
   : '|' #unaryoperator1
   | '*' #unaryoperator2
   | '&' #unaryoperator3
   | '+' #unaryoperator4
   | '!' #unaryoperator5
   | '~' #unaryoperator6
   | '-' #unaryoperator7
   | 'not' #unaryoperator8
   ;

newexpression
   : '::'? New newplacement? newtypeid newinitializer? #newexpression1
   | '::'? New newplacement? '(' thetypeid ')' newinitializer? #newexpression2
   ;

newplacement
   : '(' expressionlist ')'
   ;

newtypeid
   : typespecifierseq newdeclarator?
   ;

newdeclarator
   : ptroperator newdeclarator? #newdeclarator1
   | noptrnewdeclarator #newdeclarator2
   ;

noptrnewdeclarator
   : '[' expression ']' attributespecifierseq? #noptrnewdeclarator1
   | noptrnewdeclarator '[' constantexpression ']' attributespecifierseq? #noptrnewdeclarator2
   ;

newinitializer
   : '(' expressionlist? ')' #newinitializer1
   | bracedinitlist #newinitializer2
   ;

deleteexpression
   : '::'? Delete castexpression #deleteexpression1
   | '::'? Delete '[' ']' castexpression #deleteexpression2
   ;

noexceptexpression
   : Noexcept '(' expression ')'
   ;

castexpression
   : unaryexpression #castexpression1
   | '(' thetypeid ')' castexpression #castexpression2
   ;

pmexpression
   : castexpression #pmexpression1
   | pmexpression '.*' castexpression #pmexpression2
   | pmexpression '->*' castexpression #pmexpression3
   ;

multiplicativeexpression
   : pmexpression #multiplicativeexpression1
   | multiplicativeexpression '*' pmexpression #multiplicativeexpression2
   | multiplicativeexpression '/' pmexpression #multiplicativeexpression3
   | multiplicativeexpression '%' pmexpression #multiplicativeexpression4
   ;

additiveexpression
   : multiplicativeexpression #additiveexpression1
   | additiveexpression '+' multiplicativeexpression #additiveexpression2
   | additiveexpression '-' multiplicativeexpression #additiveexpression3
   ;

shiftexpression
   : additiveexpression #shiftexpression1
   | shiftexpression shiftoperator additiveexpression #shiftexpression2
   ;

shiftoperator
  : RightShift #shiftoperator1
  | LeftShift  #shiftoperator2
  ;

relationalexpression
   : shiftexpression #relationalexpression1
   | relationalexpression '<' shiftexpression #relationalexpression2
   | relationalexpression '>' shiftexpression #relationalexpression3
   | relationalexpression '<=' shiftexpression #relationalexpression4
   | relationalexpression '>=' shiftexpression #relationalexpression5
   ;

equalityexpression
   : relationalexpression #equalityexpression1
   | equalityexpression '==' relationalexpression #equalityexpression2
   | equalityexpression '!=' relationalexpression #equalityexpression3
   ;

andexpression
   : equalityexpression #andexpression1
   | andexpression '&' equalityexpression #andexpression2
   ;

exclusiveorexpression
   : andexpression #exclusiveorexpression1
   | exclusiveorexpression '^' andexpression #exclusiveorexpression2
   ;

inclusiveorexpression
   : exclusiveorexpression #inclusiveorexpression1
   | inclusiveorexpression '|' exclusiveorexpression #inclusiveorexpressio2
   ;

logicalandexpression
   : inclusiveorexpression #logicalandexpression1
   | logicalandexpression '&&' inclusiveorexpression #logicalandexpression2
   | logicalandexpression 'and' inclusiveorexpression #logicalandexpression3
   ;

logicalorexpression
   : logicalandexpression #logicalorexpression1
   | logicalorexpression '||' logicalandexpression #logicalorexpression2
   | logicalorexpression 'or' logicalandexpression #logicalorexpression3
   ;

conditionalexpression
   : logicalorexpression #conditionalexpression1
   | logicalorexpression '?' expression ':' assignmentexpression #conditionalexpression2
   ;

assignmentexpression
   : conditionalexpression #assignmentexpression1
   | logicalorexpression assignmentoperator initializerclause #assignmentexpression2
   | throwexpression #assignmentexpression3
   ;

assignmentoperator
   : '=' #assignmentoperator1
   | '*=' #assignmentoperator2
   | '/=' #assignmentoperator3
   | '%=' #assignmentoperator4
   | '+=' #assignmentoperator5
   | '-=' #assignmentoperator6
   | RightShiftAssign #assignmentoperator7
   | LeftShiftAssign #assignmentoperator8
   | '&=' #assignmentoperator9
   | '^=' #assignmentoperator10
   | '|=' #assignmentoperator11
   ;

expression
   : assignmentexpression #expression1
   | expression ',' assignmentexpression #expression2
   ;

constantexpression
   : conditionalexpression
   ;


/*Statements*/
statement
   : labeledstatement #statement1
   | attributespecifierseq? expressionstatement #statement2
   | attributespecifierseq? compoundstatement #statement3
   | attributespecifierseq? selectionstatement #statement4
   | attributespecifierseq? iterationstatement #statement5
   | attributespecifierseq? jumpstatement #statement6
   | declarationstatement #statement7
   | attributespecifierseq? tryblock #statement8
   ;

labeledstatement
   : attributespecifierseq? Identifier ':' statement #labeledstatement1
   | attributespecifierseq? Case constantexpression ':' statement #labeledstatement2
   | attributespecifierseq? Default ':' statement #labeledstatement3
   ;

expressionstatement
   : expression? ';'
   ;

compoundstatement
   : '{' statementseq? '}'
   ;

statementseq
   : statement #statementseq1
   | statementseq statement #statementseq2
   ;

selectionstatement
   : If '(' condition ')' statement #selectionstatement1
   | If '(' condition ')' statement Else statement #selectionstatement2
   | Switch '(' condition ')' statement #selectionstatement3
   ;

condition
   : expression #condition1
   | attributespecifierseq? declspecifierseq declarator '=' initializerclause #condition2
   | attributespecifierseq? declspecifierseq declarator bracedinitlist #condition3
   ;

iterationstatement
   : While '(' condition ')' statement #iterationstatement1
   | Do statement While '(' expression ')' ';' #iterationstatement2
   | For '(' forinitstatement condition? ';' expression? ')' statement #iterationstatement3
   | For '(' forrangedeclaration ':' forrangeinitializer ')' statement #iterationstatement4
   ;

forinitstatement
   : expressionstatement #forinitstatement1
   | simpledeclaration #forinitstatement2
   ;

forrangedeclaration
   : attributespecifierseq? declspecifierseq declarator
   ;

forrangeinitializer
   : expression #forrangeinitializer1
   | bracedinitlist #forrangeinitialize2
   ;

jumpstatement
   : Break ';' #jumpstatement1
   | Continue ';' #jumpstatement2
   | Return expression? ';' #jumpstatement3
   | Return bracedinitlist ';' #jumpstatement4
   | Goto Identifier ';' #jumpstatement5
   ;

declarationstatement
   : blockdeclaration
   ;


/*Declarations*/
declarationseq
   : declaration #declarationseq1
   | declarationseq declaration #declarationseq2
   ;

declaration
   : blockdeclaration #declaration1
   | functiondefinition #declaration2
   | templatedeclaration #declaration3
   | explicitinstantiation #declaration4
   | explicitspecialization #declaration5
   | linkagespecification #declaration6
   | namespacedefinition #declaration7
   | emptydeclaration #declaration8
   | attributedeclaration #declaration9
   ;

blockdeclaration
   : simpledeclaration #blockdeclaration1
   | asmdefinition #blockdeclaration2
   | namespacealiasdefinition #blockdeclaration3
   | usingdeclaration #blockdeclaration4
   | usingdirective #blockdeclaration5
   | static_assertdeclaration #blockdeclaration6
   | aliasdeclaration #blockdeclaration7
   | opaqueenumdeclaration #blockdeclaration8
   ;

aliasdeclaration
   : Using Identifier attributespecifierseq? '=' thetypeid ';'
   ;

simpledeclaration
   : declspecifierseq? initdeclaratorlist? ';' #simpledeclaration1
   | attributespecifierseq declspecifierseq? initdeclaratorlist ';' #simpledeclaration2
   ;

static_assertdeclaration
   : Static_assert '(' constantexpression ',' Stringliteral ')' ';'
   ;

emptydeclaration
   : ';'
   ;

attributedeclaration
   : attributespecifierseq ';'
   ;

declspecifier
   : storageclassspecifier #declspecifier1
   | typespecifier #declspecifier2
   | functionspecifier #declspecifier3
   | Friend #declspecifier4
   | Typedef #declspecifier5
   | Constexpr #declspecifier6
   ;

declspecifierseq
   : declspecifier attributespecifierseq? #declspecifierseq1
   | declspecifier declspecifierseq #declspecifierseq2
   ;

storageclassspecifier
   : Register #storageclassspecifier1
   | Static #storageclassspecifier2
   | Thread_local #storageclassspecifier3
   | Extern #storageclassspecifier4
   | Mutable #storageclassspecifier5
   ;

functionspecifier
   : Inline #functionspecifier1
   | Virtual #functionspecifier2
   | Explicit #functionspecifier3
   ;

typedefname
   : Identifier
   ;

typespecifier
   : trailingtypespecifier #typespecifier1
   | classspecifier #typespecifier2
   | enumspecifier #typespecifier3
   ;

trailingtypespecifier
   : simpletypespecifier #trailingtypespecifier1
   | elaboratedtypespecifier #trailingtypespecifier2
   | typenamespecifier #trailingtypespecifier3
   | cvqualifier #trailingtypespecifier4
   ;

typespecifierseq
   : typespecifier attributespecifierseq? #typespecifierseq1
   | typespecifier typespecifierseq #typespecifierseq2
   ;

trailingtypespecifierseq
   : trailingtypespecifier attributespecifierseq? #trailingtypespecifierseq1
   | trailingtypespecifier trailingtypespecifierseq #trailingtypespecifierseq2
   ;

simpletypespecifier
   : nestednamespecifier? thetypename #simpletypespecifier1
   | nestednamespecifier Template simpletemplateid #simpletypespecifier2
   | Char #simpletypespecifier3
   | Char16 #simpletypespecifier4
   | Char32 #simpletypespecifier5
   | Wchar #simpletypespecifier6
   | Bool #simpletypespecifier7
   | Short  #simpletypespecifier8
   | Int  #simpletypespecifier9
   | Long  #simpletypespecifier10
   | Signed  #simpletypespecifier11
   | Unsigned  #simpletypespecifier12
   | Float  #simpletypespecifier13
   | Double  #simpletypespecifier14
   | Void  #simpletypespecifier15
   | Auto  #simpletypespecifier16
   | decltypespecifier  #simpletypespecifier17
   ;

thetypename
   : classname #thetypename1
   | enumname #thetypename2
   | typedefname #thetypename3
   | simpletemplateid #thetypename4
   ;

decltypespecifier
   : Decltype '(' expression ')' #decltypespecifier1
   | Decltype '(' Auto ')' #decltypespecifier2
   ;

elaboratedtypespecifier
   : classkey attributespecifierseq? nestednamespecifier? Identifier #elaboratedtypespecifier1
   | classkey simpletemplateid #elaboratedtypespecifier2
   | classkey nestednamespecifier Template? simpletemplateid #elaboratedtypespecifier3
   | Enum nestednamespecifier? Identifier #elaboratedtypespecifier4
   ;

enumname
   : Identifier
   ;

enumspecifier
   : enumhead '{' enumeratorlist? '}' #enumspecifier1
   | enumhead '{' enumeratorlist ',' '}' #enumspecifier2
   ;

enumhead
   : enumkey attributespecifierseq? Identifier? enumbase? #enumhead1
   | enumkey attributespecifierseq? nestednamespecifier Identifier enumbase? #enumhead2
   ;

opaqueenumdeclaration
   : enumkey attributespecifierseq? Identifier enumbase? ';'
   ;

enumkey
   : Enum #enumkey1
   | Enum Class #enumkey2
   | Enum Struct #enumkey3
   ;

enumbase
   : ':' typespecifierseq
   ;

enumeratorlist
   : enumeratordefinition #enumeratorlist1
   | enumeratorlist ',' enumeratordefinition #enumeratorlist2
   ;

enumeratordefinition
   : enumerator #enumeratordefinition1
   | enumerator '=' constantexpression #enumeratordefinition2
   ;

enumerator
   : Identifier
   ;

namespacename
   : originalnamespacename #namespacename1
   | namespacealias #namespacename2
   ;

originalnamespacename
   : Identifier
   ;

namespacedefinition
   : namednamespacedefinition #namespacedefinition1
   | unnamednamespacedefinition #namespacedefinition2
   ;

namednamespacedefinition
   : originalnamespacedefinition #namednamespacedefinition1
   | extensionnamespacedefinition #namednamespacedefinition2
   ;

originalnamespacedefinition
   : Inline? Namespace Identifier '{' namespacebody '}'
   ;

extensionnamespacedefinition
   : Inline? Namespace originalnamespacename '{' namespacebody '}'
   ;

unnamednamespacedefinition
   : Inline? Namespace '{' namespacebody '}'
   ;

namespacebody
   : declarationseq?
   ;

namespacealias
   : Identifier
   ;

namespacealiasdefinition
   : Namespace Identifier '=' qualifiednamespacespecifier ';'
   ;

qualifiednamespacespecifier
   : nestednamespecifier? namespacename
   ;

usingdeclaration
   : Using Typename_? nestednamespecifier unqualifiedid ';' #usingdeclaration1
   | Using '::' unqualifiedid ';' #usingdeclaration2
   ;

usingdirective
   : attributespecifierseq? Using Namespace nestednamespecifier? namespacename ';'
   ;

asmdefinition
   : Asm '(' Stringliteral ')' ';'
   ;

linkagespecification
   : Extern Stringliteral '{' declarationseq? '}' #linkagespecification1
   | Extern Stringliteral declaration #linkagespecification2
   ;

attributespecifierseq
   : attributespecifier #attributespecifierseq1
   | attributespecifierseq attributespecifier #attributespecifierseq2
   ;

attributespecifier
   : '[' '[' attributelist ']' ']' #attributespecifier1
   | alignmentspecifier #attributespecifier2
   ;

alignmentspecifier
   : Alignas '(' thetypeid '...'? ')' #alignmentspecifier1
   | Alignas '(' constantexpression '...'? ')' #alignmentspecifier2
   ;

attributelist
   : attribute? #attributelist1
   | attributelist ',' attribute? #attributelist2
   | attribute '...' #attributelist3
   | attributelist ',' attribute '...' #attributelist4
   ;

attribute
   : attributetoken attributeargumentclause?
   ;

attributetoken
   : Identifier #attributetoken1
   | attributescopedtoken #attributetoken2
   ;

attributescopedtoken
   : attributenamespace '::' Identifier
   ;

attributenamespace
   : Identifier
   ;

attributeargumentclause
   : '(' balancedtokenseq ')'
   ;

balancedtokenseq
   : balancedtoken? #balancedtokenseq1
   | balancedtokenseq balancedtoken #balancedtokenseq2
   ;

balancedtoken
   : '(' balancedtokenseq ')' #balancedtoken1
   | '[' balancedtokenseq ']' #balancedtoken2
   | '{' balancedtokenseq '}' #balancedtoken3
   | ~('('|')'|'{'|'}'|'['|']')+ #balancedtoken4
   ;


/*Declarators*/
initdeclaratorlist
   : initdeclarator #initdeclaratorlist1
   | initdeclaratorlist ',' initdeclarator #initdeclaratorlist2
   ;

initdeclarator
   : declarator initializer?
   ;

declarator
   : ptrdeclarator #declarator1
   | noptrdeclarator parametersandqualifiers trailingreturntype #declarator2
   ;

ptrdeclarator
   : noptrdeclarator #ptrdeclarator1
   | ptroperator ptrdeclarator #ptrdeclarator2
   ;

noptrdeclarator
   : declaratorid attributespecifierseq? #noptrdeclarator1
   | noptrdeclarator parametersandqualifiers #noptrdeclarator2
   | noptrdeclarator '[' constantexpression? ']' attributespecifierseq? #noptrdeclarator3
   | '(' ptrdeclarator ')' #noptrdeclarator4
   ;

parametersandqualifiers
   : '(' parameterdeclarationclause ')' cvqualifierseq? refqualifier? exceptionspecification? attributespecifierseq?
   ;

trailingreturntype
   : '->' trailingtypespecifierseq abstractdeclarator?
   ;

ptroperator
   : '*' attributespecifierseq? cvqualifierseq? #ptroperator1
   | '&' attributespecifierseq? #ptroperator2
   | '&&' attributespecifierseq? #ptroperator3
   | nestednamespecifier '*' attributespecifierseq? cvqualifierseq? #ptroperato4
   ;

cvqualifierseq
   : cvqualifier cvqualifierseq?
   ;

cvqualifier
   : Const #cvqualifier1
   | Volatile #cvqualifier2
   ;

refqualifier
   : '&' #refqualifier1
   | '&&' #refqualifier2
   ;

declaratorid
   : '...'? idexpression
   ;

thetypeid
   : typespecifierseq abstractdeclarator?
   ;

abstractdeclarator
   : ptrabstractdeclarator #abstractdeclarator1
   | noptrabstractdeclarator? parametersandqualifiers trailingreturntype #abstractdeclarator2
   | abstractpackdeclarator #abstractdeclarator3
   ;

ptrabstractdeclarator
   : noptrabstractdeclarator #ptrabstractdeclarator1
   | ptroperator ptrabstractdeclarator? #ptrabstractdeclarator2
   ;

noptrabstractdeclarator
   : noptrabstractdeclarator parametersandqualifiers #noptrabstractdeclarator1
   | parametersandqualifiers #noptrabstractdeclarator2
   | noptrabstractdeclarator '[' constantexpression? ']' attributespecifierseq? #noptrabstractdeclarator3
   | '[' constantexpression? ']' attributespecifierseq? #noptrabstractdeclarator4
   | '(' ptrabstractdeclarator ')' #noptrabstractdeclarator5
   ;

abstractpackdeclarator
   : noptrabstractpackdeclarator #abstractpackdeclarator1
   | ptroperator abstractpackdeclarator #abstractpackdeclarator2
   ;

noptrabstractpackdeclarator
   : noptrabstractpackdeclarator parametersandqualifiers  #noptrabstractpackdeclarator1
   | noptrabstractpackdeclarator '[' constantexpression? ']' attributespecifierseq? #noptrabstractpackdeclarator2
   | '...' #noptrabstractpackdeclarator3
   ;

parameterdeclarationclause
   : parameterdeclarationlist? '...'? #parameterdeclarationclause1
   | parameterdeclarationlist ',' '...' #parameterdeclarationclause2
   ;

parameterdeclarationlist
   : parameterdeclaration #parameterdeclarationlist1
   | parameterdeclarationlist ',' parameterdeclaration #parameterdeclarationlist2
   ;

parameterdeclaration
   : attributespecifierseq? declspecifierseq declarator #parameterdeclaration1
   | attributespecifierseq? declspecifierseq declarator '=' initializerclause #parameterdeclaration2
   | attributespecifierseq? declspecifierseq abstractdeclarator? #parameterdeclaration3
   | attributespecifierseq? declspecifierseq abstractdeclarator? '=' initializerclause #parameterdeclaration4
   ;

functiondefinition
   : attributespecifierseq? declspecifierseq? declarator virtspecifierseq? functionbody
   ;

functionbody
   : ctorinitializer? compoundstatement #functionbody1
   | functiontryblock #functionbody2
   | '=' Default ';' #functionbody3
   | '=' Delete ';' #functionbody4
   ;

initializer
   : braceorequalinitializer #initializer1
   | '(' expressionlist ')' #initializer2
   ;

braceorequalinitializer
   : '=' initializerclause #braceorequalinitializer1
   | bracedinitlist #braceorequalinitializer2
   ;

initializerclause
   : assignmentexpression #initializerclause1
   | bracedinitlist #initializerclause2
   ;

initializerlist
   : initializerclause '...'? #initializerlist1
   | initializerlist ',' initializerclause '...'? #initializerlist2
   ;

bracedinitlist
   : '{' initializerlist ','? '}' #bracedinitlist1
   | '{' '}' #bracedinitlist2
   ;


/*Classes*/
classname
   : Identifier #classname1
   | simpletemplateid #classname2
   ;

classspecifier
   : classhead '{' memberspecification? '}'
   ;

classhead
   : classkey attributespecifierseq? classheadname classvirtspecifier? baseclause? #classhead1
   | classkey attributespecifierseq? baseclause? #classhead2
   ;

classheadname
   : nestednamespecifier? classname
   ;

classvirtspecifier
   : Final
   ;

classkey
   : Class #classkey1
   | Struct #classkey2
   | Union #classkey3
   ;

memberspecification
   : memberdeclaration memberspecification? #memberspecification1
   | accessspecifier ':' memberspecification? #memberspecification2
   ;

memberdeclaration
   : attributespecifierseq? declspecifierseq? memberdeclaratorlist? ';' #memberdeclaration1
   | functiondefinition #memberdeclaration2
   | usingdeclaration #memberdeclaration3
   | static_assertdeclaration #memberdeclaration4
   | templatedeclaration #memberdeclaration5
   | aliasdeclaration #memberdeclaration6
   | emptydeclaration #memberdeclaration7
   ;

memberdeclaratorlist
   : memberdeclarator #memberdeclaratorlis1
   | memberdeclaratorlist ',' memberdeclarator #memberdeclaratorlis2
   ;

memberdeclarator
   : declarator virtspecifierseq? purespecifier? #memberdeclarator1
   | declarator braceorequalinitializer? #memberdeclarator2
   | Identifier? attributespecifierseq? ':' constantexpression #memberdeclarator3
   ;

virtspecifierseq
   : virtspecifier #virtspecifierseq1
   | virtspecifierseq virtspecifier #virtspecifierseq2
   ;

virtspecifier
   : Override #virtspecifier1
   | Final #virtspecifier2
   ;


purespecifier
   : Assign val = Octalliteral
   ;


/*Derived classes*/
baseclause
   : ':' basespecifierlist
   ;

basespecifierlist
   : basespecifier '...'? #basespecifierlist1
   | basespecifierlist ',' basespecifier '...'? #basespecifierlist2
   ;

basespecifier
   : attributespecifierseq? basetypespecifier #basespecifier1
   | attributespecifierseq? Virtual accessspecifier? basetypespecifier #basespecifier2
   | attributespecifierseq? accessspecifier Virtual? basetypespecifier #basespecifier3
   ;

classordecltype
   : nestednamespecifier? classname #classordecltype1
   | decltypespecifier #classordecltype2
   ;

basetypespecifier
   : classordecltype
   ;

accessspecifier
   : Private #accessspecifier1
   | Protected #accessspecifier2
   | Public #accessspecifier3
   ;


/*Special member functions*/
conversionfunctionid
   : Operator conversiontypeid
   ;

conversiontypeid
   : typespecifierseq conversiondeclarator?
   ;

conversiondeclarator
   : ptroperator conversiondeclarator?
   ;

ctorinitializer
   : ':' meminitializerlist
   ;

meminitializerlist
   : meminitializer '...'? #meminitializerlist1
   | meminitializer '...'? ',' meminitializerlist #meminitializerlist2
   ;

meminitializer
   : meminitializerid '(' expressionlist? ')' #meminitializer1
   | meminitializerid bracedinitlist #meminitializer2
   ;

meminitializerid
   : classordecltype #meminitializerid1
   | Identifier #meminitializerid2
   ;


/*Overloading*/
operatorfunctionid
   : Operator theoperator
   ;

literaloperatorid
   : Operator Stringliteral Identifier #literaloperatorid1
   | Operator Userdefinedstringliteral #literaloperatorid2
   ;


/*Templates*/
templatedeclaration
   : Template '<' templateparameterlist '>' declaration
   ;

templateparameterlist
   : templateparameter #templateparameterlist1
   | templateparameterlist ',' templateparameter #templateparameterlist2
   ;

templateparameter
   : typeparameter #templateparameter1
   | parameterdeclaration #templateparameter2
   ;

typeparameter
   : Class '...'? Identifier? #typeparameter1
   | Class Identifier? '=' thetypeid #typeparameter2
   | Typename_ '...'? Identifier? #typeparameter3
   | Typename_ Identifier? '=' thetypeid #typeparameter4
   | Template '<' templateparameterlist '>' Class '...'? Identifier? #typeparameter5
   | Template '<' templateparameterlist '>' Class Identifier? '=' idexpression #typeparameter6
   ;

simpletemplateid
   : templatename '<' templateargumentlist? '>'
   ;

templateid
   : simpletemplateid #templateid1
   | operatorfunctionid '<' templateargumentlist? '>' #templateid2
   | literaloperatorid '<' templateargumentlist? '>' #templateid3
   ;

templatename
   : Identifier
   ;

templateargumentlist
   : templateargument '...'? #templateargumentlist1
   | templateargumentlist ',' templateargument '...'? #templateargumentlist2
   ;

templateargument
   : thetypeid #templateargument1
   | constantexpression #templateargument2
   | idexpression #templateargument3
   ;

typenamespecifier
   : Typename_ nestednamespecifier Identifier #typenamespecifier1
   | Typename_ nestednamespecifier Template? simpletemplateid #typenamespecifier2
   ;

explicitinstantiation
   : Extern? Template declaration
   ;

explicitspecialization
   : Template '<' '>' declaration
   ;


/*Exception handling*/
tryblock
   : Try compoundstatement handlerseq
   ;

functiontryblock
   : Try ctorinitializer? compoundstatement handlerseq
   ;

handlerseq
   : handler handlerseq?
   ;

handler
   : Catch '(' exceptiondeclaration ')' compoundstatement
   ;

exceptiondeclaration
   : attributespecifierseq? typespecifierseq declarator #exceptiondeclaration1
   | attributespecifierseq? typespecifierseq abstractdeclarator? #exceptiondeclaration2
   | '...' #exceptiondeclaration3
   ;

throwexpression
   : Throw assignmentexpression?
   ;

exceptionspecification
   : dynamicexceptionspecification #exceptionspecification1
   | noexceptspecification #exceptionspecification2
   ;

dynamicexceptionspecification
   : Throw '(' typeidlist? ')'
   ;

typeidlist
   : thetypeid '...'? #typeidlist1
   | typeidlist ',' thetypeid '...'? #typeidlist2
   ;

noexceptspecification
   : Noexcept '(' constantexpression ')' #noexceptspecification1
   | Noexcept #noexceptspecification2
   ;


/*Preprocessing directives*/
MultiLineMacro
   : '#' (~ [\n]*? '\\' '\r'? '\n')+ ~ [\n]+ -> channel (HIDDEN)
   ;

Directive
   : '#' ~ [\n]* -> channel (HIDDEN)
   ;


/**Lexer**/

/*Keywords = 75 different Keywords*/
Alignas
   : 'alignas'
   ;

Alignof
   : 'alignof'
   ;

Asm
   : 'asm'
   ;

Auto
   : 'auto'
   ;

Bool
   : 'bool'
   ;

Break
   : 'break'
   ;

Case
   : 'case'
   ;

Catch
   : 'catch'
   ;

Char
   : 'char'
   ;

Char16
   : 'char16_t'
   ;

Char32
   : 'char32_t'
   ;

Class
   : 'class'
   ;

Const
   : 'const'
   ;

Constexpr
   : 'constexpr'
   ;

Const_cast
   : 'const_cast'
   ;

Continue
   : 'continue'
   ;

Decltype
   : 'decltype'
   ;

Default
   : 'default'
   ;

Delete
   : 'delete'
   ;

Do
   : 'do'
   ;

Double
   : 'double'
   ;

Dynamic_cast
   : 'dynamic_cast'
   ;

Else
   : 'else'
   ;

Enum
   : 'enum'
   ;

Explicit
   : 'explicit'
   ;

Export
   : 'export'
   ;

Extern
   : 'extern'
   ;

False1
   : 'false'
   ;

Final
   : 'final'
   ;

Float
   : 'float'
   ;

For
   : 'for'
   ;

Friend
   : 'friend'
   ;

Goto
   : 'goto'
   ;

If
   : 'if'
   ;

Inline
   : 'inline'
   ;

Int
   : 'int'
   ;

Long
   : 'long'
   ;

Mutable
   : 'mutable'
   ;

Namespace
   : 'namespace'
   ;

New
   : 'new'
   ;

Noexcept
   : 'noexcept'
   ;

Nullptr
   : 'nullptr'
   ;

Operator
   : 'operator'
   ;

Override
   : 'override'
   ;

Private
   : 'private'
   ;

Protected
   : 'protected'
   ;

Public
   : 'public'
   ;

Register
   : 'register'
   ;

Reinterpret_cast
   : 'reinterpret_cast'
   ;

Return
   : 'return'
   ;

Short
   : 'short'
   ;

Signed
   : 'signed'
   ;

Sizeof
   : 'sizeof'
   ;

Static
   : 'static'
   ;

Static_assert
   : 'static_assert'
   ;

Static_cast
   : 'static_cast'
   ;

Struct
   : 'struct'
   ;

Switch
   : 'switch'
   ;

Template
   : 'template'
   ;

This
   : 'this'
   ;

Thread_local
   : 'thread_local'
   ;

Throw
   : 'throw'
   ;

True1
   : 'true'
   ;

Try
   : 'try'
   ;

Typedef
   : 'typedef'
   ;

Typeid_
   : 'typeid'
   ;

Typename_
   : 'typename'
   ;

Union
   : 'union'
   ;

Unsigned
   : 'unsigned'
   ;

Using
   : 'using'
   ;

Virtual
   : 'virtual'
   ;

Void
   : 'void'
   ;

Volatile
   : 'volatile'
   ;

Wchar
   : 'wchar_t'
   ;

While
   : 'while'
   ;


/*Operators*/
LeftParen
   : '('
   ;

RightParen
   : ')'
   ;

LeftBracket
   : '['
   ;

RightBracket
   : ']'
   ;

LeftBrace
   : '{'
   ;

RightBrace
   : '}'
   ;

Plus
   : '+'
   ;

Minus
   : '-'
   ;

Star
   : '*'
   ;

Div
   : '/'
   ;

Mod
   : '%'
   ;

Caret
   : '^'
   ;

And
   : '&'
   ;

Or
   : '|'
   ;

Tilde
   : '~'
   ;

Not
   : '!'
   | 'not'
   ;

Assign
   : '='
   ;

Less
   : '<'
   ;

Greater
   : '>'
   ;

PlusAssign
   : '+='
   ;

MinusAssign
   : '-='
   ;

StarAssign
   : '*='
   ;

DivAssign
   : '/='
   ;

ModAssign
   : '%='
   ;

XorAssign
   : '^='
   ;

AndAssign
   : '&='
   ;

OrAssign
   : '|='
   ;

LeftShift
   : '<<'
   ;

RightShift
   :
   '>>'
   ;

LeftShiftAssign
   : '<<='
   ;

RightShiftAssign
   :
   '>>='
   ;

Equal
   : '=='
   ;

NotEqual
   : '!='
   ;

LessEqual
   : '<='
   ;

GreaterEqual
   : '>='
   ;

AndAnd
   : '&&'
   | 'and'
   ;

OrOr
   : '||'
   | 'or'
   ;

PlusPlus
   : '++'
   ;

MinusMinus
   : '--'
   ;

Comma
   : ','
   ;

ArrowStar
   : '->*'
   ;

Arrow
   : '->'
   ;

Question
   : '?'
   ;

Colon
   : ':'
   ;

Doublecolon
   : '::'
   ;

Semi
   : ';'
   ;

Dot
   : '.'
   ;

DotStar
   : '.*'
   ;

Ellipsis
   : '...'
   ;

theoperator
   : New #theoperator1
   | Delete  #theoperator2
   | New '[' ']'  #theoperator3
   | Delete '[' ']'  #theoperator4
   | '+' #theoperator5
   | '-' #theoperator6
   | '*' #theoperator7
   | '/' #theoperator8
   | '%' #theoperator9
   | '^' #theoperator10
   | '&' #theoperator11
   | '|' #theoperator12
   | '~' #theoperator13
   | '!' #theoperator14
   | 'not' #theoperator15
   | '=' #theoperator16
   | '<' #theoperator17
   | '>' #theoperator18
   | '+=' #theoperator19
   | '-=' #theoperator20
   | '*=' #theoperator21
   | '/=' #theoperator22
   | '%=' #theoperator23
   | '^=' #theoperator24
   | '&=' #theoperator25
   | '|=' #theoperator26
   | LeftShift #theoperator27
   | RightShift #theoperator28
   | RightShiftAssign #theoperator29
   | LeftShiftAssign #theoperator30
   | '==' #theoperator31
   | '!=' #theoperator32
   | '<=' #theoperator33
   | '>=' #theoperator34
   | '&&' #theoperator35
   | 'and' #theoperator36
   | '||' #theoperator37
   | 'or' #theoperator38
   | '++' #theoperator39
   | '--' #theoperator40
   | ',' #theoperator41
   | '->*' #theoperator42
   | '->' #theoperator43
   | '(' ')' #theoperator44
   | '[' ']' #theoperator45
   ;


/*Fragments*/
Identifier
   : Identifiernondigit (Identifiernondigit | DIGIT)*
   ;

fragment Identifiernondigit
   : NONDIGIT
   | Universalcharactername
   ;

fragment NONDIGIT
   : [a-zA-Z_]
   ;

fragment DIGIT
   : [0-9]
   ;

fragment Hexquad
   : HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT
   ;

fragment Universalcharactername
   : '\\u' Hexquad
   | '\\U' Hexquad Hexquad
   ;


literal
   : Integerliteral #literal1
   | Characterliteral #literal2
   | Floatingliteral #literal3
   | Stringliteral #literal4
   | booleanliteral #literal5
   | pointerliteral #literal6
   | userdefinedliteral #literal7
   ;

Integerliteral
   : Decimalliteral Integersuffix?
   | Octalliteral Integersuffix?
   | Hexadecimalliteral Integersuffix?
   | Binaryliteral Integersuffix?
   ;

Decimalliteral
   : NONZERODIGIT ('\''? DIGIT)*
   ;

Octalliteral
   : '0' ('\''? OCTALDIGIT)*
   ;

Hexadecimalliteral
   : ('0x' | '0X') HEXADECIMALDIGIT ('\''? HEXADECIMALDIGIT)*
   ;

Binaryliteral
   : ('0b' | '0B') BINARYDIGIT ('\''? BINARYDIGIT)*
   ;

fragment NONZERODIGIT
   : [1-9]
   ;

fragment OCTALDIGIT
   : [0-7]
   ;

fragment HEXADECIMALDIGIT
   : [0-9a-fA-F]
   ;

fragment BINARYDIGIT
   : [01]
   ;

Integersuffix
   : Unsignedsuffix Longsuffix?
   | Unsignedsuffix Longlongsuffix?
   | Longsuffix Unsignedsuffix?
   | Longlongsuffix Unsignedsuffix?
   ;

fragment Unsignedsuffix
   : [uU]
   ;

fragment Longsuffix
   : [lL]
   ;

fragment Longlongsuffix
   : 'll'
   | 'LL'
   ;

Characterliteral
   : '\'' Cchar+ '\''
   | 'u' '\'' Cchar+ '\''
   | 'U' '\'' Cchar+ '\''
   | 'L' '\'' Cchar+ '\''
   ;

fragment Cchar
   : ~ ['\\\r\n]
   | Escapesequence
   | Universalcharactername
   ;

fragment Escapesequence
   : Simpleescapesequence
   | Octalescapesequence
   | Hexadecimalescapesequence
   ;

fragment Simpleescapesequence
   : '\\\''
   | '\\"'
   | '\\?'
   | '\\\\'
   | '\\a'
   | '\\b'
   | '\\f'
   | '\\n'
   | '\\r'
   | '\\t'
   | '\\v'
   ;

fragment Octalescapesequence
   : '\\' OCTALDIGIT
   | '\\' OCTALDIGIT OCTALDIGIT
   | '\\' OCTALDIGIT OCTALDIGIT OCTALDIGIT
   ;

fragment Hexadecimalescapesequence
   : '\\x' HEXADECIMALDIGIT+
   ;

Floatingliteral
   : Fractionalconstant Exponentpart? Floatingsuffix?
   | Digitsequence Exponentpart Floatingsuffix?
   ;

fragment Fractionalconstant
   : Digitsequence? '.' Digitsequence
   | Digitsequence '.'
   ;

fragment Exponentpart
   : 'e' SIGN? Digitsequence
   | 'E' SIGN? Digitsequence
   ;

fragment SIGN
   : [+-]
   ;

fragment Digitsequence
   : DIGIT ('\''? DIGIT)*
   ;

fragment Floatingsuffix
   : [flFL]
   ;

Stringliteral
   : Encodingprefix? '"' Schar* '"'
   | Encodingprefix? 'R' Rawstring
   ;

fragment Encodingprefix
   : 'u8'
   | 'u'
   | 'U'
   | 'L'
   ;

fragment Schar
   : ~ ["\\\r\n]
   | Escapesequence
   | Universalcharactername
   ;

fragment Rawstring
   : '"' .*? '(' .*? ')' .*? '"'
   ;

booleanliteral
   : False1 #booleanliteral1
   | True1 #booleanliteral2
   ;

pointerliteral
   : Nullptr
   ;

userdefinedliteral
   : Userdefinedintegerliteral #userdefinedliteral1
   | Userdefinedfloatingliteral #userdefinedliteral2
   | Userdefinedstringliteral #userdefinedliteral3
   | Userdefinedcharacterliteral #userdefinedliteral4
   ;

Userdefinedintegerliteral
   : Decimalliteral Udsuffix
   | Octalliteral Udsuffix
   | Hexadecimalliteral Udsuffix
   | Binaryliteral Udsuffix
   ;

Userdefinedfloatingliteral
   : Fractionalconstant Exponentpart? Udsuffix
   | Digitsequence Exponentpart Udsuffix
   ;

Userdefinedstringliteral
   : Stringliteral Udsuffix
   ;

Userdefinedcharacterliteral
   : Characterliteral Udsuffix
   ;

fragment Udsuffix
   : Identifier
   ;

Whitespace
   : [ \t]+ -> channel(HIDDEN)
   ;

Newline
   : ('\r' '\n'? | '\n') -> channel(HIDDEN)
   ;

BlockComment
   : '/*' .*? '*/' -> channel(HIDDEN)
   ;

LineComment
   : '//' ~ [\r\n]* -> channel(HIDDEN)
   ;
