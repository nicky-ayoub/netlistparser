%{
   #include"cdlParser.tab.h"
   #include<stdlib.h>
   #include<string.h>

%}

%%
[ \t\n]+ {}
^[m|M][0-9a-zA-Z_]+ {return TRANS;}
^[c|C][0-9a-zA-Z_]+ {return CAP;}
^[x|X][0-9a-zA-Z_]+ {return INSTANCE;}
^[d|D][0-9a-zA-Z_]+ {return DIODE;}
^[r|R][0-9a-zA-Z_]+ {return RESISTOR;}
[0-9\.-]+ {yylval.val=atof(yytext);return FNUMBER;}
\= {return EQUAL;}
^.ENDS {return ENDS;}
^.SUBCKT {return SUBCKT;}
^\+ {}
[a-zA-Z0-9_\-\[\]]* {
		      if(!strcmp(yytext,"U") || !strcmp(yytext,"u"))
		      {
		         return MICRON;
		      }
		      /*else if(!strcmp(yytext,"L"))
		      {
		          return LEN;
		      }	  
		      else if(!strcmp(yytext,"W"))
		      {
		          return WID;
		      }	*/ 
		      else
		      {
		          yylval.string=strdup(yytext);
		          return NAME;
	              }		  
	      }
%%

int yywrap()
{
   return 1;
}

void yyerror(const char *s)
{
   printf("\n\n%s at line no: in the line \n",s);
}
