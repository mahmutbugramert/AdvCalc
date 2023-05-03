#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LL_INT_SIZE sizeof(long long int)  // size of long long int
#define LL_INT_BITS LL_INT_SIZE * 8 - 1   // size of long long int in bits - 1

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch){
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || 
		ch == '|' || ch == '&')
		return (true);
	return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch){
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '|' || ch == '&' ||
		ch == '=' || ch == ',')
		return (true);
	return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str){
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		str[0] == '9' || isDelimiter(str[0]) == true)
		return (false);
	return (true);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str){	
	int i, len = strlen(str);
	
	if (len == 0)
		return (false);	
	
	int sum= 0;
	for (i = 0; i < len; i++) {
	sum++;
	
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0)){

			return (false);}
	}
	return (true);
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right){
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

// Returns 'true' if the string is a FUNCTION.
bool isFunction(char c[]){
	if(strcmp(c, "xor") ==0 || strcmp(c, "ls") ==0 || strcmp(c, "rs")==0 || strcmp(c, "lr") ==0 || strcmp(c, "rr")==0 || strcmp(c, "not") == 0)
	return true;
return false;

}

// Returns 'true' if the character is a LEFT PARENTHESES.
bool isLeftParentheses(char ch){
	if(ch == '(')
		return true;
	return false;
}

// Returns 'true' if the character is a RIGHT PARENTHESES.
bool isRightParentheses(char ch){
	if(ch == ')')
		return true;
	return false;
}

// TokenType enumeration
typedef enum {
	// General TokenTypes
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_LEFT_PARENTHESES,
    TOKEN_TYPE_RIGHT_PARENTHESES,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_FUNCTION,
    
    // Spesific TokenTypes
    TOKEN_TYPE_ADD, 
    TOKEN_TYPE_SUBT,   
    TOKEN_TYPE_MULT, 
    TOKEN_TYPE_BAND,
    TOKEN_TYPE_BOR,
    TOKEN_TYPE_XOR, 
    TOKEN_TYPE_LS, 
    TOKEN_TYPE_RS,
    TOKEN_TYPE_NOT,
    TOKEN_TYPE_RR,
    TOKEN_TYPE_LR,
    TOKEN_TYPE_EQUAL,
    TOKEN_TYPE_COMMA,
    DEFAULT,
} TokenType;

// Struct a TOKEN data type
typedef struct {
    TokenType type;
    char val[257];
    char identifierValue[257];
} Token;

// takes Token as a parameter and it generalize the type of Token
char isGeneral(Token tok){
	if(tok.type == TOKEN_TYPE_ADD || tok.type == TOKEN_TYPE_SUBT || tok.type == TOKEN_TYPE_MULT || tok.type == TOKEN_TYPE_BAND || tok.type == TOKEN_TYPE_BOR ) return  TOKEN_TYPE_OPERATOR;
	else if(tok.type == TOKEN_TYPE_XOR || tok.type == TOKEN_TYPE_LS || tok.type == TOKEN_TYPE_RS || tok.type == TOKEN_TYPE_LR || tok.type == TOKEN_TYPE_RR || tok.type == TOKEN_TYPE_NOT) return TOKEN_TYPE_FUNCTION;
}

// Struct a NODE data type
struct Node{
	Token data;
	struct Node* nextNode;
};
typedef struct Node Node;

//QUEUE STARTS HERE
// decleration of functions for queue
void enqueue(Node* *firstNode, Token data);
void dequeue(Node* *firstNode);
void printQueue(Node* currentNode);
bool hasOneElt(Node* currentNode);

// for printing queue	
void printQueue(Node* currentNode){
	Node* tempNode = currentNode;
	if(tempNode == NULL || tempNode->nextNode == NULL){
		printf("Queue is empty\n");
		return; 
	}
	while (tempNode != NULL){
		printf("%s -->", tempNode->data.val);
		tempNode = tempNode->nextNode;
	}
	
	printf("NULL\n");
	return;	
}

// it creates new node and adds it to the queue
void enqueue(Node* *firstNode, Token data){
	Node* newNode = malloc(sizeof(Node));
	
	newNode->data = data;
	newNode->nextNode = NULL;
	
	Node* currentNode = *firstNode;
	
	while(currentNode->nextNode != NULL){
		currentNode = currentNode->nextNode;
	}
	
	currentNode->nextNode = newNode;
}

// it deletes the element from the queue
void dequeue(Node* *startNode){
	
	Node* start = *startNode;
	
	if(start == NULL || start->nextNode == NULL){
		return;
	}
	
	Node* firstNode = start->nextNode;
	Node* secondNode = firstNode->nextNode;
	
	start->nextNode = secondNode;
	
	free(firstNode);
	return;
}

// Returns 'true' if there is one element in the queue
bool hasOneElt(Node* currentNode){
	Node* tempNode = currentNode;
	if(tempNode->nextNode->nextNode == NULL ){
		return true; 
	}

	return false;	
}
//QUEUE ENDS HERE

//STACK STARTS HERE
// decleration of functions for stack
void push(Node* *firstNode, Token data);
Token peek(Node* *firstNode);
void pop(Node* *firstNode);
bool isEmpty(Node* firstNode);
void printStack(Node* currentNode);


// it creates a node, adds a Token inside of it and pushes into the Stack 
void push(Node* *firstNode, Token data){
	Node* start = *firstNode;
	Node* newNode = malloc(sizeof(Node));
	
	newNode->data = data;
	newNode->nextNode = NULL;
	
	if(start == NULL || start->nextNode == NULL){
		start->nextNode = newNode;
		return;
	}
	Node* firstNodeOfStack = start->nextNode;
	
	newNode->nextNode = firstNodeOfStack;
	start->nextNode = newNode;
	return;
}

// it returns the last Token in the Stack
Token peek(Node* *startNode){
	Node* start = *startNode;
	if(start->nextNode != NULL)
		return start->nextNode->data;
}

// it deletes the last elelement in the stack
void pop(Node* *startNode){
	Node* start = *startNode;
	if(start == NULL || start->nextNode == NULL){
		return;
	}
	Node* firstNode = start->nextNode;
	
	Token tokenToReturn = firstNode->data;
	
	Node* secondNode = firstNode->nextNode;
	
	start->nextNode = secondNode;
	
	free(firstNode);
	return;
}

// it controls whether stack is empty or not
bool isEmpty(Node* firstNode){
	Node* start = firstNode;
	
	if(start == NULL || start->nextNode == NULL){
		return true;
	}
	else{
		return false;
	}
}

// it prints the stack
void printStack(Node* currentNode){
	Node* tempNode = currentNode;
	if(tempNode == NULL || tempNode->nextNode == NULL){
		printf("Stack is empty\n");
		return; 
	}
	while (tempNode != NULL){
		printf("%s --->", tempNode->data.val);
		tempNode = tempNode->nextNode;
	}
	
	printf("NULL\n");
	return;
}
//STACK ENDS HERE

//HASH TABLE STARTS HERE
// decleration of functions for dictionary 
char* get(Node* startNode ,char* identifier);
void add(Node* *startNode, Token newToken);
void printDict(Node* startNode);
void updateValue(Node* startNode, char newValue[257], char identifier[257] );
bool doesExist(Node* startNode ,char* identifier);

// it creates a node, adds a Token inside of it and adds into the Dictionary
void add(Node* *startNode, Token newToken){
	Node* start = *startNode;
	Node* newNode = malloc(sizeof(Node));
	
	newNode->data = newToken;
	newNode->nextNode = NULL;
	newNode->data.identifierValue[0] = '0';
	newNode->data.identifierValue[1] = '\0';
	
	if(start == NULL || start->nextNode == NULL){
		start->nextNode = newNode;
		return;
	}
	Node* firstNodeOfDict = start->nextNode;
	
	newNode->nextNode = firstNodeOfDict;
	start->nextNode = newNode;
	return;
}

// it returns the value of given identifier
char* get(Node* startNode ,char identifier[257]){
	Node* tempNode = startNode;
	
	char* str = malloc(sizeof(char)*257);	
	while (tempNode != NULL){
		if(strcmp(tempNode->data.val, identifier) == 0){
			strcpy(str,tempNode->data.identifierValue);
			return str;		
		}	
		tempNode = tempNode->nextNode;
	}
	return str;
	
}

// it prints the elements of Dictionary
void printDict(Node* startNode){
	Node* tempNode = startNode;
	if(tempNode == NULL || tempNode->nextNode == NULL){
		printf("Dictionary is empty\n");
		return; 
	}
	while (tempNode != NULL){
		printf("(%s, %s) ~~>", tempNode->data.val, tempNode->data.identifierValue);
		tempNode = tempNode->nextNode;
	}
	
	printf("NULL\n");	
}

// it updates the value of given identifer
void updateValue(Node* startNode, char newValue[257], char identifier[257]){
	Node* tempNode = startNode;
	while (tempNode != NULL){
		if(strcmp(tempNode->data.val, identifier) == 0){
			strcpy(tempNode->data.identifierValue, newValue);
			return;
		}	
		tempNode = tempNode->nextNode;
	}
	
	return;
}

// it controls whether the identifer exist in Dictionary or not
bool doesExist(Node* startNode ,char* identifier){
	Node* tempNode = startNode;
		
	while (tempNode != NULL){
		if(strcmp(tempNode->data.val, identifier) == 0){
			return true;		
		}	
		tempNode = tempNode->nextNode;
	}
	
	return false;
}
//DICTIONARY ENDS HERE

//determine the exact operator
char whichOperator(char ch){
	if(ch == '+') return TOKEN_TYPE_ADD;
	else if(ch == '-') return TOKEN_TYPE_SUBT;
	else if(ch == '*') return TOKEN_TYPE_MULT;
	else if(ch == '&') return TOKEN_TYPE_BAND;
	else if(ch == '|') return TOKEN_TYPE_BOR;
	else if(ch == '=') return TOKEN_TYPE_EQUAL;
	else if(ch == ',') return TOKEN_TYPE_COMMA;
}

// returns the precedence of the given Token
int precedence(Token tok){
	if(tok.type == TOKEN_TYPE_BOR) return 1;
	else if(tok.type== TOKEN_TYPE_BAND) return 2;
	else if(tok.type == TOKEN_TYPE_SUBT || tok.type == TOKEN_TYPE_ADD) return 3;
	else if(tok.type== TOKEN_TYPE_MULT) return 4;
	else if(tok.type == TOKEN_TYPE_XOR || tok.type == TOKEN_TYPE_LR || tok.type == TOKEN_TYPE_RR || tok.type == TOKEN_TYPE_LS || tok.type == TOKEN_TYPE_RS || tok.type == TOKEN_TYPE_NOT ) return 5;
	else if(tok.type == TOKEN_TYPE_EQUAL) return 0;
	
	else return -1;
}

// returns the precedence of given TokenType
int precedence2(TokenType tt){
	if(tt == TOKEN_TYPE_BOR) return 1;
	else if(tt== TOKEN_TYPE_BAND) return 2;
	else if(tt == TOKEN_TYPE_SUBT || tt == TOKEN_TYPE_ADD) return 3;
	else if(tt== TOKEN_TYPE_MULT) return 4;
	else if(tt == TOKEN_TYPE_XOR || tt == TOKEN_TYPE_LS || tt == TOKEN_TYPE_RS || tt == TOKEN_TYPE_RR || tt == TOKEN_TYPE_LR || tt == TOKEN_TYPE_NOT) return 5;
	else if(tt == TOKEN_TYPE_EQUAL) return 0;	
	else return -1;
}


int numOfTokens; //number of Tokens in the line
int numOfIdentifiers; //number of identifers in the line
int numOfEq; //number of equal signs in the line
int numOfLeftPar; //number of open parenthesis in the line 
int numOfRightPar; //number of close parenthesis in the line

// Parsing the input STRING.
Token * parse(char* str){
	Token * tokenArray; // decleration of tokenArray 
	tokenArray = (Token*) calloc(257, sizeof(Token)); // initialization of tokenArray with calloc, to make it dynamic
	int left = 0, right = 0;
	int len = strlen(str) - 1;
	
	int i = 0;
	
	numOfTokens= 0; // initialization of number of Tokens. When we call parse function, value of numOfTokens will be zero.
	numOfIdentifiers = 0; // initialization of number of Identifiers. When we call parse function, value of numOfIdentifiers will be zero.
	numOfEq = 0; // initialization of number of Equal signs. When we call parse function, value of numOfEq will be zero.
	numOfLeftPar = 0;	// initialization of number of open parentheses. When we call parse function, value of numOfLeftPar will be zero.
	numOfRightPar = 0; // initialization of number of close parentheses. When we call parse function, value of numOfRightPar will be zero.
	

	while (right <= len && left <= right) {
		Token token;
		if(str[right] == '%')
			break;
			
		if(str[right] == '=')
			numOfEq++;
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right) {
			// determine whether the coming token is operator or not
			if (isOperator(str[right]) == true){
				token.type = whichOperator(str[right]);
				token.val[0]= str[right];
				token.val[1]= '\0';
				tokenArray[i] = token;
				i++;
				numOfTokens++;
				}
				
			// determine whether the coming token is open parentheses or not	
			else if(isLeftParentheses(str[right]) == true){
				token.type = TOKEN_TYPE_LEFT_PARENTHESES;
				token.val[0]= str[right];
				token.val[1]= '\0';
				tokenArray[i] = token;
				i++;
				numOfTokens++;
				numOfLeftPar++;
				}

			// determine whether the coming token is close parentheses or not
			else if(isRightParentheses(str[right]) == true){
				token.type = TOKEN_TYPE_RIGHT_PARENTHESES;
				token.val[0]= str[right];
				token.val[1]= '\0';
				tokenArray[i] = token;
				i++;
				numOfTokens++;
				numOfRightPar++;
				}

			right++;
			left = right;
		} else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) {
		
			char* subStr = subString(str, left, right - 1);

			// determine wether the coming token is function or not
			if(isFunction(subStr) == true){
				// determine wether the coming token's type is xor or not
				if(strcmp(subStr, "xor") == 0){					
					token.type = TOKEN_TYPE_XOR;
					strcpy(token.val,subStr);
					tokenArray[i] = token;
					i++;
					numOfTokens++;
					}
				// determine wether the coming token's type is ls or not
				else if(strcmp(subStr, "ls") == 0){				
					token.type = TOKEN_TYPE_LS;
					strcpy(token.val,subStr);
					tokenArray[i] = token;
					i++;
					numOfTokens++;
				}
				// determine wether the coming token's type is rs or not
				else if(strcmp(subStr, "rs") == 0){
					token.type = TOKEN_TYPE_RS;
					strcpy(token.val,subStr);
					tokenArray[i] = token;
					i++;
					numOfTokens++;
				}
				// determine wether the coming token's type is lr or not
				else if(strcmp(subStr, "lr") == 0){
					token.type = TOKEN_TYPE_LR;
					strcpy(token.val,subStr);
					tokenArray[i] = token;
					i++;
					numOfTokens++;
				}
				// determine wether the coming token's type is rr or not
				else if(strcmp(subStr, "rr") == 0){
					token.type = TOKEN_TYPE_RR;
					strcpy(token.val,subStr);
					tokenArray[i] = token;
					i++;
					numOfTokens++;
				}
				// determine wether the coming token's type is not or not
				else if(strcmp(subStr, "not") == 0){
					token.type = TOKEN_TYPE_NOT;
					strcpy(token.val,subStr);
					tokenArray[i] = token;
					i++;
					numOfTokens++;
				}
			}
			
			// determine wether the coming token is integer or not
			else if (isInteger(subStr) == true){
				if(subStr != " "){
				token.type = TOKEN_TYPE_NUMBER;
				strcpy(token.val,subStr);
				tokenArray[i] = token;
				i++;
				numOfTokens++;
				}
			}
			
			// determine wether the coming token is identifier or not
			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false){
				token.type = TOKEN_TYPE_IDENTIFIER;
				strcpy(token.val,subStr);
				tokenArray[i] = token;
				i++;
				numOfTokens++;	
				numOfIdentifiers++;
				}
				
			else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false){
                     		strcpy(token.val,subStr);
				tokenArray[i] = token;
				i++;
				numOfTokens++; 
            }

			left = right;
		}
	}
	return tokenArray;
}


