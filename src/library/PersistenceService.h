#ifndef CONVERTER_PERSISTENCE_SERVICE
#define CONVERTER_PERSISTENCE_SERVICE

#include <string>

class TeDatabase;

	/** \brief Imports the given image to the given database using the given layerName.
		\param database The database where the image will be imported.
		\param imgFileName The image that will be imported.
		\param layerName The name of the layer that will be created to store the imported image.
		\return TRUE in case of success. FALSE otherwise
	*/
	bool ImportImageToDatabase(TeDatabase* database, const std::string& imgFileName, const std::string& layerName);


#endif //CONVERTER_PERSISTENCE_SERVICE