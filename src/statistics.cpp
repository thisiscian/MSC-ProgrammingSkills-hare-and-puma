#include "statistics.h"

BoardStatistics::BoardStatistics(Board<Tile> field)
{
	set_totals(field);
	previousTime = 0;
	previousPumaTotal = 0;
	previousHareTotal = 0;
}

void BoardStatistics::set_totals(Board<Tile> field)
{
	int height = field.get_height();
	int width = field.get_width();
	double haresTotal=0;
	double pumasTotal=0;
	for(int i=1; i<width-1; ++i)
	{
		for(int j=1; j<height-1; ++j)
		{
				hareTotal += field(i,j).hare;	
				pumaTotal += field(i,j).puma;
		}
	}
	previousHareTotal = currentHareTotal;
	previousPumaTotal = currentPumaTotal;
	currentHareTotal = hareTotal;
	currentPumaTotal = pumaTotal;
}

void BoardStatistics::set_time_averages(Board<Tile> field, double time)
{
	hareAverage = (previousHareTotal*previousTime+currentHareTotal*(time-previousTime))/time;
	pumaAverage = (previousPumaTotal*previousTime+currentPumaTotal*(time-previousTime))/time;
	previousTime = time;
}

void BoardStatistics::trawl_for_statistics(Board<Tile> field, double time)
{
	set_totals(field);
	set_time(field, time);
}
double BoardSetters::get_hare_total(){ return currentHareTotal; }
double BoardSetters::get_puma_total(){ return currentPumaTotal; }
double BoardSetters::get_hare_average(){ return hareAverage; }
double BoardSetters::get_puma_average(){ return pumaAverage;}
