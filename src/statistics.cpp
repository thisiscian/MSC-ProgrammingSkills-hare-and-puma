#include "statistics.h"

BoardStatistics::BoardStatistics(Board<Tile>& field)
{
	set_totals(field);
	set_maxima(field);
	previousTime = 0;
	previousPumaTotal = 0;
	previousHareTotal = 0;
}

void BoardStatistics::set_totals(Board<Tile>& field)
{
	int height = field.get_height();
	int width = field.get_width();
	double hareTotal=0;
	double pumaTotal=0;
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

void BoardStatistics::set_time_averages(Board<Tile>& field, double time)
{
	hareAverage = (previousHareTotal*previousTime+currentHareTotal*(time-previousTime))/time;
	pumaAverage = (previousPumaTotal*previousTime+currentPumaTotal*(time-previousTime))/time;
	previousTime = time;
}

void BoardStatistics::trawl_for_statistics(Board<Tile>& field, double time)
{
	set_totals(field);
	set_time_averages(field, time);
	set_maxima(field);
}

void BoardStatistics::set_maxima(Board<Tile>& field)
{
	int height = field.get_height();
	int width = field.get_width();
	maxPuma = 0.0;
	maxHare = 0.0;
	for(int i=1; i<width-1; ++i)
	{
		for(int j=1; j<height-1; ++j)
		{
				maxHare = max(field(i,j).hare, maxHare);	
				maxPuma = max(field(i,j).puma, maxPuma);
		}
	}
}

double BoardStatistics::get_hare_total(){ return currentHareTotal; }
double BoardStatistics::get_puma_total(){ return currentPumaTotal; }
double BoardStatistics::get_puma_average(){ return pumaAverage;}
double BoardStatistics::get_hare_average(){ return hareAverage; }
double BoardStatistics::get_hare_max(){ return maxHare; }
double BoardStatistics::get_puma_max(){ return maxPuma; }
