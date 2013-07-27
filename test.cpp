#define RGB(red, green, blue)	((unsigned short int)( (( red >> 3 ) << 11 ) | \
								(( green >> 2 ) << 5  ) | \
								( blue  >> 3 )))
#include <iostream>
#include <Magick++.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
using namespace Magick;
int x,y;
unsigned char rh, rl,buf[2];
int main(int argc, char **argv)
{
  if(argc<3)
  {
    cout << "Usage:\n" << argv[0] << " source_file output_file\n";
    return 0;
  }
  Image image;
  Color pix;
  try
  {
    image.read(argv[1]);
  }
  catch (Error& err)
  {
    cerr << err.what() << "\n";
    return 1;
  }
  FILE *outfile;
  outfile=fopen(argv[2],"ab");
  if(outfile==NULL)
  {
    cerr << "Could not open output file.\n";
    return 1;
  }
  //if(image.size().width()>image.size().height())image.rotate(90);
  //if(image.size().width()!=240)image.sample(Geometry(240,320));
  cout << image.size().width() << 'x' << image.size().height() << '\n';
  //image.display();
  for(y=0;y<image.size().height();y++)
    for(x=0;x<image.size().width();x++)
    {
      if(x>=image.size().width() || y>=image.size().height())
      {
	buf[0]=buf[1]=buf[2]=255;
      }
      else
      {
	pix=image.pixelColor(x,y);
	buf[0]=(pix.redQuantum()*255)/MaxRGB;
	buf[1]=(pix.greenQuantum()*255)/MaxRGB;
	buf[2]=(pix.blueQuantum()*255)/MaxRGB;
	rh=RGB(buf[0],buf[1],buf[2])>>8;
	rl=RGB(buf[0],buf[1],buf[2])&0xFF;
	buf[1]=rh; buf[0]=rl;
      }
      fwrite(buf,1,2,outfile);
     //putchar('x');
    }
  fclose(outfile);
  return 0;
}
