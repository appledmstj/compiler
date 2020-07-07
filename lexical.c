#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

#define MAXTOKEN 100
#define STRING_SIZE 256

typedef enum {
	VAR_TYPE = 0,
	INTEGER = 1,
	LITERAL = 2,
	BOOLEAN = 3,            //무시
	FLOAT = 4,
	IDENTIFIER = 5,
	KEYWORD = 6,
	ARITHMETIC = 7,
	BITWISE = 8,            //무시
	ASSIGN = 9,
	COMPARISON = 10,
	TERMINATE = 11,
	LBRACKET = 12, RBRACKET = 13,
	COMMA = 14,
	LPAREN = 15, RPAREN = 16,
	WHITESPACE = 17
} TokenType;

typedef struct token {
	TokenType tokenType;
	char* token;
} token;


bool isLetter(char ch) {
	if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' ||
		ch == 'e' || ch == 'f' || ch == 'g' || ch == 'h' ||
		ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' ||
		ch == 'm' || ch == 'n' || ch == 'o' || ch == 'p' ||
		ch == 'q' || ch == 'r' || ch == 's' || ch == 't' ||
		ch == 'u' || ch == 'v' || ch == 'w' || ch == 'x' ||
		ch == 'y' || ch == 'z' || ch == '_')
		return (true);
	return (false);
}
bool isKeyword(char* str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "return") ||
		!strcmp(str, "for"))
		return (true);
	return (false);
}

bool isVar_Type(char* str)
{
	if (!strcmp(str, "int") || !strcmp(str, "float") ||
		!strcmp(str, "bool") || !strcmp(str, "char"))
		return (true);
	return (false);
}

bool isBoolean(char* str) {
	if (!strcmp(str, "true") || !strcmp(str, "false"))
		return (true);
	return (false);
}

bool isDigit(char ch) {
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' ||
		ch == '4' || ch == '5' || ch == '6' || ch == '7' ||
		ch == '8' || ch == '9')
		return (true);
	return (false);
}
bool isSign(char ch) {
	if (ch == '-')
		return (true);
	return (false);
}
bool isIdentifier(char ch) {         //keyword나 identifier가 아니면 시작부터~digit,_로 이루어진 토큰 전체를 identifier로 판단
	if (isLetter(ch) || isDigit(ch) || ch == '_')
		return (true);
	return (false);
}


bool isNonzero(char ch) {
	if (ch == '1' || ch == '2' || ch == '3' ||
		ch == '4' || ch == '5' || ch == '6' || ch == '7' ||
		ch == '8' || ch == '9')
		return (true);
	return (false);
}
bool isZero(char ch) {
	if (ch == '0')
		return (true);
	return (false);
}

bool isFloatingPoint(char ch) {
	if (ch == '.')
		return (true);
	return (false);
}

bool findLiteral(char ch) {         //첫번째 쌍 나오면 두번째 쌍 나올때까지 반복
	if (ch == '"')
		return (true);
	return (false);
}

bool is1Delimiter(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
		ch == ',' || ch == ';' ||
		ch == '(' || ch == ')' ||
		ch == '{' || ch == '}' || ch == '&' || ch == '|')
		return (true);
	return (false);
}

bool isArithmetic(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/')
		return (true);
	return (false);
}

bool isTerminate(char ch)
{
	if (ch == ';')
		return (true);
	return (false);
}

bool isLBracket(char ch) {
	if (ch == '{')
		return (true);
	return (false);
}

bool isRBracket(char ch) {
	if (ch == '}')
		return (true);
	return (false);
}

bool isLParen(char ch) {
	if (ch == '(')
		return (true);
	return (false);
}

bool isRParen(char ch) {
	if (ch == ')')
		return (true);
	return (false);
}

bool isComma(char ch) {
	if (ch == ',')
		return (true);
	return (false);
}

bool is1Bitwise(char ch) {
	if (ch == '&' || ch == '|')
		return (true);
	return (false);
}

