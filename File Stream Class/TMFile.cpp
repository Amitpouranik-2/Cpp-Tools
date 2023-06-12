#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
class OutputFileStream
{
private:
FILE *f;
int mode;
int lastOperationFailed;
public:
const static int append =1;
const static int overwrite =2;
OutputFileStream()
{
this->lastOperationFailed=0;
this->f = NULL;
this->mode = -1;
}
OutputFileStream(const char *FileName , int mode)
{
this->lastOperationFailed=0;
this->f =NULL;
this->mode =-1;
open(FileName , mode);
}
void open(const char *FileName , int mode)
{
if(f!=NULL)
{
fclose(f);
this->f = NULL;
this->mode =-1;
}
this->lastOperationFailed=1;
if(FileName == NULL) return;
if(mode!= append && mode!= overwrite) return;
if(mode== append)
{
f = fopen(FileName , "a");
}
else if(mode== overwrite)
{
f= fopen(FileName , "w");
}
if(f== NULL) return;
this->lastOperationFailed =0 ;
}
 void close()
{
this->lastOperationFailed =0;
if(this->f== NULL) return;
fclose(this->f);
}

int fail()
{
return this->lastOperationFailed;
}

OutputFileStream & operator<<(char c)
{
this->lastOperationFailed =1;
if(this->f == NULL) return *this;
fputc(c ,this->f);
this->lastOperationFailed =0;
return *this;
}
};

class InputfileStream
{
private:
FILE *f;
int  lastOperationFailed;
public:
InputfileStream()
{
this->f =NULL;
this->lastOperationFailed = 0;
}
InputfileStream(const char *FileName  )
{
this->f =NULL;
this->lastOperationFailed= 0;
open(FileName);
}
void open(const char *FileName)
{
if(this->f!=NULL)
{
fclose(this->f);
this->lastOperationFailed=0;
}
this->lastOperationFailed=1;
if(FileName == NULL) return;
this->f = fopen(FileName , "r");
if(this->f== NULL) return ;
this->lastOperationFailed=0;
}

int fail()
{
return this->lastOperationFailed;
}

InputfileStream  & operator>> (char &c)
{
this->lastOperationFailed=1;
if(this->f== NULL) return *this;
if(feof(this->f)) return *this;
c = fgetc(this->f);
if(feof(this->f)) return *this;
this->lastOperationFailed=0;
return *this;
} 

void close ()
{
this->lastOperationFailed=0;
if(this->f!= NULL) fclose(this->f);
}
};

void Addfriends()
{
char name[21] , contactNumber[81];
cout<<"Enter Name:";
fgets(name, 22 , stdin);
fflush(stdin);
name[strlen(name)-1 ] = '\0';
int i;
for(i=0; name[i]!= '\0'; i++)
{
if(name[i]== '!')
{
cout<<"Name cannot contain this ! symbol"<<endl;
return;
}
} 
cout<<"Enter Contact Number:";
fgets(contactNumber, 82 ,stdin);
fflush(stdin);
contactNumber[strlen(contactNumber)-1] = '\0';
for(i=0; contactNumber[i]!= '\0'; i++)
{
if(contactNumber[i]== '!')
{
cout<<"Name cannot contain  ! symbol "<<endl;
return;
}
}
OutputFileStream  f("friends.ddd", OutputFileStream::append);
i=0;
while(name[i]!='\0')
{
f<<name[i];
i++;
}
f<<'!';
i=0;
while(contactNumber[i]!='\0')
{
f<<contactNumber[i];
i++;
}
f<<'!';
f.close();
cout<<"friends added "<<endl;
}
void DisplayListoffriends()
{
InputfileStream  k("friends.ddd");
if(k.fail())
{
cout<<"no friends added"<<endl;
return;
}
char nm[21];
char cn[82];
int x;
char m;
while(1)
{
k>>m;
if(k.fail()) break;
nm[0] = m;
x=1;
while(1)
{
k>>m;
if(m== '!') break;
nm[x] = m;
x++;
}
nm[x] = '\0';
x=0;
while(1)
{
k>>m;
if(m=='!') break;
cn[x] = m;
x++;
}
cn[x] = '\0';
cout<<"Name:"<<nm<<","<<"ContactNumber:"<<cn<<endl;
}
k.close();
}


int main ()
{
int ch;
while(1)
{
cout<<"1. Add Friends:"<<endl;
cout<<"2. Display List Of Frnds:"<<endl;
cout<<"3. EXIT"<<endl;
cout<<"Enter your Choice:";
scanf("%d" , &ch);
fflush(stdin);
if(ch==1) Addfriends();
if(ch==2) DisplayListoffriends();
if(ch==3) break;
}
return 0;
}



