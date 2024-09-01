// name: Masa Ahmad Ali Jalamneh
// id number: 1212145
// section number: 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 100
#include <ctype.h>
#include <math.h>
#define MAX_SIZE 100

//////////
// Structure to represent an equation, will be used to store each equation read from the file. (dynamic array)
typedef struct Equation
{
    char equation[100];// length of each equation
} Equation;

//////////
// Structure to represent an equation, will be used to store each prefix (expression) equation  converted through the infixToPrefix function. (dynamic array)
typedef struct preEquation
{
    char preequation[100];// length of each equation
} preEquation;

/////////
// Struct node
typedef struct node* PtrToNode;
typedef PtrToNode Stack;
struct node
{
    int Element;
    PtrToNode Next;
};

/////////
// Implementation of stack
int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

/////////
// Pop function
void Pop(Stack S)
{
    PtrToNode firstCell;
    if (IsEmpty(S))
        printf(" ");
    else
    {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free(firstCell);
    }
}

/////////
// Make Empty
void MakeEmpty(Stack S)
{
    if (S == NULL)
        printf("Out of space!\n");
    else
    {
        while (!IsEmpty(S))
            Pop(S);
    }
}

/////////
// Implementation of stack
Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct node));
    if (S == NULL)
        printf("Out of space!\n");

    S->Next = NULL;
    MakeEmpty(S);
    return S;
}

/////////
// Top function
int Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Next->Element;

    printf("");

    return 0;
}

/////////
// Push function
void Push(int X, Stack S)// push an Integer
{
    PtrToNode temp;
    temp = (PtrToNode)malloc(sizeof(struct node));
    if (temp == NULL)
        printf("Out of space!\n");
    else
    {
        temp->Element = X;
        temp->Next = S->Next;
        S->Next = temp;
    }
}

/////////
// Push function
void Push2(char X, Stack S)// push an char
{
    PtrToNode temp;
    temp = (PtrToNode)malloc(sizeof(struct node));
    if (temp == NULL)
        printf("Out of space!\n");
    else
    {
        temp->Element = X;
        temp->Next = S->Next;
        S->Next = temp;
    }
}

/////////
// Dispose Stack function
void DisposeStack(Stack S)
{
    MakeEmpty(S);
    free(S);
}

/////////
// Function to check if the char is integer
int isInteger(char ch)
{
    if(ch == '0' ||  ch == '1' || ch == '2' ||  ch == '3' ||ch == '4' ||  ch == '5' ||ch == '6' ||  ch == '7' ||ch == '8' ||  ch == '9')
        return 1;
    else
        return 0;
}

//////////
// Function to check if the char is operator
int isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return 1;

    else return 0;
}

//////////
// Function to check if the char is opening symbol
int isOpeningSymbol(char ch)
{
    return ch == '(' || ch == '[' || ch == '{' || ch == '<';
}

//////////
// Function to check if the char is closing symbol
int isClosingSymbol(char ch)
{
    return ch == ')' || ch == ']' || ch == '}' || ch == '>';
}

/////////
// Function to correct the opening and closing sequences
void replaceOpeningAndClosingSymbols(char* str)
{
    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        // replace opening symbols
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == '[')
            str[i] = ')';
        else if (str[i] == '{')
            str[i] = ')';
        else if (str[i] == '<')
            str[i] = ')';
        // replace closing symbols
        else if (str[i] == ')')
            str[i] = '(';
        else if (str[i] == ']')
            str[i] = '(';
        else if (str[i] == '}')
            str[i] = '(';
        else if (str[i] == '>')
            str[i] = '(';
    }
}

