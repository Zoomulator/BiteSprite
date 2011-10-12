#include "BiteSprite\batch.hpp"




namespace Bite
	{


	void
	BatchGroup::Render() const
		{
		for( BatchContainer::const_iterator batchIt = batches.begin();
			batchIt != batches.end();
			++batchIt )
			{
			(*batchIt)->Render();
			}
		}


	void
	BatchGroup::Add( Batch* batch )
		{
		batches.insert( batch );
		}


	void
	BatchGroup::Remove( Batch* batch )
		{
		batches.erase( batch );
		}


	void
	BatchGroup::Clear()
		{
		batches.clear();
		}

	} // namespace Bite