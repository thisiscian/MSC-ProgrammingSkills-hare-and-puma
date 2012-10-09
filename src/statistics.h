#include "tile.h"
#include "board.h"

class BoardStatistics
{

	public:
	BoardStatistics();	

	double get_totals(Board<Tile> field);
	double get_time_averages(Board<Tile> field, double time);

	void trawl_for_statistics(Board<Tile> field, double time);

	double get_hare_average();
	double get_puma_average();
	double get_hare_total();
	double get_puma_total();
	
	private:
	double currentHareTotal;
	double currentPumaTotal;
	double hareAverage;
	double pumaAverage;
	double previousTime;
	double previousHareTotal;
	double previousPumaTotal;
}