/////////
// Function to check validity
int checkValidity(char equation[100])
{
    int isValid = 0;
    Stack stack = CreateStack();
    int i = 0;
    while (equation[i] != '\0')
    {
        char ch = equation[i];

        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') // If the character is an opening symbol, push it onto the stack
        {
            Push(ch, stack);
        }

        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') // If the character is a closing symbol

        {
            if (IsEmpty(stack)) // If the stack is empty, then error
            {
                printf("  Invalid: there is no opening for %c.\n", ch );
                DisposeStack(stack);
                return isValid;
            }


            char top = Top(stack); // Get the top element from the stack

            // Check if the closing symbol corresponds to the top opening symbol
            if ((ch == ')' && top == '(') || (ch == ']' && top == '[') ||
                    (ch == '}' && top == '{') || (ch == '>' && top == '<'))
            {

                Pop(stack);// Pop the top element from the stack
            }
            else
            {
                printf("  Invalid: %c is not closed.\n", top);
                DisposeStack(stack);
                return isValid;
            }
        }

        // Additional checks
        if (i > 0 && i < strlen(equation) - 1)
        {
            char prev_ch = equation[i - 1];
            char next_ch = equation[i + 1];

            // Between any decimal number and an opening symbol, there must be an operation symbol
            if ((isdigit(prev_ch)) && (ch == '(' || ch == '[' || ch == '{' || ch == '<'))
            {
                if (next_ch != '+' && next_ch != '*' && next_ch != '/' && next_ch != '-')
                {
                    printf("  Invalid: Missing operator between %c%c%c.\n", prev_ch,ch,next_ch);
                    DisposeStack(stack);
                    return isValid;
                }
            }

            // Between any closing symbol and a decimal number, there must be an operation symbol
            if ((ch == ')' || ch == ']' || ch == '}' || ch == '>') && (isdigit(next_ch) ))
            {
                if (prev_ch != '+' && prev_ch != '*' && prev_ch != '/' && prev_ch != '-')
                {
                    printf("  Invalid: Missing operator between %c%c%c.\n", prev_ch,ch,next_ch);
                    DisposeStack(stack);
                    return isValid;
                }
            }
        }

        i++;
    }
    char last_ch = Top(stack);
    // If reached the end of the equation and the stack is not empty, then error
    if (!IsEmpty(stack))
    {
        printf("  Invalid: %c is not closed.\n", last_ch);
        DisposeStack(stack);
        return isValid;
    }


    // last step
    isValid=1;
    printf("  Valid.\n");
    DisposeStack(stack);
    return isValid;
}

/////////
// Function to check precedence of operators
int checkPrecedence(char ch1, char ch2) // ch1 : current char , ch2 : Top char
{
    //operators can be : ^  /  *  +  -
    // return 1 : ch1 is lower in precedence than ch2 -> pop
    // return 0 : ch1 is higher or equal in precedence than ch2 -> push next to
    if ((ch1 == '/' && ch2 == '^') || (ch1 == '*' && ch2 == '^') || (ch1 == '+' && ch2 == '^') ||( ch1 == '-' && ch2 == '^' ))
        return 1;
    else if ((ch1 == '*' && ch2 == '/') || (ch1 == '+' && ch2 == '/') || (ch1 == '-' && ch2 == '/') )
        return 1;
    else if ((ch1 == '+' && ch2 == '*') || (ch1 == '-' && ch2 == '*' ))
        return 1;
    else if (ch1 == '-' && ch2 == '+' )
        return 1;
    else
        return 0;
}

