%{

#include<stdio.h>
#include<stdlib.h>
#include"netlistclasses.hpp"
#include"netlistfunctions.hpp"
void yyerror(const char *s);
int yylex(void);



//GLOBAL Variable section

class netlist *mynetlist=new netlist;
class subckt *tempsubckt;
class device *mydevice;
class prop *myprop;


%}

%union{
    char *string;
    float val;
}

%token <string> NAME
%token <val> FNUMBER
%token SUBCKT ENDS EQUAL MICRON WID ENDLINE LEN TRANS CAP INSTANCE DIODE RESISTOR

%%

cdlfile: subckts
;

subckts: subckt| subckt subckts {}
;

subckt: SUBCKT NAME {tempsubckt=mynetlist->addsubckt($2);tempsubckt->devices=new devicelist();} ports elements ENDS NAME {}
;

ports: port | port ports {}
;

port: NAME {}
;

elements: element | element elements {}
;

element:  xelements | melements | delements | ENDLINE {}
;

melements: TRANS NAME NAME NAME NAME NAME props {mydevice=tempsubckt->devices->adddevice(1);mydevice->dev->set($2,$3,$4,$5,$6);}
;

props: prop | prop props {}
;

prop: NAME EQUAL FNUMBER units {myprop=mydevice->dev->props->addprop();myprop->set($1,$3,"U");}
;

units: MICRON {}
;

xelements: INSTANCE ports {}
;

delements: DIODE NAME NAME NAME FNUMBER NAME FNUMBER MICRON {mydevice=tempsubckt->devices->adddevice(2);mydevice->dev->set($2,$3,$4);}
;

%%

int main()
{
    yyparse();
    mynetlist->printall();
    return 0;
}
