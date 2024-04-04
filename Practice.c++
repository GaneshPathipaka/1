//1.FOLLOW


#include<bits/stdc++.h>
using namespace std;

int m=0,n;
char a[10][10],followResult[10];

void FOLLOW(char c);
void FIRST(char c);

void FOLLOW(char c){
	if(c==a[0][0]){
		followResult[m++]='$';
	}
	for(int i=0;i<n;i++){
		for(int j=2;j<strlen(a[i]);j++){
			if(a[i][j]==c){
				if(a[i][j+1]!='\0'){
					FIRST(a[i][j+1]);
				}
				if(a[i][j+1]=='\0' && c!=a[i][0]){
					FOLLOW(a[i][0]);
				}
			}
		}
	}
}

void FIRST(char c){
	if(!(isupper(c))){
		followResult[m++]=c;
	}
	for (int k=0;k<n;k++){
		if(a[k][0]==c){
			if(a[k][2]=='$'){
				FOLLOW(a[k][0]);
			}
			else if(islower(a[k][2])){
				followResult[m++]=a[k][2];
			}
			else{
				FIRST(a[k][2]);
			}
		}
	}
}

int main(){
	char c,choice;
	cout<<"Enter no of Productions : ";
	cin>>n;
	cout<<"Enter Productions : "<<endl;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	
	do{
		m=0;
		cout<<"Find Follow of : ";
		cin>>c;
		FOLLOW(c);
		cout<<"FOLLOW of  ("<<c<<") = { ";
		for(int i=0;i<m;i++){
			cout<<followResult[i]<<" ";
		}
		cout<<"}"<<endl;
		cout<<"Enter 'Y' to continue :";
		cin>>choice;
	}
	while(choice=='Y' or choice=='y');
	
	
	return 0;
}

/*
Enter no of Productions : 9
Enter Productions : 
S-aBDh
B-cC
c-bc
C-$
D-EF
E-g
E-$
F-f
F-$
Find Follow of : S
FOLLOW of  (S) = { $ }
Enter 'Y' to continue :Y
Find Follow of : B
FOLLOW of  (B) = { g f h }
Enter 'Y' to continue :Y
Find Follow of : C
FOLLOW of  (C) = { g f h }
Enter 'Y' to continue :Y
Find Follow of : D
FOLLOW of  (D) = { h }
Enter 'Y' to continue :Y
Find Follow of : E
FOLLOW of  (E) = { f h }
Enter 'Y' to continue :Y
Find Follow of : F
FOLLOW of  (F) = { h }
Enter 'Y' to continue :N

*/


//2.FIRST


#include<bits/stdc++.h>
using namespace std;

int numOfProductions;
char productionSet[10][10];

void addToResultSet(char Result[],char val){
	int k;
	for(k=0;Result[k]!='\0';k++){
		if(Result[k]==val){
			return;
		}
	}
	Result[k]=val;
	Result[k+1]='\0';
}

void FIRST(char* Result,char c){
	int i,j,k;
	char subResult[20];
	int foundEpsilon;
	subResult[0]='\0';
	Result[0]='\0';
	
	if(!(isupper(c))){
		addToResultSet(Result,c);
		return;
	}
	
	for(i=0;i<numOfProductions;i++){
		if(productionSet[i][0]==c){
			if(productionSet[i][2]=='$'){
				addToResultSet(Result,'$');
			}
			else{
				j=2;
				while(productionSet[i][j]!='\0'){
					foundEpsilon=0;
					FIRST(subResult,productionSet[i][j]);
					for(k=0;subResult[k]!='\0';k++){
						addToResultSet(Result,subResult[k]);
					}
					for(k=0;subResult[k]!='\0';k++){
						if(subResult[k]=='$'){
							foundEpsilon=1;
							break;
						}
					}
					if(!foundEpsilon){
						break;
					}
					j++;
				}	
			}
		}
	}
	return;
}

int main(){
	int i;
	char choice;
	char c;
	char result[20];
	
	cout<<"How Many number of productions ? :"<<endl;
	cin>>numOfProductions;
	
	for(int i=0;i<numOfProductions;i++){
		cout<<"Enter productions Number "<<i+1<<" : "<<endl;
		cin>>productionSet[i];
	}
	
	do{
		cout<<"Find the FIRST of : ";
		cin>>c;
		FIRST(result,c);
		cout<<" FIRST("<<c<<")"<<"= { ";
		for(i=0;result[i]!='\0';i++){
			cout<<result[i]<<" ";
		}
		cout<<"}"<<endl;
		cout<<"Enter 'y' to continue : ";
		cin>>choice;
		cout<<endl;
	}
	while(choice=='y' || choice=='Y');
	
	return 0;
}


