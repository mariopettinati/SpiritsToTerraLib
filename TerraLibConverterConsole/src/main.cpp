#include <string>
#include <vector>

#include <PersistenceService.h>

int main( int argc, char ** argv )
{
	std::string message = "TerraLib Converter Console";
	message += "\nThe basic command line is:";
	message += "\nterralibConverterConsole.exe [parameters]";
	message += "\nParameters:";
	message += "\n--host host";

	std::string params;
	for(int i = 1; i < argc; ++i)
	{
		params += argv[i];
	}

	std::vector<std::string> vecParameters;
	for(int i = 0; i < argc; ++i)
	{
		std::string param(argv[i]);
		vecParameters.push_back(param);
	}

	TeDatabase* database = OpenConnection();
	/*
	//ShapeFiles test
	std::string shapeFileName = "D:/mario/devel/Data/Shapes/Agricab/regions.shp";
	ImportShapeToDatabase(database, shapeFileName, "shape_test1");
	*/

	
	//Erdas IMG Files test
	std::string imageFileName = "D:/mario/devel/Data/Images/Agricab/regions.img";
	std::string imageFileName2 = "D:/mario/devel/Data/Images/Agricab/GLC_5classes.img";
	ImportImageToDatabase(database, imageFileName2, "image_test");
	

	/*
	//CSV (RUM) Files test
	std::string csvFileName = "D:/mario/devel/Data/CSV/RUM/glc5_classes/vt19990101k.RUM";
	ImportRUMToDatabase(database, csvFileName, "vt19990101k");
	*/

	CloseConnection(database);

	return 1;
}