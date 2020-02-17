#pragma once

#define NO_PATH_FOUND -1

int FindPath( const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize );
