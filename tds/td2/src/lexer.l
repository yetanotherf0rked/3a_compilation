%{
#include <string.h>	/* for strcmp, strdup & friends */
#include <stdio.h>	/* for strcmp, strdup & friends */
#include <stdlib.h>	/* for atoi() */

#include "parser.h"	/* (TK_) symbols from parser.y */

extern int line_number;	/* defined in parser.ypp */
%}

%x comment
%x asm

%%
[ \t\r]			break;		/* ignore white space */
"\n" 			++line_number; 

"("                     return TK_LPAR;
")"                     return TK_RPAR;
","                     return TK_COMMA;
";"                     return TK_SEMI;
"{"                     return TK_LACC;
"}"                     return TK_RACC; 

">"                     return TK_GREATER;
"=="                    return TK_EQ;
"!="                    return TK_NEQ;

"+"                     return TK_PLUS;
"-"                     return TK_MINUS;
"*"                     return TK_MUL;
"/"                     return TK_DIV;
"++"                    return TK_PLUSPLUS;

"int"                   return TK_INT_TYPE;
"void"                  return TK_VOID_TYPE;

"="                     return TK_ASSIGN; 

"if"                    return TK_IF;
"else"                  return TK_ELSE;
"while"                 return TK_WHILE;
"do"                    return TK_DO;
"return"                return TK_RETURN;

"print"                 return TK_PRINT;
"input"                 return TK_INPUT;

"//"                    BEGIN(comment);   //
<comment>[^\n]          break;            //
<comment>\n             {                 // Comments handling
                          BEGIN(INITIAL); //
                          line_number++;  //
                        }                 //

[0-9]+                  { 
                          yylval.integer = atoi(yytext); 
                          return TK_NUM; 
                        }

\"[^\n]*\"              {
                          yylval.id_string = strdup(yytext);
                          return TK_STRING; 
                        }


\'[^\n]\'               {
                          yylval.integer = (int)(yytext[1]); 
                          return TK_CHAR; 
                        }

[A-Za-z_]([A-Za-z0-9_])* {
                          yylval.id_string = strdup(yytext);
                          //cout << yylval.id_string << endl;
                          return TK_ID;
                        }

.			{ 
                          fprintf(stderr,"line %d: error: illegal character\n", 
                                  line_number); 
                          exit(1);
                        }

