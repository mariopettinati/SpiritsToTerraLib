#ifndef CONVERTER_PERSISTENCE_SERVICE
#define CONVERTER_PERSISTENCE_SERVICE

#include <string>
#include "TerraLibConverterDefines.h"

class TeDatabase;

/** \brief Opens a connection to the database.
	\return Returns a valid connected database in case of success. Otherwise returns NULL
*/
TC_DLL TeDatabase* OpenConnection();

TC_DLL TeDatabase* CreateDatabase();

TC_DLL void CloseConnection(TeDatabase* database);

/** \brief Imports the given image to the given database using the given layerName.
	\param database The database where the image will be imported.
	\param imgFileName The image that will be imported.
	\param layerName The name of the layer that will be created to store the imported image.
	\return TRUE in case of success. FALSE otherwise
*/
TC_DLL bool ImportImageToDatabase(TeDatabase* database, const std::string& imgFileName, const std::string& layerName);

/** \brief Imports the given ShapeFile to the given database using the given layerName.
	\param database The database where the ShapeFile will be imported.
	\param shapeFileName The ShapeFile that will be imported.
	\param layerName The name of the layer that will be created to store the imported ShapeFile.
	\return TRUE in case of success. FALSE otherwise
*/
TC_DLL bool ImportShapeToDatabase(TeDatabase* database, const std::string& shapeFileName, const std::string& layerName);

/** \brief Imports the given CSV file to the given database using the given table.
	\param database The database where the CSV file will be imported.
	\param tableFileName The CSV file that will be imported.
	\param tableName The name of the table that will be created to store the imported CSV file.
	\return TRUE in case of success. FALSE otherwise
*/
TC_DLL bool ImportCSVToDatabase(TeDatabase* database, const std::string& csvFileName, const std::string& tableName);

/** \brief Imports the given RUM CSV file to the given database using the given table.
	\param database The database where the RUM CSV file will be imported.
	\param tableFileName The RUM CSV file that will be imported.
	\param tableName The name of the table that will be created to store the imported RUM CSV file.
	\return TRUE in case of success. FALSE otherwise
*/
TC_DLL bool ImportRUMToDatabase(TeDatabase* database, const std::string& rumFileName, const std::string& tableName);

#endif //CONVERTER_PERSISTENCE_SERVICE
