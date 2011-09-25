#ifndef BITE_BATCH_HPP
#define BITE_BATCH_HPP


#include <set>


namespace Bite
	{


	class Batch
		{
		public:

		virtual
		~Batch() {};

		virtual
		void 
		Render() const = 0;
		};



	class BatchGroup : public Batch
		{
		public:

		~BatchGroup() {};

		void
		Render() const;

		void
		Add( Batch* batch );

		void
		Remove( Batch* batch );

		void
		Clear();

		private:
		std::set<Batch*> BatchContainer;
		BatchContainer batches;
		};


	} // namespace Bite



#endif // BITE_BATCH_HPP