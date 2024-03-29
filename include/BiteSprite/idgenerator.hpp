#ifndef BITE_IDGENERATOR_HPP
#define BITE_IDGENERATOR_HPP



#include <set>
#include <map>

namespace Bite
	{

	typedef unsigned int ID;
	typedef std::set<ID> IDSet;
	typedef std::map<std::string, ID> StringID;

	class IDGenerator
		{
		public:
			IDGenerator();

			ID NewID();
			void RecycleID( ID );
			ID LastID();
			ID TopID();

		private:
			IDSet recycleBin;
			ID top;
			ID last;
		};

	} // namespace Bite

#endif // BITE_IDGENERATOR_HPP