long long int rotateLeft(long long int number, unsigned long long int rotation); 
long long int rotateRight(long long int number, unsigned long long int rotation);
long long int calculate(long long int number1,long long int number2,TokenType typeOfOperator); 

long long int rotateLeft(long long int number, unsigned long long int rotation){   // Returns the result of "number" rotated "rotation" times to the left.
   
   long long  int fallingNumber;

    rotation %= LL_INT_BITS;

    while(rotation--){
        fallingNumber = (number >> LL_INT_BITS) & 1; 
        number = (number << 1) | fallingNumber;
    }

    return number;
}

long long int rotateRight(long long int number, unsigned long long int rotation){ // Returns the result of "number" rotated "rotation" times to the right.
   
    long long  int fallingNumber;

    rotation %= LL_INT_BITS;

    while(rotation--){
        fallingNumber = number & 1;
        number = (number >> 1) & (~(1UL << LL_INT_BITS));
        number = number | (fallingNumber << LL_INT_BITS);
    }

    return number;
}

long long int calculate(long long int number1,long long int number2,TokenType typeOfOperator){ // It applies the given type of operator to number1 and number2
	switch(typeOfOperator){
		case TOKEN_TYPE_ADD:
			return number1 + number2;
			break;
		case TOKEN_TYPE_SUBT:
			return number2 - number1;
			break;
		case TOKEN_TYPE_MULT:
			return number1 * number2;
			break;
		case TOKEN_TYPE_BOR:
			return number1 | number2;
			break;
		case TOKEN_TYPE_BAND:
			return number1 & number2;
			break;
		case TOKEN_TYPE_XOR:
			return number1 ^ number2;
			break;
		case TOKEN_TYPE_LS:
			return number2 << number1;
			break;
		case TOKEN_TYPE_RS:
			return number2 >> number1;
			break;	
		case TOKEN_TYPE_NOT:
			return ~number1;
			break;
		case TOKEN_TYPE_RR:
			return rotateRight(number2, number1);
			break;
		case TOKEN_TYPE_LR:
			return rotateLeft(number2, number1);
			break;	
		default:
			printf("Error!\n");
			printf("> ");
			return 1;				
	}
}


