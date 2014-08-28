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
	//std::string imageFileName = "D:/mario/devel/Data/Images/Agricab/regions.img";
	std::string imageFileName = "D:/mario/devel/Data/Images/Agricab/GLC_5classes.img";

	TeDatabase* database = OpenConnection();
	//ImportShapeToDatabase(database, shapeFileName, "shape_test");
	ImportImageToDatabase(database, imageFileName, "image_test");

	CloseConnection(database);

	return 1;
}