/* General C functions 2005-11-15 by K.Hoshino & SHI */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//------------------------------------------------------------------- Macros
#define pp(c) fputs(c,stdout)
#define pc(c) printf("%d",c)
#define pd(c) printf("%10.10lf",c)
#define errexit(a,b,c) if(a<b){pp(c);pp("\n");fgetc(stdin);exit(-1);}
#define openerr(p) if(p==NULL){pp("File/MemoryOpenError\n");exit(-1);}
#define zf(s,b,m) memset(m+s,0,b)
//m=MP, s=start, b=bytes
#define cw(s,m) memcpy(m,s,strlen(s))
//s=str, m=MP

//------------------------------------------------------------malloc wrapper
void *k_malloc(unsigned int size){
void *ret=malloc(size+sizeof(unsigned int));openerr(ret);
*(unsigned int *)ret=size;return(void *)((unsigned int *)ret+1);}

void *k_realloc(void *ptr, unsigned int size){
void *ret=realloc((unsigned int *)ptr - 1, size+sizeof(unsigned int));
openerr(ret);
*(unsigned int *)ret=size;return (void *)((unsigned int *)ret+1);}

void *k_calloc(unsigned int sizee, unsigned int size){
void *ret=calloc(sizee, size+sizeof(unsigned int));openerr(ret);
*(unsigned int *)ret=size;return (void *)((unsigned int *)ret+1);}

unsigned int kgetsize(void *ptr){return *((unsigned int *)ptr-1);}
void k_free(void *ptr){free((unsigned int *)ptr-1);}
#define malloc k_malloc
#define calloc k_calloc
#define realloc k_realloc
#define free k_free

//-------------------------------------------------------------GENERAL HEADER
char *binloadplus(char *filename, int addsize){
FILE *fp;
long filesize;
char *MP;

fp= fopen( filename, "rb" );openerr(fp);
fseek(fp,0,SEEK_END);filesize=ftell(fp);
MP=(char *)malloc((int)filesize+addsize);openerr(MP);
fseek(fp,0,SEEK_SET);
if(fread( MP, (int)filesize, 1, fp )!=1){pp("Read error at binload\n");
exit(-1);};fclose(fp);return(MP);}

//----------------------------------binload:binloadplus:load from file to *MP
char *binload(char *fn){return(binloadplus(fn, 0));}

//--------------------------------------------------------binsavetmp::save MP
void binsavetmp(char *filename, char *MP, int savesize, int add){
FILE *fp;

if(filename[0]!=0){
if(add==0){fp= fopen( filename, "wb" );}else{fp= fopen( filename, "ab" );}
openerr(fp);
if(fwrite(MP,savesize,1,fp)!=1){pp("disk full at binsave\n");exit(-1);}
fclose(fp);}}

//------------------------------------binsave:binsavetmp:save to file from MP
void binsave(char *filename, char *MP, int savesize){
binsavetmp(filename, MP, savesize, 0);}

//-----------------------------------addsave:binsavetmp:save add file from MP
char *chikan(char *in, char *moto, char *saki){
//all inputs must be in heap memory!

int ins=kgetsize(in),motos=kgetsize(moto),sakis=kgetsize(saki);
int cnt, cnt2=0, skip=0;
char *out=malloc((int)ins*(sakis/motos+1));

openerr(out);
errexit(ins,motos,"input length error at chikan");
for(cnt=0;cnt<(ins-motos+1);cnt++){

if(skip>0){skip--;}else
if(memcmp(in+cnt,moto,motos)!=0){out[cnt2]=in[cnt];cnt2++;}else
if(memcmp(in+cnt,moto,motos)==0){
memcpy(out+cnt2,saki,sakis);cnt2+=sakis;skip=(motos-1);}

//pc(cnt);pp(",");pc(out[cnt2-1]);pp(",");pp("\n");

}//for
memcpy(out+cnt2,in+ins-(motos-skip-1),motos-skip-1);cnt2+=(motos-skip-1);
out=realloc(out,cnt2);free(in);return(out);}

//-------------------------------------split::mojiretu no mae ka ato wo kaesu
