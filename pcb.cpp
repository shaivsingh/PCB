#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
char status[][15]={"Ready","Running","Waiting","Terminated"};
int new_priority=0;
class Thread{
	public:
		int p_id;
		char *p_name[];
		char *file_name[];
		int n_char;
		int n_line;
		char *p_status[];
		int p_priority;
		int p_position;
		int interrupt(int p)
		{
			if(p>=new_priority)
				return 0;
			else
				return 1;
		}
};
class Thread1:public Thread{
	public:
		int lines_printed=0;
		Thread1()
		{
			p_id=1401;
			p_name[20]="Thread1";
			file_name[40]="sample1.txt";
			n_char=4900;
			n_line=100;
			p_status[15]=status[0];
			p_priority=1;
			cout<<endl<<p_id<<" is "<<p_status[15]<<endl;
			
		}
		int process()
		{
			p_status[15]=status[1];
			int i,count=0,cur=0,line=0;
			char c;
			char s[]="A Quick Brown Fox Jumps Over the Little Lazy Dog.";
			fstream f;
			
			f.open(file_name[40],ios::app);
			
			cout<<endl<<p_id<<" is "<<p_status[15]<<endl;
			for(i=lines_printed;i<=100;i++)
			{
				if(i==23)
				{
					
					cur=f.tellg();
					
					//n_char=count;
					//n_line=line;
					p_position=cur;
		
					
					//cout<<endl<<"No of character: "<<n_char<<endl;
					
					if(interrupt(p_priority))
					{
						p_status[15]=status[2];
						cout<<endl<<p_id<<" is "<<p_status[15]<<endl;
						cout<<endl<<"No of lines_Printed : "<<line<<endl;
						cout<<endl<<"Current position of curser: "<<p_position<<endl;
						f.close();
						return line;;
					}
					i++;
		
				}
				Sleep(1000);
				cout<<"-";
				f<<s;
				line++;
				
			}
			cur=f.tellg();
			f.close();
			f.open(file_name[40],ios::in);
			while(f.get(c))
			{
				count++;
			}
			f.close();
			p_status[15]=status[3];
			//n_char=count;
			line=line+lines_printed-1;
			p_position=cur;
		
		
			cout<<endl<<"No. of Lines_Printed : "<<line<<endl;
			cout<<endl<<"No. of Character_Printed : "<<count<<endl;
			if(line==n_line&&count==n_char)
			{
				p_status[15]=status[3];
				cout<<endl<<p_name[20]<<" is "<<p_status[15]<<endl;
				
			}
			//cout<<endl<<"Current Position of Cursor : "<<p_position<<endl;
			return line;
		}
		
};
class Thread2:public Thread{
	public:
		Thread2()
		{
			p_id=1402;
			p_name[20]="Thread2";
			file_name[40]="process2.txt";
			n_char=2400;
			n_line=50;
			p_status[15]="Ready";
			p_priority=2;
			new_priority=p_priority;
			
		}
		int process()
		{
			
			char s1[]="We Reached to Process Two and Its On Completion.";
			char c;
			int i,count=0,line=0;
			fstream f1;
			p_status[15]=status[1];
			cout<<endl<<p_id<<" is "<<p_status[15]<<endl;
			f1.open(file_name[40],ios::out);
			for(i=0;i<50;i++)
			{
				f1<<s1;
				Sleep(1000);
				cout<<"-";
				line++;
			}
			f1.close();
			f1.open(file_name[40],ios::in);
			while(f1.get(c))
			{
				count++;
			}
			f1.close();
			//n_line=line;
			//n_char=count;
			cout<<endl<<"No. of Lines_Printed : "<<line<<endl;
			cout<<endl<<"No. of Character_Printed : "<<count<<endl;
			//check2=1;
			if(line==n_line&&count==n_char)
			{
				p_status[15]=status[3];
				cout<<endl<<p_name[20]<<" is "<<p_status[15]<<endl;
			}
			p_status[15]=status[4];
		}
};

int main()
{
	Thread1 th1;
	Thread2 th2;
	int c;
	int lines_to_print=th1.n_line;

	c=th1.process();
	//cout<<lines_to_print<<endl<<c<<endl;
	th2.process();
	if(c!=lines_to_print)
	{
		c++;
		th1.lines_printed=c;
		c=th1.process();
	}
	return 0;	
}