/*
ganesh@sampu:~/Desktop/CDLAB$ g++ FIRST.c++ 
ganesh@sampu:~/Desktop/CDLAB$ ./a.out 
How Many number of productions ? :
9
Enter productions Number 1 : 
S-aBDh
Enter productions Number 2 : 
B-cC
Enter productions Number 3 : 
C-bc
Enter productions Number 4 : 
C-$
Enter productions Number 5 : 
D-EF
Enter productions Number 6 : 
E-g
Enter productions Number 7 : 
E-$
Enter productions Number 8 : 
F-f
Enter productions Number 9 : 
F-$
Find the FIRST of : S
 FIRST(S)= { a }
Enter 'y' to continue : y

Find the FIRST of : b
 FIRST(b)= { b }
Enter 'y' to continue : Y

Find the FIRST of : B
 FIRST(B)= { c }
Enter 'y' to continue : Y

Find the FIRST of : C
 FIRST(C)= { b $ }
Enter 'y' to continue : Y

Find the FIRST of : D
 FIRST(D)= { g $ f }
Enter 'y' to continue : Y

Find the FIRST of : E
 FIRST(E)= { g $ }
Enter 'y' to continue : Y

Find the FIRST of : F
 FIRST(F)= { f $ }
Enter 'y' to continue : N

ganesh@sampu:~/Desktop/CDLAB$ 


*/

//3.Shift Reduce Parser

#include <iostream>
#include <cstring>

struct ProductionRule
{
    char left[10];
    char right[10];
};

int main()
{
    char input[20], stack[50], temp[50], ch[2], *token1, *token2, *substring;
    int i, j, stack_length, substring_length, stack_top, rule_count = 0;
    struct ProductionRule rules[10];
    stack[0] = '\0';

    // User input for the number of production rules
    std::cout << "\nEnter the number of production rules: ";
    std::cin >> rule_count;

    // User input for each production rule in the form 'left->right'
    std::cout << "\nEnter the production rules (in the form 'left->right'):\n";
    for (i = 0; i < rule_count; i++)
    {
        std::cin >> temp;
        token1 = strtok(temp, "->");
        token2 = strtok(NULL, "->");
        strcpy(rules[i].left, token1);
        strcpy(rules[i].right, token2);
    }

    // User input for the input string
    std::cout << "\nEnter the input string: ";
    std::cin >> input;
    i = 0;
    while (1)
    {
        // If there are more characters in the input string, add the next character to the stack
        if (i < strlen(input))
        {
            ch[0] = input[i];
            ch[1] = '\0';
            i++;
            strcat(stack, ch);
            std::cout << stack << "\t";
            for (int k = i; k < strlen(input); k++)
            {
                std::cout << input[k];
            }
            std::cout << "\tShift " << ch << std::endl;
        }

        // Iterate through the production rules
        for (j = 0; j < rule_count; j++)
        {
            // Check if the right-hand side of the production rule matches a substring in the stack
            substring = strstr(stack, rules[j].right);
            if (substring != NULL)
            {
                // Replace the matched substring with the left-hand side of the production rule
                stack_length = strlen(stack);
                substring_length = strlen(substring);
                stack_top = stack_length - substring_length;
                stack[stack_top] = '\0';
                strcat(stack, rules[j].left);
                std::cout << stack << "\t";
                for (int k = i; k < strlen(input); k++)
                {
                    std::cout << input[k];
                }
                std::cout << "\tReduce " << rules[j].left << "->" << rules[j].right << std::endl;
                j = -1; // Restart the loop to ensure immediate reduction of the newly derived production rule
            }
        }

        // Check if the stack contains only the start symbol and if the entire input string has been processed
        if (strcmp(stack, rules[0].left) == 0 && i == strlen(input))
        {
            std::cout << "\nAccepted";
            break;
        }

        // Check if the entire input string has been processed but the stack doesn't match the start symbol
        if (i == strlen(input))
        {
            std::cout << "\nNot Accepted";
            break;
        }
    }

    return 0;
}

/*
Enter the number of production rules: 4

Enter the production rules (in the form 'left->right'):
E->E+E
E->E*E
E->(E)
E->i

Enter the input string: i*i+i
i	*i+i	Shift i
E	*i+i	Reduce E->i
E*	i+i	Shift *
E*i	+i	Shift i
E*E	+i	Reduce E->i
E	+i	Reduce E->E*E
E+	i	Shift +
E+i		Shift i
E+E		Reduce E->i
E		Reduce E->E+E

Accepted
*/


//4.vowels lex 

%{
	#include<bits/stdc++.h>
	int vow_count=0;
	int const_count=0;
%}

%%
[aeiouAEIOU] {vow_count++;}
[a-zA-Z] {const_count++;}
%%

