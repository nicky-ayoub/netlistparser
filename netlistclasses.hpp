// netlistclass.hpp : This hpp file contains all the classes used to
// hold a netlist in the memory
// ERROR-RANGE 40-80

#include<string.h>

class prop
{
	private:
		char *property;
		double value;
		double multiplier;
	public:
		class prop *next;
		prop(void) {next=NULL;}
		void set(char *name,double val,char *unit);
};

class proplist
{
	private:
		class prop *head,*current,*loopvar;
	public:
		proplist(void) {head=current=loopvar=NULL;}
		class prop *addprop(void);
		void printall(void);
};

class basedevice
{
	public:
		virtual void set(char *d, char *g, char *s, char *b, char *mname)=0;
		virtual void set(char *node1, char *node2, char *modelname)=0;
		virtual void printall(void)=0;
		class proplist *props;
};

class mos:public basedevice
{
	private:
		char *drain,*gate,*source,*bulk,*modelname;
		class proplist *props;
	public:
		mos(void){props=new proplist;}
		void set(char *d, char *g, char *s, char *b, char *mname);
		void set(char *node1, char *node2, char *modelname){}; // Not used here
		void printall(void);
};

class diode:public basedevice
{
	private:
		char *node1,*node2,*modelname;
		class proplist *props;
	public:
		diode(void){props=new proplist;}
		void set(char *d, char *g, char *s, char *b, char *mname){}// Not used here
		void set(char *n1, char *n2, char *mname); 
		void printall(void);
};

class device
{
	public:
		class basedevice *dev;
		class device *next;
		device(void) {next=NULL;}
		void printall(void){dev->printall();};
};

class devicelist
{
	private:
		class device *head,*current,*looptemp;
	public:
		devicelist(void){head=current=NULL;}
		class device *adddevice(int d);
		void printall(void);
};

class subckt
{
	public:
		class devicelist *devices;
		class subckt *next;
		//class portlist *ports;
		char *subcktname;

		subckt(char *name) {next=NULL; subcktname=(char *)malloc(strlen(name)+1); strcpy(subcktname,name);}
		void printall(void);
};

class netlist
{
	private:
		class subckt *head,*current,*looptemp;
	public:
		netlist(void) {head=current=NULL;}
		class subckt *addsubckt(char *name);
		void printall(void);
};
