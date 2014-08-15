#include "PersistenceService.h"

#include <TeDatabase.h>
#include <TeImportRaster.h>

bool ImportImageToDatabase(TeDatabase* database, const std::string& imgFileName, const std::string& layerName)
{
	if(database == 0)
	{
		return false;
	}
	if(database->isConnected() == false)
	{
		return false;
	}
	
	TeRaster* rasterIn = new TeRaster(imgFileName);
	if(rasterIn->init() == false)
	{
		delete rasterIn;
		return false;
	}

	TeLayer* layer = new TeLayer(layerName, database, rasterIn->projection());

	bool result = TeImportRaster(layer, rasterIn);

	return true;
}