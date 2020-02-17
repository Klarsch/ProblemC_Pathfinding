#include "Pathfinder.h"

Pathfinder::Pathfinder( const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight )
{
	Width = nMapWidth;
	Height = nMapHeight;

	Start = V2Dint( nStartX, nStartY );
	Target = V2Dint( nTargetX, nTargetY );

	MapNodes( pMap );
}

Pathfinder::~Pathfinder()
{
	for( int i = 0; i < Height; i++ )
	{
		delete[] MappedNodes[i];
	}
	delete[] MappedNodes;
}

void Pathfinder::MapNodes( const unsigned char* pMap )
{
	if(Height != 0 && Width != 0){
		MappedNodes = new Node*[Height];
		unsigned NodeCount;
		for( int y = 0; y < Height; y++ )
		{
			MappedNodes[y] = new Node[Width];
			for( int x = 0; x < Width; x++ )
			{
				NodeCount = ( y * Width ) + x;

				MappedNodes[y][x].setNodeID( NodeCount );
				MappedNodes[y][x].setNodeType( pMap[NodeCount] );
				MappedNodes[y][x].setPosition( x, y );
				MappedNodes[y][x].setParentNode( nullptr );
			}
		}
	}
}

unsigned Pathfinder::GeneratePath( const unsigned char* pMap, int* pOutBuffer, const int nOutBufferSize )
{
	int PathLength = getCurrentNode()->getDistanceFromStart();

	if( PathLength <= nOutBufferSize )
	{
		for( int i = PathLength - 1; i >= 0; i-- )
		{
			pOutBuffer[i] = getCurrentNode()->getNodeID();
			setCurrentNode( getCurrentNode()->getParent() );
		}
	}
	return PathLength;
}

void Pathfinder::FindSurondingNodes()
{
	V2Dint CurrentPos = CurrentNode->getPosition();
	
	for( int Offset = -1; Offset < 2; Offset += 2 )
	{
		int OffsetX = CurrentPos.x + Offset;
		int OffsetY = CurrentPos.y + Offset;

		//Check Left and/or Right Node
		if( 0 <= OffsetX && OffsetX < Width )
		{
			TestNode( CurrentPos.y, OffsetX );
		}

		//Check Up and/or Down Node
		if( 0 <= OffsetY && OffsetY < Height )
		{
			TestNode( OffsetY, CurrentPos.x );
		}
	}
}

void Pathfinder::TestNode( const int y, const int x )
{
	Node *TempNode;
	TempNode = &MappedNodes[y][x];
	if( TempNode->getNodeType() != 0 )
	{
		TempNode->setParentNode( CurrentNode );
		TempNode->CalculateHeuristic(Start, TempNode->getPosition(), Target );

		if( !TempNode->getIsClosed() )
		{
			//if not, add to open.
//TODO: Same node can get added twize, fix it so that it gets edited instead. or longer more complex paths will eat all your memory.
			ViableNodes.push( TempNode );
		}
	}
}