bool is2test(char ch)                  // 2개가 1부호인지 1개가 1부호인지 확인이 필요한 부호, 이 함수 2번돌려서 확인
{
	if (ch == '<' || ch == '>' || ch == '=')
		return (true);
	return (false);
}

bool isExclamation(char ch) {
	if (ch == '!')
		return (true);
	return (false);
}


bool is2Bitwise(char* str)               //위에서 2번 돌려서 2번째 결과도 true면 사용
{
	if (!strcmp(str, "<<") || !strcmp(str, ">>"))
		return (true);
	return (false);
}

bool is2Comparison(char* str)               //위에서 2번 돌려서 2번째 결과도 true면 사용
{
	if (!strcmp(str, "==") || !strcmp(str, "!=") ||
		!strcmp(str, "<=") || !strcmp(str, ">="))
		return (true);
	return (false);
}


bool isAssign(char ch) {                  //2번째가 false일때
	if (ch == '=')
		return (true);
	return (false);
}

bool is1Comparison(char ch) {                  //2번째가 false일때
	if (ch == '<' || ch == '>')
		return (true);
	return (false);
}

bool isWhiteSpace(char ch) {                  //연속으로 true 나와도 1개로 처리
	if (ch == '\t' || ch == '\n' || ch == ' ')
		return (true);
	return (false);
}

char* subString(char* str, int left, int right)
{
	//printf("subStringstart\n");
	int i;
	char* subStr = (char*)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}
