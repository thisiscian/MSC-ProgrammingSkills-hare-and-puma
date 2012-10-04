/*
A module that recieves two arrays 'hares[][]' and 'pumas[][]' and outputs their values to the console

Cian Booth
this.is.cian@gmail.com
*/

void output_to_console(double hares[][], double pumas[][])
{
	int horizontalPosition, verticalPosition;
	int width, height;
	for(horizontalPosition = 0; horizontalPosition < width; horizontalPosition++)
	{
		for(verticalPosition = 0; verticalPosition < height; verticalPosition++)
		{
			cout << hares[horizontalPosition][verticalPosition] <<	";" << pumas[horizontalPosition][verticalPosition] << "|" << flush;
		}
		cout << endl;
	}
	return 0;
}
