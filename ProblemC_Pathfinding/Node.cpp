#include "Node.h"

#include <cmath>

Node::Node()
{
	ID = 0xffffffff;
	Type = 255;
	Position = V2Dint( 0xffffffff, 0xffffffff );
	IsValid = false;
	IsClosed = false;
	pParentNode = nullptr;
	DistanceFromStart = 0;
	Heuristic = 3.402823466e+38F;
	
}

void Node::CalculateHeuristic(V2Dint start, V2Dint position, V2Dint target )
{
	DistanceFromStart = pParentNode->DistanceFromStart + 1;
	Heuristic = (float)DistanceFromStart * sqrtf(powf((float)target.x - (float)position.x, 2) + powf((float)target.y - (float)position.y, 2));//(abs( target.x - position.x) + abs( target.y - position.y));
}