int tableFlag = 0;
int parser(char* str, token* table[MAXTOKEN]) {
	int left = 0, right = 0;

	int len = strlen(str);
	//printf("parserstart len: %d \n", len);
	while (right <= len && left <= right) {
		//printf("whilestart %c \n", str[right]);
		if (is1Delimiter(str[right]) == true) {
			//printf("1Delimiter\n");
			if (isArithmetic(str[right]) == true) {
				table[tableFlag]->tokenType = ARITHMETIC;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (isComma(str[right]) == true) {
				//printf("dd\n");
				table[tableFlag]->tokenType = COMMA;
				//printf("type\n");
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (isTerminate(str[right]) == true) {
				table[tableFlag]->tokenType = TERMINATE;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (isLParen(str[right]) == true) {
				table[tableFlag]->tokenType = LPAREN;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (isRParen(str[right]) == true) {
				table[tableFlag]->tokenType = RPAREN;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (isLBracket(str[right]) == true) {
				table[tableFlag]->tokenType = LBRACKET;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (isRBracket(str[right]) == true) {
				table[tableFlag]->tokenType = RBRACKET;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			else if (is1Bitwise(str[right]) == true) {
				table[tableFlag]->tokenType = BITWISE;
				table[tableFlag]->token = str[right];
				tableFlag++;
			}
			right++;
			left = right;
			//printf("right: %d\n", right);
		}
		else if (findLiteral(str[right]) == true) {      //" 하나 등장, Literal 찾기
														 //printf("findLiteral\n");
			int temp = right;
			do {         //다른 " 찾기
				temp++;
				if (str[temp] == '\0') {            //문장 끝까지 "가 다시 나타나지 않을 경우 에러
					printf("Error: Only one \" in the whole string \n");
					return 0;
				}
				//printf("temp:%d", temp);
			} while (!findLiteral(str[temp]));
			right = temp;
			char* subStr = subString(str, left, right);
			table[tableFlag]->tokenType = LITERAL;

			//for (int i = 0; i <= strlen(subStr); i++) {      //table에 literal 저장
			table[tableFlag]->token = subStr;
			//printf("****\n");
			tableFlag++;
			right++;
			left = right;
			//printf("right: %d\n", right);
		}
		else if (is2test(str[right]) == true || isExclamation(str[right]) == true) {            //1bit이나 2bit을 한번에 검사해야 하는 시작부호들
																								//printf("is2test\n");
			bool secondtest = is2test(str[right + 1]);
			if (secondtest == true || isExclamation(str[right]) == true) { //바로 다음 문자도 테스트통과 혹은 !로 시작하는 부호는 무조건 2bit 검사
				right++;
				char* subStr = subString(str, left, right);
				if (is2Bitwise(subStr) == true) {
					//printf("bit\n");
					table[tableFlag]->tokenType = BITWISE;
					table[tableFlag]->token = subStr;
					tableFlag++;
				}
				else if (is2Comparison(subStr) == true) {
					table[tableFlag]->tokenType = BITWISE;
					table[tableFlag]->token = subStr;
					tableFlag++;
					//printf("dd?\n");
				}
				else {
					printf("Error: %s is Unknown sign\n", subStr);
				}
			}
			else {
				if (isAssign(str[right]) == true) {
					//printf("?\n");
					table[tableFlag]->tokenType = ASSIGN;
					table[tableFlag]->token = str[right];
					tableFlag++;
				}
				else if (is1Comparison(str[right]) == true) {
					table[tableFlag]->tokenType = COMPARISON;
					table[tableFlag]->token = str[right];
					tableFlag++;
				}
			}
			right++;
			left = right;
			//printf("right: %d\n", right);
		}
		else if (isLetter(str[right]) == true) {
			//printf("letter\n");
			int temp = right;
			while (isLetter(str[temp])) {         //letter 끝 찾기
				temp++;
				//printf("temp:%d", temp);
			}
			right = temp - 1;
			char* subStr = subString(str, left, right);
			if (isKeyword(subStr) == true) {
				table[tableFlag]->tokenType = KEYWORD;
				table[tableFlag]->token = subStr;
			}
			else if (isVar_Type(subStr) == true) {
				//printf("int\n");
				table[tableFlag]->tokenType = VAR_TYPE;
				table[tableFlag]->token = subStr;
			}
			else if (isBoolean(subStr) == true) {
				table[tableFlag]->tokenType = BOOLEAN;
				table[tableFlag]->token = subStr;
			}
			else {
				temp = right;
				while (isIdentifier(str[temp])) {
					temp++;
					//printf("temp:%d", temp);
				}
				right = temp - 1;
				char* subStr = subString(str, left, right);
				table[tableFlag]->tokenType = IDENTIFIER;
				table[tableFlag]->token = subStr;
			}
			//printf("*****%s\n", table[tableFlag]->token);
			tableFlag++;
			right++;
			left = right;
		}
		else if (isWhiteSpace(str[right]) == true) {
			//printf("ws\n");
			int temp = right;
			while (isWhiteSpace(str[temp])) {
				//printf("temp:%c", str[temp]);
				temp++;
			}
			//printf("**temp:%c\n", str[temp]);
			right = temp - 1;
			//printf("**right:%c, %c\n", str[right], str[right+1]);
			char* subStr = subString(str, left, right);
			table[tableFlag]->tokenType = WHITESPACE;
			table[tableFlag]->token = subStr;
			//printf("*****%s..\n", table[tableFlag]->token);
			tableFlag++;
			right++;
			left = right;
		}
		else if (isZero(str[right]) == true) {
			if (isFloatingPoint(str[right + 1]) == false) {            //0
				table[tableFlag]->tokenType = INTEGER;
				table[tableFlag]->token = str[right];
				//printf("%d\n", atoi(table[tableFlag]->token));
				tableFlag++;
				right++;
				left = right;
			}
			else if (isFloatingPoint(str[right + 1]) == true) {
				//printf("%c %c\n", str[right], str[right + 1]);
				right++;            //지금 right는 .에 있음
				if (isDigit(str[right + 1]) == true) {
					//printf("%c\n", str[right]);
					int temp = right + 1;
					//printf("%c\n", str[temp]);
					//printf("temp:%d", temp);
					while (isDigit(str[temp])) {            //0.xx
						temp++;
						//printf("%c", str[temp]);
					}
					temp--;;
					//printf("%c\n", str[temp]);
					if (str[temp] == '0') {
						if (temp == (right + 1)) {         //0.0
							right = temp;
							char* subStr = subString(str, left, right);
							table[tableFlag]->tokenType = FLOAT;
							table[tableFlag]->token = subStr;
							tableFlag++;
							right++;
							left = right;
						}
						else {
							do {
								temp--;
							} while (str[temp] != 0);
							right = temp;
							char* subStr = subString(str, left, right);
							table[tableFlag]->tokenType = FLOAT;
							table[tableFlag]->token = subStr;
							tableFlag++;
							right++;
							left = right;
						}
					}
					else if (isNonzero(str[temp])) {
						right = temp;
						char* subStr = subString(str, left, right);
						table[tableFlag]->tokenType = FLOAT;
						table[tableFlag]->token = subStr;
						tableFlag++;
						right++;
						left = right;
					}
				}
				else {
					printf("Error: there is no floating number after floating point\n");
					right++;
					left = right;
				}
			}
		}
		else if (isNonzero(str[right]) == true || isSign(str[right]) == true) {
			//printf("digit\n");
			int temp = right + 1;
			while (isDigit(str[temp])) {            //숫자토큰
				temp++;
				//printf("temp:%d", temp);
			}
			//printf("%c\n", str[temp]);
			if (isFloatingPoint(str[temp]) == true) {
				right = temp;                  //지금 right는 .에 있음
				if (isDigit(str[right + 1]) == true) {
					temp++;
					while (isDigit(str[temp])) {            //0.xx
						temp++;
						//printf("temp:%d", temp);
					}
					temp--;;
					if (str[temp] == '0') {
						if (temp == right + 1) {         //.0
							right = temp;
							char* subStr = subString(str, left, right);
							table[tableFlag]->tokenType = FLOAT;
							table[tableFlag]->token = subStr;
							tableFlag++;
							right++;
							left = right;
						}
						else {
							do {
								temp--;
							} while (str[temp] != 0);
							right = temp;
							char* subStr = subString(str, left, right);
							table[tableFlag]->tokenType = FLOAT;
							table[tableFlag]->token = subStr;
							tableFlag++;
							right++;
							left = right;
						}
					}
					else if (isNonzero(str[temp])) {
						right = temp;
						char* subStr = subString(str, left, right);
						table[tableFlag]->tokenType = FLOAT;
						table[tableFlag]->token = subStr;
						tableFlag++;
						right++;
						left = right;
					}
				}
				else {
					printf("Error: there is no floating number after floating point\n");
					right++;
					left = right;
				}
			}
			else {
				right = temp - 1;
				char* subStr = subString(str, left, right);
				table[tableFlag]->tokenType = INTEGER;
				table[tableFlag]->token = subStr;               //한자리도 됨?
				tableFlag++;
				right++;
				left = right;
			}
		}
		else if (right + 1 > len || left == right) {
			break;
		}
	}

	return tableFlag;
}

void lexical(void) {
	token* table[MAXTOKEN];
	for (int i = 0; i < MAXTOKEN; i++) {
		table[i] = (token*)malloc(sizeof(token));
	}
	// maximum legth of string is STRING_SIZE here 
	char buffer[STRING_SIZE];
	FILE* fp = NULL;
	fp = fopen("afds.txt", "r");
	if (fp == NULL) {
		printf("%s: 파일이 열리지 않습니다.\n", "afds.txt");
		return 0;
	}
	FILE* wfp = NULL;
	wfp = fopen("lexicalOutput.txt", "wb");
	char* test;
	if (fp != NULL) {
		while (fgets(buffer, STRING_SIZE, fp)) {
			if ((test = strchr(buffer, '\n')) != NULL) *test = '\0';
			char str[STRING_SIZE];
			strcpy(str, buffer);
			int start = tableFlag;
			//printf("start %s\ntableFlag: %d\n", str, tableFlag);
			int tableFlag = parser(str, table);
			//printf("end tableflag: %d\n", tableFlag);
			for (int i = start; i < tableFlag; i++) {
				//printf("for:%d\n", i);
				switch (table[i]->tokenType) {
				case 0:
					printf("|VAR_TYPE,%s|\n", table[i]->token);
					fprintf(wfp, "VAR_TYPE %s$", table[i]->token);
					break;
				case 1:
					printf("|INTEGER,");
					fprintf(wfp, "INTEGER ");
					if (table[i]->token == '0') {
						printf("%c|\n", table[i]->token);
						fprintf(wfp, "%c$", table[i]->token);
					}
					else {
						printf("%d|\n", atoi(table[i]->token));
						fprintf(wfp, "%d$", atoi(table[i]->token));
					}
					break;
				case 2:
					printf("|LITERAL,%s|\n", table[i]->token);
					fprintf(wfp, "LITERAL %s$", table[i]->token);
					break;
				case 3:
					printf("|BOOLEAN,%s|\n", table[i]->token);         //boolean은 output file에 저장하지 않는다(무시)
					break;
				case 4:
					printf("|FLOAT,%s|\n", table[i]->token);
					fprintf(wfp, "FLOAT %s$", table[i]->token);
					break;
				case 5:
					printf("|IDENTIFIER,%s|\n", table[i]->token);
					fprintf(wfp, "IDENTIFIER %s$", table[i]->token);
					break;
				case 6:
					printf("|KEYWORD,%s|\n", table[i]->token);
					fprintf(wfp, "KEYWORD %s$", table[i]->token);
					break;
				case 7:
					printf("|ARITHMETIC,%c|\n", table[i]->token);
					fprintf(wfp, "ARITHMETIC %c$", table[i]->token);
					break;
				case 8:                                       //bitwise는 output file에 저장하지 않는다(무시)
					printf("|BITWISE,");
					if (table[i]->token == '|' || table[i]->token == '&') {
						printf("%c|\n", table[i]->token);
					}
					else {
						printf("%s|\n", table[i]->token);
					}
					break;
				case 9:
					printf("|ASSIGN,%c|\n", table[i]->token);
					fprintf(wfp, "ASSIGN %c$", table[i]->token);
					break;
				case 10:
					printf("|COMPARISON,");
					fprintf(wfp, "COMPARISON ");
					if (table[i]->token == '<' || table[i]->token == '>') {
						printf("%c|\n", table[i]->token);
						fprintf(wfp, "%c$", table[i]->token);
					}
					else {
						printf("%s|\n", table[i]->token);
						fprintf(wfp, "%s$", table[i]->token);
					}
					break;
				case 11:
					printf("|TERMINATE,%c|\n", table[i]->token);
					fprintf(wfp, "TERMINATE %c$", table[i]->token);
					break;
				case 12:
					printf("|LBRACKET,%c|\n", table[i]->token);
					fprintf(wfp, "LBRACKET %c$", table[i]->token);
					break;
				case 13:
					printf("|RBRACKET,%c|\n", table[i]->token);
					fprintf(wfp, "RBRACKET %c$", table[i]->token);
					break;
				case 14:
					printf("|COMMA,%c|\n", table[i]->token);
					fprintf(wfp, "COMMA %c$", table[i]->token);
					break;
				case 15:
					printf("|LPAREN,%c|\n", table[i]->token);
					fprintf(wfp, "LPAREN %c$", table[i]->token);
					break;
				case 16:
					printf("|RPAREN,%c|\n", table[i]->token);
					fprintf(wfp, "RPAREN %c$", table[i]->token);
					break;
				case 17:                                 //white space는 outputfile에 저장하지 않는다(버림)
					printf("|WHITESPACE, |\n");            //whitespace는 출력 되도 안된것처럼 보임
														   //printf("%c|\n", table[i]->token);
					break;
				}
			}
		}
	}

	fclose(wfp);
	fclose(fp);
	return 0;
}

void main() {
	lexical();
}