#include "header.h"

char hexget(char *in){
char tmp[3];
tmp[0]=in[0];tmp[1]=in[1];tmp[2]=0;
return((char)strtol(tmp, 0, 16));}

int main(int ac, char *av[]){
char *MP, *MPM, *MPS;
int cnt, cnt2;
FILE *fp;

errexit(ac,4,"chikanu v0.4u by jarupxx\n\
Usage: chikan targetfile beforestring afterstring\n\
\n\
 /n   = LF          /r   = CR\n\
 /s   = Space       /t   = Tab\n\
 /m   = '>'         /h   = '<'\n\
 /q   = '?'         /a   = '*'\n\
 /d   = '$'         /=   = '~'\n\
 //   = '/'         /x** = Hexadecimal form\n\
\n");

MPM=malloc(strlen(av[2]));openerr(MPM);
MPS=malloc(strlen(av[3]));openerr(MPS);

cnt=0;cnt2=0;
while(av[2][cnt]!=0){
 if(av[2][cnt]=='/' && av[2][cnt+1]!=0){
 if(av[2][cnt+1]=='n'){MPM[cnt2]='\n';}else
 if(av[2][cnt+1]=='r'){MPM[cnt2]='\r';}else
 if(av[2][cnt+1]=='s'){MPM[cnt2]=' ';}else
 if(av[2][cnt+1]=='/'){MPM[cnt2]='/';}else
 if(av[2][cnt+1]=='m'){MPM[cnt2]='>';}else
 if(av[2][cnt+1]=='h'){MPM[cnt2]='<';}else
 if(av[2][cnt+1]=='t'){MPM[cnt2]='\t';}else
 if(av[2][cnt+1]=='q'){MPM[cnt2]='?';}else
 if(av[2][cnt+1]=='a'){MPM[cnt2]='*';}else
 if(av[2][cnt+1]=='d'){MPM[cnt2]='$';}else
 if(av[2][cnt+1]=='='){MPM[cnt2]='~';}else
 if(av[2][cnt+1]=='x'){MPM[cnt2]=hexget(av[2]+cnt+2);cnt+=2;}else
 if(av[2][cnt+1]=='X'){MPM[cnt2]=hexget(av[2]+cnt+2);cnt+=2;}else
 {MPM[cnt2]=av[2][cnt+1];}
cnt++;
}
else{MPM[cnt2]=av[2][cnt];}
cnt++;cnt2++;
}
MPM=realloc(MPM,cnt2);openerr(MPM);

cnt=0;cnt2=0;
while(av[3][cnt]!=0){
 if(av[3][cnt]=='/' && av[3][cnt+1]!=0){
 if(av[3][cnt+1]=='n'){MPS[cnt2]='\n';}else
 if(av[3][cnt+1]=='r'){MPS[cnt2]='\r';}else
 if(av[3][cnt+1]=='s'){MPS[cnt2]=' ';}else
 if(av[3][cnt+1]=='/'){MPS[cnt2]='/';}else
 if(av[3][cnt+1]=='m'){MPS[cnt2]='>';}else
 if(av[3][cnt+1]=='h'){MPS[cnt2]='<';}else
 if(av[3][cnt+1]=='d'){MPS[cnt2]='$';}else
 if(av[3][cnt+1]=='='){MPS[cnt2]='~';}else
 if(av[3][cnt+1]=='t'){MPS[cnt2]='\t';}else
 if(av[3][cnt+1]=='q'){MPS[cnt2]='?';}else
 if(av[3][cnt+1]=='a'){MPS[cnt2]='*';}else
 if(av[3][cnt+1]=='x'){MPS[cnt2]=hexget(av[3]+cnt+2);cnt+=2;}else
 if(av[3][cnt+1]=='X'){MPS[cnt2]=hexget(av[3]+cnt+2);cnt+=2;}else
 {MPS[cnt2]=av[3][cnt+1];}
cnt++;
}
else{MPS[cnt2]=av[3][cnt];}
cnt++;cnt2++;
}
MPS=realloc(MPS,cnt2);openerr(MPS);

MP=binload(av[1]);openerr(MP);
MP=chikan(MP, MPM, MPS);
binsave(av[1], MP, kgetsize(MP));
free(MP);free(MPM);free(MPS);
return(0);}
