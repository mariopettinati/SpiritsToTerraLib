#include "PersistenceService.h"

#include <TeDatabase.h>
#include <TeImportRaster.h>
#include <TeImportExport.h>

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
	if(imgFileName.empty() == true)
	{
		return false;
	}
	if(layerName.empty() == true)
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
	if(result == false)
	{
		return false;
	}

	return true;
}

bool ImportShapeToDatabase(TeDatabase* database, const std::string& shapeFileName, const std::string& layerName)
{
	if(database == 0)
	{
		return false;
	}
	if(database->isConnected() == false)
	{
		return false;
	}
	if(shapeFileName.empty() == true)
	{
		return false;
	}
	if(layerName.empty() == true)
	{
		return false;
	}

	bool result = TeImportShape(shapeFileName, database, layerName);
	if(result == false)
	{
		return false;
	}
	return true;
}
