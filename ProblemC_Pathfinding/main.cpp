#include "Map.h"
#include "ScenarioLoader.h"

#include "Pathfinder.h"
//#include "PathfinderSimple.h"

#include <iostream>
#include <Windows.h>

bool TestMaps = true;
//{
	bool TestMaze = false;
	bool TestWheelofWar = true;
	bool TestTheFrozenSea = true;
	bool TestLabyrinth = true;
//}

int TestPath( const int nStartX, const int nStartY
	, const int nTargetX, const int nTargetY
	, const unsigned char* pMap, const int nMapWidth, const int nMapHeight
	, int* pOutBuffer, const int nOutBufferSize )
{
	int res = FindPath( nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize );

	if ( res >= 0 )
	{
		for ( int i = 0; i < res; ++i )
		{
			std::cout << pOutBuffer[i];
			if ( i < res - 1 )
				std::cout << ",";
		}
		std::cout << " length=" << res;
	}
	else
	{
		std::cout << res;
	}
	std::cout << std::endl;
	return res;
}

void TestMap( Map map, ScenarioLoader scenario)
{
	HANDLE hConsole;
	hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	int *pOutBuffer = new int[99999];
	for ( int i = 0; i < scenario.GetNumExperiments(); i++ )
	{
		Experiment experiment = scenario.GetNthExperiment( i );
		int res = FindPath( experiment.GetStartX(), experiment.GetStartY(), experiment.GetGoalX(), experiment.GetGoalY(), map.land.data(), map.GetMapWidth(), map.GetMapHeight(), pOutBuffer, 99999 );

		if ( res == (int)scenario.GetNthExperiment( i ).GetDistance() )
		{

			printf( "%i: %i == %i\n", i + 2, res, (int)scenario.GetNthExperiment( i ).GetDistance() );
		}
		else
		{
			//this is where you break in case of wrong path.
			SetConsoleTextAttribute( hConsole, 12 );
			printf( "%i:\t %i != %i\n",i+2, res, (int)scenario.GetNthExperiment( i ).GetDistance() );
			SetConsoleTextAttribute( hConsole, 10 );
		}
	}
delete[] pOutBuffer;
}

int main()
{
	HANDLE hConsole;
	hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	{ // length = 3; 9,5,1
		unsigned char pMap[] = {
			1, 1, 1, 1,
			0, 1, 0, 1,
			0, 1, 1, 1
		};
		int pOutBuffer[12];
		int length = TestPath( 0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12 );
	}

	{ // res = -1
		unsigned char pMap[] = {
			0, 0, 1,
			0, 1, 1,
			1, 0, 1
		};
		int pOutBuffer[7];
		TestPath( 2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7 );
	}

	{ // length = 6
		unsigned char pMap[] = {
			1, 1, 1, 1,
			1, 1, 1, 1,
			1, 0, 1, 1,
			1, 0, 1, 0,
			0, 1, 1, 1
		};
		int pOutBuffer[19];
		TestPath( 0, 1, 1, 4, pMap, 4, 5, pOutBuffer, 19 );
	}

	{ // length = 10
		unsigned char pMap[] = {
			/*0*/	1, 1, 1, 1, 1, 1,
			/*6*/	1, 1, 1, 1, 0, 1,
			/*12*/	1, 1, 1, 1, 0, 1,
			/*18*/	1, 1, 1, 1, 0, 1,
			/*24*/	1, 0, 0, 0, 0, 1,
			/*30*/	1, 1, 1, 1, 1, 1
		};
		int pOutBuffer[36];
		TestPath( 3, 3, 5, 5, pMap, 6, 6, pOutBuffer, 36 );
	}

	{ // res = (buffer to small), and then a correct path: length = 10
		unsigned char pMap[] = {
			1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 0, 1,
			1, 1, 1, 1, 0, 1,
			1, 1, 1, 1, 0, 1,
			1, 0, 0, 0, 0, 1,
			1, 1, 1, 1, 1, 1
		};
		int buffer_size = 5;
		int* pOutBuffer = new int[buffer_size];
		int length = TestPath( 3, 3, 5, 5, pMap, 6, 6, pOutBuffer, buffer_size );
		delete[] pOutBuffer;

		if ( length > buffer_size )
		{
			int* pOutBuffer2 = new int[length];
			TestPath( 3, 3, 5, 5, pMap, 6, 6, pOutBuffer2, length );
			delete[] pOutBuffer2;
		}
	}

	{
		unsigned char pMap[] = {
			/*0*/	1, 1, 1, 1, 1,
			/*5*/	1, 1, 1, 1, 1,
			/*10*/	1, 1, 1, 1, 1,
			/*15*/	1, 1, 1, 1, 1,
			/*20*/	1, 1, 1, 1, 1
		};
		int pOutBuffer[19];
		TestPath( 1, 1, 3, 3, pMap, 5, 5, pOutBuffer, 19 );
	}

	{ // res = -1
		unsigned char pMap[] = {
			0, 0, 0,
			0, 0, 0,
			0, 0, 0
		};
		int pOutBuffer[5];
		TestPath( 0, 0, 2, 2, pMap, 3, 3, pOutBuffer, 5 );
	}

	{ // res = 0
		unsigned char pMap[] = {
			1
		};
		int pOutBuffer[5];
		TestPath( 0, 0, 0, 0, pMap, 1, 1, pOutBuffer, 5 );
	}

	{ // res = 1, 2, 3
		unsigned char pMap[] = {
			1, 1, 1, 1
		};
		int pOutBuffer[5];
		TestPath( 0, 0, 3, 0, pMap, 4, 1, pOutBuffer, 5 );
	}
	SetConsoleTextAttribute( hConsole, 10 );
	
	if( TestMaps )
	{
		if( TestMaze )
		{
			Map Map( "Maze-Map/maze512-1-0.map" );
			ScenarioLoader Scenario( "Maze-scen/maze512-1-0.map.scen" );

			TestMap( Map, Scenario );
		}
		if( TestWheelofWar )
		{
			Map Map( "SC1-Map/WheelofWar.map" );
			ScenarioLoader Scenario( "SC1-scen/WheelofWar.map.scen" );

			TestMap( Map, Scenario );
		}
		if( TestTheFrozenSea )
		{
			Map Map( "SC1-Map/TheFrozenSea.map" );
			ScenarioLoader Scenario( "SC1-scen/TheFrozenSea.map.scen" );

			TestMap( Map, Scenario );
		}
		if( TestLabyrinth )
		{
			Map Map( "SC1-Map/Labyrinth.map" );
			ScenarioLoader Scenario( "SC1-scen/Labyrinth.map.scen" );

			TestMap( Map, Scenario );
		}
	}
	system( "PAUSE" );
}