#include "FindPath.h"

#include "Pathfinder.h"

#include <algorithm>

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
	Pathfinder PF(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight);

	//Initiate Starting node
	Node* StartNode;
	StartNode = PF.getNode(nStartY, nStartX);

	PF.ViableNodes.push(StartNode);

	while (true)
	{
		if (PF.ViableNodes.size() > 0)
		{
			if (!PF.ViableNodes.top()->getIsClosed())
			{
				PF.setCurrentNode(PF.ViableNodes.top());
				PF.ViableNodes.top()->CloseNode();
				PF.ViableNodes.pop();

				if (PF.getCurrentNode()->getPosition() == V2Dint(nTargetX, nTargetY))
				{
					////Goal found
					return PF.GeneratePath(pMap, pOutBuffer, nOutBufferSize);
				}
				else
				{
					//Look for path
					PF.FindSurondingNodes();
				}
			}
			else
			{
				PF.ViableNodes.pop();
			}
		}
		else
		{
			//No path found
			return NO_PATH_FOUND;
		}

	}
}