/////////
// Function to convert form infix to prefix
char* infixToPrefix(char* infixEqu)
{
    Stack operatorStack = CreateStack(); // store opreators

    char* reversedString = strrev(infixEqu);
    replaceOpeningAndClosingSymbols(reversedString); // easier to deal with
    int strLength = strlen(reversedString);

    char* prefix = malloc((strLength + 1) * sizeof(char));// allocate the prefix string
    if (prefix == NULL)
    {
        printf("Memory allocation failed. Exiting...\n");
        return NULL;
    }
    prefix[0] = ' ';  // Null terminate the string

    for (int i = 0; i < strLength; i++) // start divide char one by one
    {
        char ch = reversedString[i];
        if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' ||
                ch == '7' || ch == '8' || ch == '9')                                                          //case 1: ch = number
        {
            prefix[strlen(prefix)] = ch;  // Append ch to the result string
            prefix[strlen(prefix) + 1] = '\0';  // Null terminate the string
        }

        else if (ch == '(') // case 2: ch = opening symbol
        {
            Push2(ch, operatorStack); // push immediately into the stack
        }

        else if (isOperator(ch)) // case 3: ch = operator -> cases
        {
            if (isOperator(ch) && IsEmpty(operatorStack)) // ch= operator & the stack is empty
            {
                Push2(ch, operatorStack); // just push it
            }
            else if (isOperator(ch) && !IsEmpty(operatorStack)) // ch= operator & the stack is not empty -> cases
            {
                char top = Top(operatorStack);
                int w = checkPrecedence(ch, top); // check Precedence between ch and the stack top
                if (top == '(') // if the top is not operator
                {
                    Push2(ch, operatorStack);
                }
                else if (isOperator(top) && w == 1) // ch is lower than top in Precedence
                {
                    Pop(operatorStack);
                    prefix[strlen(prefix)] = top;  // Append top
                    prefix[strlen(prefix) + 1] = '\0';  // Null terminate the string
                    Push2(ch, operatorStack);
                }
                else if (isOperator(top) && w == 0)// ch is higher than top in Precedence
                {
                    Push2(ch, operatorStack);
                }
            }
        }
        else if (ch == ')') // case 4: ch = closing symbol
        {
            char top = Top(operatorStack);
            while (top != '(')
            {
                Pop(operatorStack);
                prefix[strlen(prefix)] = top;  // Append top
                prefix[strlen(prefix) + 1] = '\0';  // Null terminate the string
                top = Top(operatorStack);
            }
            Pop(operatorStack);
        }
    }

    char top = Top(operatorStack);
    while(!IsEmpty(operatorStack))// append the operators remains in the stack
    {
        Pop(operatorStack);
        prefix[strlen(prefix)] = top;  // Append top
        prefix[strlen(prefix) + 1] = '\0';  // Null terminate the string
        char top = Top(operatorStack);
    }


    char* reversedFinalPrefixString = strrev(prefix);
    int strlength = strlen(reversedFinalPrefixString);
    if (strlength > 0)
    {
        reversedFinalPrefixString[strlength - 3] = '\0';// Set the last character to null terminator
    }
    return reversedFinalPrefixString;
}

/////////
// Check number of digits for an integer
int numOfDigits(int x, char* equation) // x : the position of the number in the prefix expression
{
    char* equ=equation;
    int length= strlen(equ);
    int c=0;   // counter to track the position of the number in the infix reversed expression
    int result=0;  // if the number has two digits the return the result calculated bellow, but if its one digit the return 0
    for (int i = 0 ; i < length ; i++)
    {
        char ch= equ[i];
        if (!isInteger(ch))
            continue;

        else if(isInteger(ch))
        {
            c++;

            if (c == x) // reach the same position
            {
                char ch2= equ[i+1]; // check the next char if its integer or not
                if(isInteger(ch2)) // calculate the result the return it
                {
                    int n1=atoi(&ch);
                    int n2=atoi(&ch2);
                    result = n2;
                    return result;
                }
                else if(!isInteger(ch2))
                    return 0;

            }
            else continue;

        }
    }

}

/////////
// Function to Evaluate the prefix expression result
int evaluateTheResult(char* origEqu, char* prefixEqu)
{

    Stack numbersstack= CreateStack(); // stack to store numbers

    char* equ=origEqu; // need it to check if the equation have multi digit numbers
    char* preequ=prefixEqu; // the prefix expression that we are going evaluate it is result
    char* reversedString = strrev(preequ);
    int strLength=strlen(reversedString);
    int result;
    int counter = 0 ;// count how many integers the prefix equation have to check number of digits for each number
    int skip=0;// skip when there is a number of multi digits
    for (int i = 0 ; i < strLength ; i++)
    {
        char ch= reversedString[i];
        if (skip == 1)
        {
            counter++;
            skip=0;
            continue;
        }

        if(isInteger(ch))
        {
            // send the integer to check how many digits it have
            counter++;// count how many numbers
            int nofd=numOfDigits(counter, equ);
            //cases
            if(nofd == 0)// the numbers is one digit
            {
                int integer=atoi(&ch);
                Push(integer, numbersstack);
                continue;
            }
            else if(nofd != 0) // the number is multi digits
            {
                Push(nofd, numbersstack);
                skip=1;
                continue;
            }


        }
        else if(isOperator(ch)) // when the ch = operator the calculate the result and push into the stack
        {
            int top1 = Top(numbersstack);
            Pop(numbersstack);
            int top2=Top(numbersstack);
            Pop(numbersstack);
            // operator cases
            if(ch == '^')
            {
                result= pow(top1,top2);
                Push(result,numbersstack);
            }
            else if(ch == '/')
            {
                if (top2 == 0)
                {
                    printf("!!!Error, Undefined operation divide a number by 0");
                    return 0;
                }

                result= top1/top2;
                Push(result,numbersstack);
            }
            else if(ch == '*')
            {
                result= top1*top2;
                Push(result,numbersstack);
            }
            else if(ch == '+')
            {
                result= top1+top2;
                Push(result,numbersstack);
            }
            else if(ch == '-')
            {
                result= top1-top2;
                Push(result,numbersstack);
            }
        }

    }

    return Top(numbersstack);
}

