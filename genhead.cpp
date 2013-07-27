#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
FILE *infile,*outfile;
struct stat st;
#define mlen 20
unsigned char buf[200];
int n,i;
int main(int argc, char **argv)
{
  if(argc<4)
  {
    printf("Usage: %s infile outfile varname\n",argv[0]);
    return 1;
  }
  outfile=fopen(argv[2],"wb");
  infile=fopen(argv[1],"rb");
  stat(argv[1],&st);
  fprintf(outfile,"static const unsigned char %s[%ld]=\n{\n",argv[3],st.st_size);
  while((n=fread(buf,1,mlen,infile)))
  {
    for(i=0;i<n;i++)
    {
      fprintf(outfile,"0x%X,",buf[i]);
    }
    fprintf(outfile,"\n");
  }
  fseek(outfile,-2,1);
  fprintf(outfile,"\n};\n");
  fclose(outfile);
  fclose(infile);
  return 0;
}
