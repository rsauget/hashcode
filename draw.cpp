#include <vector>
#include "draw.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

void draw(vector<vector<int> > &t, int &n, int &m, int &zoom)
{
	CImg<unsigned char> image(zoom*m,zoom*n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			image(j,i) = t[i][j];
		}
	}
	image = image.get_rotate(0, 0, 0, zoom, 0, 0);
	CImgDisplay main_disp(image,"Image");
	while (!main_disp.is_closed()) {
		main_disp.wait();
	}
}