/////////
// Main function
int main()
{
    printf("enter the operation to do:\n 1-read file \n 2-Check the validity of equations \n 3-Convert valid equations from	infix to prefix and print the prefix expressions \n ");
    printf("4-Evaluate the prefix \n 5-Print invalid equations \n 6-Print all equations to a file \n 7-exit \n\n");
    int s;
    scanf("%d",&s);
    Equation* equations = NULL;
    int capacity = INITIAL_CAPACITY;
    int size = 0; // keep track of the number of equations

    int *intArray = NULL; // Initialize the array pointer to NULL
    int size2 = 0;      // Current size of the array
    int capacity2= 0;  // Capacity of the array
    int valid;

    preEquation* prefixEquations = NULL; // Initialize the array pointer to NULL // this array going to be use to store the prefix expressions
    int capacity3 = INITIAL_CAPACITY;
    int size3 = 0; // keep track of the number of equations

    int *resultArray = NULL; // Initialize the array pointer to NULL // this array going to be use to store the evaluation result
    int size4 = 0;      // Current size of the array
    int capacity4= 0;  // Capacity of the array
    int result;

    while(s!=7)
    {

        if(s==1)   // Open the file and read the data
        {
            free(equations);
            char file_name[50];
            printf("Enter the name of the file: \n");// let the user enter the file name
            scanf("%s", file_name);
            FILE *file;
            file = fopen(file_name, "r");
            if (file == NULL)
            {
                printf("Unable to open the file.\n");
                return 1;
            }

            equations = (Equation*)malloc(capacity * sizeof(Equation));
            if (equations == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }

            char one_equation[100]; // read the equation (one line)
            while (fgets(one_equation, sizeof(one_equation), file) != NULL) // read the equations
            {
                one_equation[strcspn(one_equation, "\n")] = '\0';

                if (size == capacity)
                {
                    capacity *= 2; // double the capacity (resize)
                    Equation* temp = (Equation*)realloc(equations, capacity * sizeof(Equation));
                    if (temp == NULL)
                    {
                        printf("Memory allocation failed.\n");// The equation in the buffer is copied to the equations array
                        return 1;
                    }
                    equations = temp;
                }

                strcpy(equations[size].equation, one_equation); // store the equations in the array
                size++;
            }

            fclose(file);

            for (int i = 0; i < size ; i++)// print the equations stored in the equations array
            {
                printf("%c.Equation %d: %s\n", 'a' + i, i + 1, equations[i].equation);
            }



        }

        else if(s==2)   //Check the validity of equations
        {
            for (int i = 0; i < size ; i++)
            {
                printf("%c. Equation NO.%d -->", 'a' + i, i+1);
                valid=checkValidity(equations[i].equation); // call the function

                if (size2 == capacity2) // Increase the capacity of the array if it is full
                {
                    capacity2 = capacity2 == 0 ? 1 : capacity2 * 2;
                    int *temp2 = realloc(intArray, capacity2 * sizeof(int));
                    if (temp2 == NULL)
                    {
                        printf("Memory allocation failed. Exiting...\n");
                        free(intArray);
                        return 1;
                    }
                    intArray = temp2;
                }

                // Store the (valid) in the array, this array store 1 if the equation is valid and store 0 if the equation is invalid
                intArray[size2] = valid;
                size2++;
            }

        }

        else if (s == 3)  // convert valid equation into prefix expression
        {
            prefixEquations = (preEquation*)malloc(capacity3 * sizeof(preEquation)); // allocation the array of prefix expressions
            if (prefixEquations == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }

            for (int i = 0; i < size2; i++)
            {
                if (intArray[i] == 1)  //only valid equations
                {
                    char* prefix = infixToPrefix(equations[i].equation); // call infixToPrefix function to convert the equation to prefix
                    if (prefix == NULL) // handle if the conversion process faild
                    {
                        printf("Conversion to prefix failed.\n");
                        return 1;
                    }

                    printf("%c. Equation No.%d prefix expression: %s \n", 'a' + i, i + 1, prefix); // print the result  of conversion

                    if (size3 == capacity3) // if it reached the capacity -> reallocate
                    {
                        capacity3 *= 2;
                        preEquation* temp = (preEquation*)realloc(prefixEquations, capacity3 * sizeof(preEquation));
                        if (temp == NULL)
                        {
                            printf("Memory reallocation failed.\n");
                            return 1;
                        }
                        prefixEquations = temp;
                    }

                    strcpy(prefixEquations[i].preequation, prefix); // store the prefix expression of the equation in the array
                    size3++;

                    free(prefix); // Free the allocated memory for prefix for the next equation
                }
            }
        }


        else if(s==4)  // Evaluate the prefix
        {
            for(int i=0 ; i < size2  ; i++)
            {

                if(intArray[i] == 1)
                {

                    result =evaluateTheResult(equations[i].equation, prefixEquations[i].preequation); // call the function
                    printf("%c. Equation No.%d  result = %d \n", 'a' + i,i+1,result); // print the evaluation result for valid equations
                    if (size4 == capacity4) // Increase the capacity of the array if it is full
                    {
                        capacity4 = capacity4 == 0 ? 1 : capacity4 * 2;
                        int *temp2 = realloc(resultArray, capacity4 * sizeof(int));
                        if (temp2 == NULL)
                        {
                            printf("Memory allocation failed. Exiting...\n");
                            free(resultArray);
                            return 1;
                        }
                        resultArray = temp2;
                    }

                    // Store the (evaluation result) in the array
                    resultArray[i] = result;
                    size4++;

                }
                else if (intArray == 0)
                {
                    result=0;
                    if (size4 == capacity4) // Increase the capacity of the array if it is full
                    {
                        capacity4 = capacity4 == 0 ? 1 : capacity4 * 2;
                        int *temp2 = realloc(resultArray, capacity4 * sizeof(int));
                        if (temp2 == NULL)
                        {
                            printf("Memory allocation failed. Exiting...\n");
                            free(resultArray);
                            return 1;
                        }
                        resultArray = temp2;
                    }

                    // Store the (evaluation result) in the array
                    resultArray[i] = result;
                    size4++;

                }
            }
        }
        else if(s==5)  // Print invalid equations
        {
            printf("All the invalid function : \n");

            for(int i=0 ; i < size2 ; i++)
            {
                if(intArray[i] == 0)// convert valid equations only
                {
                    printf("%c. Equation %d: %s\n", 'a' + i, i + 1, equations[i].equation);

                }
            }

        }

        else if(s==6)  // Print all equations to a output file
        {
            FILE *file2= fopen("output.txt", "w");// output file
            if (file2 == NULL)
            {
                printf("Failed to open the output file. Exiting...\n");
                return 1;
            }
            for(int i=0 ; i < size ; i++)// go through all equations
            {
                if(intArray[i] == 1)// print valid equations and their prefix and evaluation result
                {
                    strrev(equations[i].equation);
                    replaceOpeningAndClosingSymbols(equations[i].equation);
                    fprintf(file2,"Equation %d: %s", i + 1,equations[i].equation);
                    fprintf(file2,": Valid , ");
                    fprintf(file2,"prefix: %s ,",strrev (prefixEquations[i].preequation)); // not completed yet
                    fprintf(file2," result= %d \n", resultArray[i]); // not completed yet

                }
                else// print the invalid equations
                {
                    fprintf(file2,"Equation %d: %s", i + 1, equations[i].equation);
                    fprintf(file2,": Invalid \n");
                }

            }
            fclose(file2);
        }
        else
        {
            printf("please chose a number from 1-6 only\n");
        }
        printf("\n enter the operation to do:\n 1-read file \n 2-Check the validity of equations \n 3-Convert valid equations from	infix to prefix and print the prefix expressions \n ");
        printf("4-Evaluate the prefix \n 5-Print invalid equations \n 6-Print all equations to a output file \n 7-exit \n\n");
        scanf("%d", &s);

    }

    return 0;
}
