#include "output.h"
#include <math.h>
int main()
{
	board<tile> field(10,10);
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();

	/* define a field with arbitrarily different values for land, hare numbers and puma numbers */
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			field(horizontalPosition, verticalPosition).make_land();
			field(horizontalPosition, verticalPosition).hare = 255.0*max(cos(verticalPosition+horizontalPosition), 0.0);
			field(horizontalPosition, verticalPosition).puma = 255.0*max(sin(verticalPosition+horizontalPosition), 0.0);
			if(horizontalPosition % 2 == 0 && verticalPosition % 2 == 0)
			{
				field(horizontalPosition, verticalPosition).make_water();
			}
		}
	}
	
	output_to_console(field, 0.0);
	write_simple_ppm(field, 0.0);
	write_simple_adjustable_ppm(field, 0.0, 35, 3);
	write_fancy_ppm(field, 0.0);
	return 0;
}
