#include <stdio.h> //For input/output functions
#include <ctype.h>//character classification functions
#include <string.h>//string manipulation functions
 
#define LETTER 0 //representing a letter character.
#define DIGIT 1 //representing a digit character.
#define UNKNOWN 99 //used for unknown characters.
#define END_OF_FILE -1 //used to mark the end of the file
#define INT_LIT 10 //used for integer literals.
#define IDENT 11 //representing identifiers
#define ASSIGN_OP 20 //representing the assignment operator
#define ADD_OP 21//representing the addition operator
#define SUB_OP 22 //representing the subtraction operator
#define MULT_OP 23//representing the multiblication operator
#define DIV_OP 24//representing the division operator
#define LEFT_PAREN 25//representing the left parenthesis
#define RIGHT_PAREN 26// representing the right parenthesis
 
int charClass; // Stores character type
char lexeme[100]; // Stores the current lexeme
char nextChar; // Stores the next character
int nextToken; // Stores the next token type
FILE *inFile; // File pointer for input file handling
 
void addChar() {
   strncat(lexeme, &nextChar, 1);// Appends nextChar to the lexeme string
}
 
void getChar() {
   nextChar = fgetc(inFile); // Reads the next character from the file and stores it in nextChar
 
    if (nextChar != EOF){ // Checks if the character is not the end of the file
       if (isalpha(nextChar)) // Checks if the character is a letter
  {
           charClass = LETTER; // Sets charClass to LETTER if the character is a letter.
  } else if (isdigit(nextChar)){ // Checks if the character is a digit
           charClass = DIGIT; // Sets charClass to DIGIT if the character is a digit
       } else {
           charClass = UNKNOWN; // Sets charClass to UNKNOWN if the character is neither a letter nor a digit.
       }
   } else {
       charClass = END_OF_FILE ; // Sets charClass to END_OF_FILE if the character is the end of the file.
   }
}
 
void getNonBlank(){ // Defines the getNonBlank function
while (isspace(nextChar)){ // Checks if the current character is a space
       getChar();//If it's a space, get the next character until it's no longer a space
   }
}
 
int lookup(char ch) {// Define function lookup
    switch (ch) {// Starts a switch to check the value of ch
       case '(': // left parenthesis
           addChar(); // Calls addChar() to add the character to the lexeme
           nextToken = LEFT_PAREN; // puts nextToken to the constant LEFT_PAREN
           break; // Exits the switch block
       case ')': // right parenthesis
           addChar(); // Add it to the lexeme
           nextToken = RIGHT_PAREN; // Set token to RIGHT_PAREN
           break; // Exit this case
       case '+': // ADD_OP
           addChar();
           nextToken = ADD_OP; // sets nextToken to ADD_OP
           break; // Exit
       case '-': // SUB_OP
           addChar();
           nextToken = SUB_OP; // sets nextToken to SUB _OP
           break; // Exit
       case '*': //MULT_OP
           addChar();
           nextToken = MULT_OP; // sets nextToken to MULT_OP
           break; // Exit
       case '/': //DIV_OP
           addChar();
           nextToken = DIV_OP; // sets nextToken to DIV_OP
           break; // Exit
       case '=': // ASSIGN_OP
           addChar();
           nextToken = ASSIGN_OP; // Sets the nextToken to ASSIGN_OP
           break; // Exit
       default:
           addChar();
           nextToken = END_OF_FILE; //For any other char, add it and set token to EOF
           break; // Exit
   }
   return nextToken; //Return the detected token
}
 
int lex() // Defines the lex function
{
   int i = 0; // Declares a variable i
   memset(lexeme, 0, sizeof(lexeme));
// Clears the lexeme array by setting all its elements to 0
   getNonBlank();
//Calls the getNonBlank function to skip any whitespace characters and move to the next valid character.
 
   switch ((charClass) )// Starts a switch based on the character class
{
       case LETTER: // If the character is a letter
           addChar();// Add the character to the lexeme
           getChar();// Get the next character
           while (charClass == LETTER || charClass == DIGIT)
// continue adding characters if they are letters or digits
{
               addChar();// Add the character to the lexeme
               getChar();// Get the next character
           }
           nextToken = IDENT; // Set the token to identifier
           break; // Exit
 
       case DIGIT: // If the character is a digit
           addChar(); // Add the character to the lexeme
           getChar();  //Get the next character
           while (charClass == DIGIT)
// continue adding characters as long as they are digits
{
               addChar();// Add the character to the lexeme
               getChar();//Get the next character
           }
           nextToken = INT_LIT; //Set the token to integer literal
           break; // Exit
 
       case UNKNOWN:// If the character is not a letter or digit
           lookup(nextChar); // Call lookup()
           getChar();// Get the next character
           break; // Exit
 
       case END_OF_FILE: // Checks if the charClass is END_OF_FILE
           nextToken = END_OF_FILE;
// Sets nextToken to END_OF_FILE, indicating the end of the file
           strcpy(lexeme, "EOF");
// Copies the string "EOF" into the lexeme array to represent the end of file.
           break; // Exit
   }
 
   printf("Next token is: %d, Next lexeme is: %s\n", nextToken, lexeme);
//Prints the token code and the lexeme for debugging purposes.
   return nextToken; //Returns the nextToken to indicate the type of the token
}
 
int main() {
   inFile = fopen("/Users/macbookpro/Downloads/front.in", "r");
// Opens the input file (front.in) in read mode and assigns the file pointer to inFile.
   if (!inFile)
// Checks if the file failed to open
{
       printf("ERROR - cannot open front.in\n");
// Prints an error message if the file cannot be opened
       return 1;
   }
 
   getChar(); // Reads the first character from the file.
   do {
       lex();
   } while (nextToken != END_OF_FILE);
// Calls the lex function to process tokens until the end of the file is reached (nextToken becomes END_OF_FILE)
 
   fclose(inFile); // Closes the input file after processing.
   return 0;
}
