# SmartCalc

Implementation of SmartCalc

## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
   2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
   3.1. [Part 1](#part-1-implementation-of-smartcalc-v20)


## Information

Note that you should use *Dijkstra's algorithm* to translate expressions into *reverse Polish notation* to implement the calculator. You can find all the necessary information in the SmartCalc v1.0 project description to refresh your knowledge.

### MVC pattern

The Model-View-Controller (MVC) pattern is a scheme for separating application modules into three macro components: a model that contains the business logic, a view that is a UI form for interacting with the program, and a controller that modifies the model by user action.

The concept of MVC was introduced in 1978 by Trygve Reenskaug, who was working on the Smalltalk programming language at Xerox PARC. Later, Steve Burbeck implemented the pattern in Smalltalk-80.
The final version of the MVC concept was published in Technology Object in 1988. The MVC pattern continued to evolve, giving rise to variants such as HMVC, MVA, MVVM.

The primary need for this pattern stems from developers' desire to separate the business logic of the program from the views, making it easier to replace views and reuse logic once implemented in other environments. Having a model separate from the view, and a controller to interact with it, allows you to reuse or modify code you have already written more efficiently.

The model stores and accesses the main data, performs operations on requests defined by the business logic of the program, i.e. it is responsible for the part of the program that handles all the algorithms and information processing. These models, modified by the controller, affect the display of information on the user interface. The model in this programme should be the class library that performs the calculations. This library must provide all the necessary classes and methods to perform them. And this is the business logic of the program, because it provides the means to solve the problem.

A controller is a thin macro component that performs model modifications. It is used to generate requests to the model. In code, it looks like a kind of "facade" for the model, that is, a set of methods that already work directly with the model. It is called thin because the ideal controller contains no additional logic other than calling one or more methods of the model. The controller acts as a link between the interface and the model. This allows the model to be completely encapsulated from the representation. This separation is helpful in that it allows the view code to know nothing about the model code and to address only the controller, whose interface of the provided functions is unlikely to change much. The model, on the other hand, can change significantly, and if you "move" to other algorithms, technologies, or even programming languages in the model, only a small piece of code in the controller directly related to the model needs to be changed. Otherwise, it would probably be necessary to rewrite a significant part of the interface code, as it would depend very much on the implementation of the model. So when the user interacts with the interface, they call controller methods that modify the model.

The view contains all the code associated with the programme interface. An ideal interface code should not contain any business logic. It just provides the form for interacting with the user.


## Chapter III

## Part 1. Implementation of SmartCalc v2.0

You need to implement the SmartCalc v2.0:

- The program must be developed in C++ language of C++17 standard;
- The program code must be located in the src folder;
- When writing code it is necessary to follow the Google style;
- Classes must be implemented within the `s21` namespace;
- Prepare full coverage of expression calculation modules with unit-tests using the GTest library;
- The program must be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. Installation directory could be arbitrary;
- GUI implementation, based on any GUI library with API for C++17:
  * For Linux: GTK+, CEF, Qt, JUCE;
  * For Mac: GTK+, CEF, Qt, JUCE, SFML, Nanogui, Nngui;
- The program must be implemented using the MVC pattern, and also:
   - there should be no business logic code in the view code;
   - there should be no interface code in the controller and the model;
   - controllers must be thin;
- Both integers and real numbers with a dot can be input into the program. You should provide the input of numbers in exponential notation;
- The calculation must be done after you complete entering the calculating expression and press the `=` symbol;
- Calculating arbitrary bracketed arithmetic expressions in infix notation;
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable _x_ as a number;
- Plotting a graph of a function given by an expression in infix notation with the variable _x_ (with coordinate axes, mark of the used scale and an adaptive grid);
   - It is not necessary to provide the user with the ability to change the scale;
- Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000;
   - To plot a graph of a function it is necessary to additionally specify the displayed domain and codomain;
- Verifiable accuracy of the fractional part is at least to 7 decimal places;
- Users must be able to enter up to 255 characters;
- Bracketed arithmetic expressions in infix notation must support the following arithmetic operations and mathematical functions:
   - **Arithmetic operators**:
     | Operator name | Infix notation <br /> (Classic) | Prefix notation <br /> (Polish notation) |  Postfix notation <br /> (Reverse Polish notation) |
      | --------- | ------ | ------ | ------ |
      | Brackets | (a + b) | (+ a b) | a b + |
      | Addition | a + b | + a b | a b + |
      | Subtraction | a - b | - a b | a b - |
      | Multiplication | a * b | * a b | a b * |
      | Division | a / b | / a b | a b \ |
      | Power | a ^ b | ^ a b | a b ^ |
      | Modulus | a mod b | mod a b | a b mod |
      | Unary plus | +a | +a | a+ |
      | Unary minus | -a | -a | a- |
      >Note that the multiplication operator contains the obligatory sign `*`. Processing an expression with the omitted `*` sign is optional and is left to the developer's decision.
   - **Functions**:
      | Function description | Function |
      | ------ | ------ |
      | Computes cosine | cos(x) |
      | Computes sine | sin(x) |
      | Computes tangent | tan(x) |
      | Computes arc cosine | acos(x) |
      | Computes arc sine | asin(x) |
      | Computes arc tangent | atan(x) |
      | Computes square root | sqrt(x) |
      | Computes natural logarithm | ln(x) |
      | Computes common logarithm | log(x) |

