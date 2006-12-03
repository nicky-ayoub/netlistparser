#include<string.h>


void mos::set(char *d, char *g, char *s, char *b, char *mname)
{
	drain=(char *)malloc(strlen(d));
	if(drain==NULL)
	{
		printf("Unable to allocate memory in function device set for mos (netlistfunctions.hpp)\n");
		exit(42);
	}
	strcpy(drain,d);

	gate=(char *)malloc(strlen(g));
	if(gate==NULL)
	{
		printf("Unable to allocate memory in function device set for mos (netlistfunctions.hpp)\n");
		exit(42);
	}
	strcpy(gate,g);
	
	source=(char *)malloc(strlen(s));
	if(source==NULL)
	{
		printf("Unable to allocate memory in function device set for mos (netlistfunctions.hpp)\n");
		exit(42);
	}
	strcpy(source,s);
	
	bulk=(char *)malloc(strlen(b));
	if(bulk==NULL)
	{
		printf("Unable to allocate memory in function device set for mos (netlistfunctions.hpp)\n");
		exit(42);
	}
	strcpy(bulk,b);
	
	modelname=(char *)malloc(strlen(mname));
	if(modelname==NULL)
	{
		printf("Unable to allocate memory in function device set for mos (netlistfunctions.hpp)\n");
		exit(42);
	}
	strcpy(modelname,mname);
}
void diode::set(char *n1, char *n2, char *mname)
{
	node1=(char *)malloc(strlen(n1));
	if(node1==NULL)
	{
		printf("Unable to allocate memory in function device set for diode (netlistfunctions.hpp)\n");
		exit(43);
	}
	strcpy(node1,n1);

	node2=(char *)malloc(strlen(n2));
	if(node2==NULL)
	{
		printf("Unable to allocate memory in function device set for diode (netlistfunctions.hpp)\n");
		exit(43);
	}
	strcpy(node2,n2);

	modelname=(char *)malloc(strlen(mname));
	if(modelname==NULL)
	{
		printf("Unable to allocate memory in function device set for mos (netlistfunctions.hpp)\n");
		exit(42);
	}
	strcpy(modelname,mname);
}	

class device *devicelist::adddevice(int d)
{
	if(head==NULL)
	{
		current=head=new device;
		if(head==NULL)
		{
			printf("Unable to allocate memory in function adddevice (netlistfunctions.hpp)\n");
			exit(39);
		}
	}
	else
	{
		current->next=new device;
		if(current->next==NULL)
		{
			printf("Unable to allocate memory in function adddevice (netlistfunctions.hpp)\n");
			exit(39);
		}
		current=current->next;
	}
	switch(d)
	{
		case 1:
			current->dev=new mos;
			break;
		case 2:
			current->dev=new diode;
			break;
	}
	return(current);
};

class subckt *netlist::addsubckt(char *name)
{
	if(head==NULL)
	{
		current=head=new subckt(name);
		if(head==NULL)
		{
			printf("Unable to allocate memory in function addsubckt (netlistfunctions.hpp)\n");
			exit(40);
		}
	}
	else
	{
		current->next=new subckt(name);
		if(current->next==NULL)
		{
			printf("Unable to allocate memory in function addsubckt (netlistfunctions.hpp)\n");
			exit(41);
		}
		current=current->next;
	}
	return(current);
}

void netlist::printall(void)
{
	looptemp=head;
	while(looptemp!=NULL)
	{
		looptemp->printall();
		looptemp=looptemp->next;
	}
}

void subckt::printall(void)
{
	printf("SUBCKT = %s\n",subcktname);
	devices->printall();
}

void devicelist::printall(void)
{
	looptemp=head;
	while(looptemp!=NULL)
	{
		looptemp->printall();
		looptemp=looptemp->next;
	}
}

void mos::printall(void)
{
	printf("Drain = %s Gate = %s Source = %s Bulk = %s ModelName = %s\n",drain,gate,source,bulk,modelname);
}

void diode::printall(void)
{
	printf("Node1 = %s Node2 = %s ModelName = %s\n",node1,node2,modelname);
}


class prop *proplist::addprop(void)
{
	printf("Got into prop->addprop\n");
	if(head==NULL)
	{
		head=current=new prop;
		if(head==NULL)
		{
			printf("Error in allocating memory in the function addprop (netlistfunctions.hpp)\n");
			exit(46);
		}
	}
	else
	{
		current->next=new prop;
		if(current->next==NULL)
		{
			printf("Error in allocating memory in the function addprop (netlistfunctions.hpp)\n");
			exit(46);
		}
	}
	current=current->next;
	return(current);
}
void prop::set(char *name,double val,char *unit)
{
	printf("Got into prop->set\n");
	property=(char *)malloc(strlen(name));
	if(property==NULL)
	{
		printf("Error in allocating memory in the function addprop (netlistfunctions.hpp)\n");
		exit(47);
	}
	strcpy(property,name);
	
	value=val;
	
	if(!strcmp(unit,"U"))
	{
		multiplier=1e-6;
	}
	if(!strcmp(unit,"n"))
	{
		multiplier=1e-9;
	}
	if(!strcmp(unit,"p"))
	{
		multiplier=1e-12;
	}
}
