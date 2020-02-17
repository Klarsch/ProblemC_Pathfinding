#pragma once

#include "Node.h"

#include <queue>
#include <vector>
#include <functional>

class Pathfinder
{
public:
	Pathfinder( const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
		const unsigned char* pMap, const int nMapWidth, const int nMapHeight );
	~Pathfinder();

	void MapNodes( const unsigned char* pMap );
	
	unsigned GeneratePath( const unsigned char* pMap, int* pOutBuffer, const int nOutBufferSize );
	void FindSurondingNodes( );
	void TestNode( const int y, const int x );
	Node* getNode( const int y, const int x ) { return &MappedNodes[y][x]; }
	
	Node* getCurrentNode() const { return CurrentNode; }
	void setCurrentNode( Node *inputNode ) { CurrentNode = inputNode; }

	int Height;
	int Width;

	V2Dint Start;
	V2Dint Target;

	typedef std::priority_queue<Node*, std::vector<Node*>, Node> NodePrioQueue;
	NodePrioQueue ViableNodes;
	
private:
	
	Node *CurrentNode;
	Node **MappedNodes;
};

int FindPath( const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize );
