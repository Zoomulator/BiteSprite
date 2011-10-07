#include "idgenerator.hpp"





namespace Bite
	{


	IDGenerator::IDGenerator() :
			top(0),
			last(0)
		{
		}


	ID
	IDGenerator::NewID()
		{
		ID id = 0;

		if( recycleBin.empty() )
			{
			id = ++top;
			}
		else
			{
			IDSet::iterator idIt = recycleBin.begin();
			id = *idIt;
			recycleBin.erase( idIt );
			}

		last = id;
		return id;
		}


	void
	IDGenerator::RecycleID( ID id )
		{
		recycleBin.insert( id );
		}


	ID
	IDGenerator::LastID()
		{
		return last;
		}


	ID
	IDGenerator::TopID()
		{
		return top;
		}


	} // namespace Bite