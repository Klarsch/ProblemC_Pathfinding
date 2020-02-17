#pragma once

class V2Dint
{
public:
	V2Dint() {x= 0xffffffff;y= 0xffffffff;}
	V2Dint( const int xIn, const int yIn ) { x = xIn; y = yIn; }

	int x;
	int y;

	bool operator!=( const V2Dint& other ) const 
	{
		return !( x == other.x && y == other.y );
	}
	bool operator!=( const V2Dint& other )
	{
		return !( x == other.x && y == other.y );
	}

	bool operator==( const V2Dint& other ) const
	{
		return ( x == other.x && y == other.y );
	}
	bool operator==( const V2Dint& other )
	{
		return ( x == other.x && y == other.y );
	}
};
