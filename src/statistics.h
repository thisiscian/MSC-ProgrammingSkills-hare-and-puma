#include "tile.h"
#include "board.h"
#include <cmath>
#include <algorithm>
using namespace std;

class BoardStatistics
{

	public:
	BoardStatistics();	
	BoardStatistics(Board<Tile>& field);	

	void init(Board<Tile>& field);
	void set_totals(Board<Tile>& field);
	void set_time_averages(Board<Tile>& field, double time);
	void set_maxima(Board<Tile>& field);
	void trawl_for_statistics(Board<Tile>& field, double time);

	double get_hare_average();
	double get_puma_average();
	double get_hare_total();
	double get_puma_total();
	double get_puma_max();
	double get_hare_max();
	
	private:
	double currentHareTotal;
	double currentPumaTotal;
	double hareAverage;
	double pumaAverage;
	double previousTime;
	double previousHareTotal;
	double previousPumaTotal;
	double maxHare;
	double maxPuma;
};
