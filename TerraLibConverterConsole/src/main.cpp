#include <string>
#include <vector>

#include <PersistenceService.h>

int main( int argc, char ** argv )
{
	std::vector<std::string> vecParameters;
	for(int i = 0; i < argc; ++i)
	{
		std::string param(argv[i]);
		vecParameters.push_back(param);
	}

	std::string shapeFileName = "D:/mario/devel/Data/Shapes/Agricab/regions.shp";

	TeDatabase* database = CreateDatabase();
	ImportShapeToDatabase(database, shapeFileName, "shape_test");

	return 1;
}