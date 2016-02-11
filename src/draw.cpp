#include <vector>
#include "draw.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

void draw(int &rows,int &columns,int &nbWarehouses,vector<Warehouse> &warehouses, int zoom)
{
	CImg<unsigned char> image(zoom*columns,zoom*rows);
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			image(j,i) = 255;
		}
	}
	for(int i=0;i<nbWarehouses;i++)
	{
		image(warehouses[i].column,warehouses[i].row) = 0;
	}
	image = image.get_rotate(0, 0, 0, zoom, 0, 0);
	CImgDisplay main_disp(image,"Image");
	while (!main_disp.is_closed()) {
		main_disp.wait();
	}
}