// MAIN FUNCTION
int main()
{
	char line[257] = "";  // String which will be used to store input lines
	
	Node* firstNodeOfDict = (Node*) malloc(sizeof(Node));  // initial Node of Dictionary
	Node* firstNode = (Node*) malloc(sizeof(Node));        // initial Node of Queue
	Node* firstNodeOfStack = (Node*) malloc(sizeof(Node)); // initial Node of Stack
	printf("> ");
	while(fgets(line, sizeof(line), stdin)){
				
		Token *tokenArray;  
		tokenArray = parse(line);		
		
		//ERROR HANDLINGS STARTS HERE
		if(numOfTokens == 0){
		    printf("> ");
		    continue;
		}
		if(numOfEq > 1){
			printf("Error!\n");
			printf("> ");
			continue;
		}
		if(numOfRightPar != numOfLeftPar){
			printf("Error!\n");
			printf("> ");
			continue;
		}
		if(numOfTokens == 1 && isGeneral(tokenArray[0]) == TOKEN_TYPE_FUNCTION){
			printf("Error!\n");
			printf("> ");
			continue;	
		}		
		if(isGeneral(tokenArray[numOfTokens-1]) == TOKEN_TYPE_OPERATOR || isGeneral(tokenArray[numOfTokens-1]) == TOKEN_TYPE_FUNCTION){
			printf("Error!\n");
			printf("> ");
			continue;
		}
		
		bool warn= true;
		int m;

		for(int k = 0; k < numOfTokens -1; k++){
			int l = k+1;
			m = k - 1;
			if(k>0) {
				m = k-1;
				if(	tokenArray[m].type != TOKEN_TYPE_NUMBER && tokenArray[m].type != TOKEN_TYPE_IDENTIFIER){
					if(tokenArray[k].type == TOKEN_TYPE_SUBT && tokenArray[l].type == TOKEN_TYPE_NUMBER){
					printf("Error!\n");
					warn = false;
					break;
					}
				}	
	
			}
			if(k == 0 && isGeneral(tokenArray[k]) == TOKEN_TYPE_OPERATOR){
				printf("Error!\n");
				warn = false;
				break;
			}
			if((k == 0 && tokenArray[k].type == TOKEN_TYPE_LEFT_PARENTHESES) || (tokenArray[k].type == TOKEN_TYPE_LEFT_PARENTHESES && isGeneral(tokenArray[m]) != TOKEN_TYPE_FUNCTION)){
					int c = k + 1;
					bool warn2 = true;
					while(c < numOfTokens && tokenArray[c].type != TOKEN_TYPE_RIGHT_PARENTHESES && tokenArray[c].type != TOKEN_TYPE_LEFT_PARENTHESES){
						if(tokenArray[c].type == TOKEN_TYPE_COMMA){
							warn2 = false;
							break;
						}
						c++;
					}
					if(!warn2){
						printf("Error!\n");
						warn = false;
						break;
					}
					
				}
			if(tokenArray[k].type == TOKEN_TYPE_EQUAL){
				if(k == 0){
					printf("Error!\n");
					warn = false;
					break;
				}
				if(k == 1 && tokenArray[k-1].type == TOKEN_TYPE_IDENTIFIER) {
					warn = true;
				}
				else{
					printf("Error!\n");
					warn = false;
					break;
				}	
			}
			if(tokenArray[k].type == TOKEN_TYPE_LEFT_PARENTHESES && (tokenArray[l].type == TOKEN_TYPE_RIGHT_PARENTHESES || isGeneral(tokenArray[l]) == TOKEN_TYPE_OPERATOR)){
				printf("Error!\n");
				warn = false;
				break;
			}
			if(tokenArray[k].type == TOKEN_TYPE_NUMBER && tokenArray[l].type == TOKEN_TYPE_NUMBER){
				printf("Error!\n");	
				warn= false;
				break;			
			}
			if(tokenArray[k].type == TOKEN_TYPE_IDENTIFIER && tokenArray[l].type == TOKEN_TYPE_IDENTIFIER){
				printf("Error!\n");	
				warn= false;
				break;			
			}
			if(isGeneral(tokenArray[k]) == TOKEN_TYPE_OPERATOR && isGeneral(tokenArray[l]) == TOKEN_TYPE_OPERATOR || isGeneral(tokenArray[k]) == TOKEN_TYPE_FUNCTION && isGeneral(tokenArray[l]) == TOKEN_TYPE_FUNCTION ) {
				printf("Error!\n");	
				warn= false;
				break;			
			}
			if(tokenArray[k].type == TOKEN_TYPE_COMMA && isGeneral(tokenArray[l]) == TOKEN_TYPE_OPERATOR){
				printf("Error!\n");
				warn = false;	
				break;
			}
				
		}
		
		// ERROR HANDLINGS ENDS HERE
		if(warn) {
			//INFIX TO POSTFIX PART

			//This for loop and following while loop transforms the line from infix to postfix notation using the Shunting-yard Algorithm.
			for(int j = 0; j < numOfTokens ; j++){
				if(tokenArray[j].type == TOKEN_TYPE_NUMBER || tokenArray[j].type == TOKEN_TYPE_IDENTIFIER){ // if the Token is a number or a identifer, adds it to the queue.
					enqueue(&firstNode, tokenArray[j]);
					continue;
				}
				
				
				if(tokenArray[j].type == TOKEN_TYPE_ADD ||tokenArray[j].type == TOKEN_TYPE_MULT ||tokenArray[j].type == TOKEN_TYPE_SUBT ||tokenArray[j].type == TOKEN_TYPE_BAND ||
				tokenArray[j].type == TOKEN_TYPE_BOR || tokenArray[j].type == TOKEN_TYPE_XOR || tokenArray[j].type == TOKEN_TYPE_LS || tokenArray[j].type == TOKEN_TYPE_RS|| 
				tokenArray[j].type == TOKEN_TYPE_LR|| tokenArray[j].type == TOKEN_TYPE_RR|| tokenArray[j].type == TOKEN_TYPE_NOT || tokenArray[j].type == TOKEN_TYPE_EQUAL ){
				// if the Token is an operator, followings is done
						
					if(isEmpty(firstNodeOfStack)){	// if the Stack is empty, it adds the Token to the Stack	
							
						push(&firstNodeOfStack, tokenArray[j]);
					}
					else{	
						while(peek(&firstNodeOfStack).type != TOKEN_TYPE_LEFT_PARENTHESES && precedence(peek(&firstNodeOfStack)) >=  precedence(tokenArray[j])){ // while the top element of the Stack is not "(" and the top element's precedence is greater than or equal to the new Token, pop Tokens from the Stack and add themk to Queue
							
							enqueue(&firstNode, peek(&firstNodeOfStack));
							pop(&firstNodeOfStack);
							
							if(isEmpty(firstNodeOfStack))
								break;
						}
						push(&firstNodeOfStack, tokenArray[j]);
				
					}
					continue;
				}
				if(tokenArray[j].type == TOKEN_TYPE_LEFT_PARENTHESES){ // if the Token is a "(" add it to the Stack
					push(&firstNodeOfStack, tokenArray[j]);
					continue;
				}
				if(tokenArray[j].type == TOKEN_TYPE_RIGHT_PARENTHESES){
					while(peek(&firstNodeOfStack).type != TOKEN_TYPE_LEFT_PARENTHESES){ // if the Token is a ")", while the top element of the Stack is not a "(", pop Tokens from the Stack, and add them to the Queue.
						enqueue(&firstNode, peek(&firstNodeOfStack));
						pop(&firstNodeOfStack);
						
					}
					pop(&firstNodeOfStack);
					continue;
				}
				if(tokenArray[j].type == TOKEN_TYPE_COMMA){
					while(peek(&firstNodeOfStack).type != TOKEN_TYPE_LEFT_PARENTHESES){ //if the Token is a ",", while the top element of the Stack is not a "(", pop Tokens from the Stack, and add them to the Queue
						enqueue(&firstNode, peek(&firstNodeOfStack));
						pop(&firstNodeOfStack);
					}
					continue;
				}
				
			}	
			
			// it enqueues the remaining Tokens in the Stack		
			while(!isEmpty(firstNodeOfStack)){
				enqueue(&firstNode, peek(&firstNodeOfStack));
				pop(&firstNodeOfStack);	
			}

			//CALCULATION PART
			
			//This while loop calculates the expressions and pushes the final result in to the Stack
			while(firstNode->nextNode != NULL){
				if(firstNode->nextNode->data.type == TOKEN_TYPE_IDENTIFIER){	 // if the Token is an identifer, it adds it to the Dictionary and to the Stack. If it already exists, adds it to the Stack only.			
					if(hasOneElt(firstNode)){
						if(!doesExist(firstNodeOfDict, firstNode->nextNode->data.val)){
							add(&firstNodeOfDict, firstNode->nextNode->data);	
						}
						push(&firstNodeOfStack, firstNode->nextNode->data);
						dequeue(&firstNode);
						break;
					}
					else{
						if(!doesExist(firstNodeOfDict, firstNode->nextNode->data.val)){
							add(&firstNodeOfDict, firstNode->nextNode->data);	
						}
						push(&firstNodeOfStack, firstNode->nextNode->data);
						dequeue(&firstNode);
					}
					
					continue;
				}
				if(firstNode->nextNode->data.type == TOKEN_TYPE_NUMBER){ // if the Token is a number, it deletes from the Queue and adds to the Stack.
					push(&firstNodeOfStack, firstNode->nextNode->data);
					dequeue(&firstNode);
					continue;
				}
				if(firstNode->nextNode->data.type == TOKEN_TYPE_ADD || firstNode->nextNode->data.type == TOKEN_TYPE_MULT || firstNode->nextNode->data.type == TOKEN_TYPE_SUBT ||
				firstNode->nextNode->data.type == TOKEN_TYPE_BAND || firstNode->nextNode->data.type == TOKEN_TYPE_BOR || firstNode->nextNode->data.type == TOKEN_TYPE_XOR || 
				firstNode->nextNode->data.type == TOKEN_TYPE_LS || firstNode->nextNode->data.type == TOKEN_TYPE_RS|| firstNode->nextNode->data.type == TOKEN_TYPE_LR|| 
				firstNode->nextNode->data.type == TOKEN_TYPE_RR){ // if the Token is one of the above operators, it is calculated here.
								
					Token firstOperand = peek(&firstNodeOfStack);
					pop(&firstNodeOfStack);
					Token secondOperand = peek(&firstNodeOfStack);
					pop(&firstNodeOfStack);
					if(firstOperand.type != TOKEN_TYPE_NUMBER && firstOperand.type != TOKEN_TYPE_IDENTIFIER && secondOperand.type != TOKEN_TYPE_NUMBER && firstOperand.type != TOKEN_TYPE_IDENTIFIER){
						printf("Error!\n");
						break;
					}
					long long int number1;
					long long int number2;
					
					//if elses below controls whether the Tokens are identifers or numbers. 
					if(firstOperand.type == TOKEN_TYPE_NUMBER) 
						number1 = atoll(firstOperand.val); //if tokenType is number, then convert its type to integer via using atoll built-in function.
					else{
						number1 = atoll(get(firstNodeOfDict, firstOperand.val)); //if tokenType is identifier, then get its value from dictionary and convert its type to integer via using atoll built-in function.
					}
					if(secondOperand.type == TOKEN_TYPE_NUMBER)
						number2 = atoll(secondOperand.val); //if tokenType is number, then convert its type to integer via using atoll built-in function.
					else{
						number2 = atoll(get(firstNodeOfDict, secondOperand.val));//if tokenType is identifier, then get its value from dictionary and convert its type to integer via using atoll built-in function.
					}
					
					long long int result = calculate(number1, number2, firstNode->nextNode->data.type);
					char resultForToken[257];
					sprintf(resultForToken, "%lld", result);
									
					Token newToken;
					newToken.type = TOKEN_TYPE_NUMBER;
					strcpy(newToken.val, resultForToken);
									
					push(&firstNodeOfStack, newToken);
					dequeue(&firstNode);
				}	
				
				else if(firstNode->nextNode->data.type == TOKEN_TYPE_NOT){ // calculation for operator "not". 
					Token operand = peek(&firstNodeOfStack);
					pop(&firstNodeOfStack);
					if(operand.type != TOKEN_TYPE_NUMBER && operand.type != TOKEN_TYPE_IDENTIFIER){
						printf("Error!\n");
						break;
					}
					long long int number;
					if(operand.type == TOKEN_TYPE_NUMBER){
						number = atoll(operand.val);
					}
					else{
						number = atoll(get(firstNodeOfDict, operand.val));
					}
					
					long long int result = calculate(number, number, firstNode->nextNode->data.type);
								
					char resultForToken[257];
					sprintf(resultForToken, "%lld", result);
					Token newToken;
					
					newToken.type = TOKEN_TYPE_NUMBER;
					strcpy(newToken.val, resultForToken);
					push(&firstNodeOfStack, newToken);
					dequeue(&firstNode);
				}
				else if(firstNode->nextNode->data.type == TOKEN_TYPE_EQUAL){ // when it sees an equal sign, it updatess the value of the variable..
					Token operand = peek(&firstNodeOfStack);
					pop(&firstNodeOfStack);
					Token identifier = peek(&firstNodeOfStack);
					pop(&firstNodeOfStack);
					if(identifier.type != TOKEN_TYPE_IDENTIFIER){
						printf("Error!\n");
						break;
					}
						
					if(operand.type == TOKEN_TYPE_NUMBER){
						updateValue(firstNodeOfDict, operand.val, identifier.val);
					}	
					else{
						updateValue(firstNodeOfDict, get(firstNodeOfDict, operand.val), identifier.val);
					}
								
					dequeue(&firstNode);
					continue;
				}
				else if(firstNode->nextNode->data.type == TOKEN_TYPE_COMMA){
					dequeue(&firstNode);
					continue;
				}	
			}
			
			// Here final result is popped from the Stack and printed 
			if(numOfEq != 1){
				long long int finalResult;
				
				if(peek(&firstNodeOfStack).type == TOKEN_TYPE_NUMBER){
					finalResult = atoll(peek(&firstNodeOfStack).val);
					pop(&firstNodeOfStack);
				}
				else{					
					finalResult = atoll(get(firstNodeOfDict, peek(&firstNodeOfStack).val));
					pop(&firstNodeOfStack);
				}
				
				printf("%lld\n", finalResult);
			}	
					
			firstNodeOfStack->nextNode = NULL;
			firstNode->nextNode = NULL;
			
		}
     	//freeing allocated memory
		free(tokenArray);	
  		printf("> ");
  	}
  	//freeing allocated memory
	free(firstNodeOfDict);
	free(firstNode);
	free(firstNodeOfStack);
}
