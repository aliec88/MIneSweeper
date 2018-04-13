#include "StdAfx.h"
#include "Mine.h"

const int NumMineVertex=4;
const SPoint mine[NumMineVertex]={SPoint(-1,-1),SPoint(-1,1),SPoint(1,1),SPoint(1,-1)};

CMine::CMine(void)
{
	m_svPos=SVector2D((double)RandInt(0,CParams::WindowWidth),(double)RandInt(0,CParams::WindowHeight));
	for (int i=0;i<NumMineVertex;i++)
	{
		m_vecMineVertexs.push_back(mine[i]);
	}
}


CMine::~CMine(void)
{
}