int yywrap(){return 1;}

int main(){
	std::cout<<"Enter the string : "<<std::endl;
	yylex();
	std::cout<<"no of vowels : "<<vow_count<<std::endl;
	std::cout<<"no of consonants : "<<const_count;

	return 0;
}

/*
ganesh@sampu:~/Desktop/CDLAB$ flex code1.l
ganesh@sampu:~/Desktop/CDLAB$ g++ lex.yy.c -lfl
ganesh@sampu:~/Desktop/CDLAB$ ./a.out 
Enter the string : 
ganesh
no of vowels : 2
no of consonants : 4
*/

//5.Spaces Count lex 

%{
	#include<bits/stdc++.h>
	int lc=0,sc=0,tc=0,ch=0,c=0,wc=0;
%}

%%
\n {lc++;}
([ ])+ {sc++;}
\t {tc++;}
. {ch++;c++;}
[a-zA-Z0-9]+ {wc++;c=c+yyleng;}

%%

int yywrap(){return 1;}
int main(){
	yylex();
	std::cout<<"Lines Count is : "<<lc<<std::endl;
	std::cout<<"Spaces Count is : "<<sc<<std::endl;
	std::cout<<"Tabs Count is : "<<tc<<std::endl;
	std::cout<<"Characters Count is : "<<c<<std::endl;
	std::cout<<"Words Count is : "<<wc+ch<<std::endl;
	return 0;
} 

//6.Float Int lex 

%{
	#include<bits/stdc++.h>
	int numOfInt=0,numOfFloat=0;
%}

%%
[0-9]+"."[0-9]+ {ECHO;std::cout<<" : Float Number"<<std::endl;numOfFloat++;}
[0-9]+ {ECHO;std::cout<<" : Integer Number"<<std::endl;numOfInt++;}
%%

int yywrap(){
	return 1;
}

int main(){

	std::cout<<"Enter Numbers : ";
	yylex();
	std::cout<<"Total count of Float Numbers : "<<numOfFloat<<std::endl;
	std::cout<<"Total count of Integer Numbers : "<<numOfInt<<std::endl;
	return 0;
}

//7.letter A lex 

%{
	#include<bits/stdc++.h>
	int length;
	void fun(int length);
%}

%%
[a-zA-Z0-9]+ {length=yyleng;fun(length);}
%%

void fun(int length){
	if(yytext[0]=='A'){
		if(length==3){
			std::cout<<yytext<<" is word with length 3"<<std::endl;
		}
		else{
			std::cout<<"Word is not of  length 3"<<std::endl;
		}
	}
	else{
		std::cout<<"Word is not starting with A"<<std::endl;
	}
}

int yywrap(){
	return 1;
}
int main(){
	std::cout<<"Enter Words : "<<std::endl;
	yylex();
	return 0;
} 

//8. comments lex 

%{
	#include<bits/stdc++.h>
%}

%%
\/\/(.*) {std::cout<<"It is a single line command"<<yytext<<std::endl;}
\/\*(.*\n)*.*\*\/ {std::cout<<"It is a Multiple line command"<<yytext<<std::endl;}
%%

int yywrap(){
	return 1;
}

int main(){
	yyin=fopen("input5.c++","r");
	yyout=fopen("out.c++","w");
	yylex();
	return 0;
}

//input5.c++

/*program to print welcome message*/
#include<bits/stdc++.h>
using namespace std;

int main(){
//declaration
std::cout<<"Welcome"<<std::endl;
//end
} 

//out.c++ 


#include<bits/stdc++.h>
using namespace std;

int main(){

std::cout<<"Welcome"<<std::endl;

}


//Extra 

//Even or odd 

%{
#include <stdio.h>
%}

DIGIT   [0-9]
%%
{DIGIT}+ {
    int num = atoi(yytext);
    if(num % 2 == 0) {
        printf("%s is even\n", yytext);
    } else {
        printf("%s is odd\n", yytext);
    }
}
.|\n    ;

%%
int main() {
    yylex();
    return 0;
}


//prime number

%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
%}

DIGIT [0-9]
%%
{DIGIT}+   {
            int num = atoi(yytext);
            bool is_prime = true;
            if (num <= 1)
                is_prime = false;
            else if (num <= 3)
                is_prime = true;
            else if (num % 2 == 0 || num % 3 == 0)
                is_prime = false;
            else {
                int i = 5;
                while (i * i <= num) {
                    if (num % i == 0 || num % (i + 2) == 0) {
                        is_prime = false;
                        break;
                    }
                    i += 6;
                }
            }
            if (is_prime)
                printf("%d is prime\n", num);
            else
                printf("%d is not prime\n", num);
        }
.|\n        ;
%%

int main() {
    yylex();
    return 0;
}




