#include <iostream>
#include <string>
#include <unistd.h>
#include "CImg.h"
#include "io.h"

using namespace std;

const int N = 300;
unsigned t[N][N];

const int zoom=1;



void draw();

void compute()
{

}

void eval()
{

}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	read();
	draw();
	int best = -1;
	int score;
	while(1)
	{
		compute();
		score = eval();
		if(score > best)
		{
			best = score;
			write();
		}
	}
	return 0;
}

using namespace cimg_library;

void draw()
{
	CImg<unsigned char> image(zoom*N,zoom*N);
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			image(j,i) = img[i][j];
		}
	}
	image = image.get_rotate(0, 0, 0, zoom, 0, 0);
	CImgDisplay main_disp(image,"Image");
	while (!main_disp.is_closed()) {
		main_disp.wait();
	}
}