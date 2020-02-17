#pragma once
#include "V2Dint.h"

class Node
{
public:
	Node();

	const unsigned& getNodeID() const { return ID; }
	void setNodeID( const unsigned idIn ) { ID = idIn; }

	const unsigned& getNodeType() const { return Type; }
	void setNodeType( const unsigned typeIn ) { Type = typeIn; }

	const V2Dint& getPosition() const { return Position; }
	void setPosition( const V2Dint positionIn ) { Position = positionIn; }
	void setPosition( const unsigned positionInX, const unsigned positionInY ) { Position.x = positionInX; Position.y = positionInY;}

	const bool& getIsClosed() const { return IsClosed; }
	void setIsClosed( bool input ) { IsClosed = input; }
	void CloseNode() { IsClosed = true; }
	
	const bool& getIsValid() const { return IsValid; }
	void setIsValid(bool input) { IsValid = input; }
	void ValidateNode() { IsValid = true; }

	Node* getParent() const { return pParentNode; }
	void setParentNode( Node* nodeIn ) { pParentNode = nodeIn; }

	const unsigned& getDistanceFromStart() const { return DistanceFromStart; }

	const float& getHeuristic() const { return Heuristic; }
	void CalculateHeuristic(V2Dint start, V2Dint position, V2Dint target );

	bool operator!=( const Node* other )
	{
		return !( ID == other->ID
			&& Type == other->Type
			&& pParentNode == other->pParentNode
			&& Heuristic == other->Heuristic 
			);
	}

	bool operator==( const Node* other )
	{
		return ( ID == other->ID 
			&& Type == other->Type
			&& pParentNode == other->pParentNode
			&& Heuristic == other->Heuristic 
			);
	}

	bool operator() (const Node* left, const Node* right )
	{
		return left->Heuristic > right->Heuristic;
	}

private:
	unsigned ID;
	unsigned char Type;
	V2Dint Position;
	bool IsClosed;
	bool IsValid;
	Node* pParentNode;
	unsigned DistanceFromStart;
	float Heuristic;
};