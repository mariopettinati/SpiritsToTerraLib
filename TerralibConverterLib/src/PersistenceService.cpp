#include "PersistenceService.h"

#include <TeDatabase.h>
#include <TeDBConnectionsPool.h>
#include <TeDatabaseFactory.h>
#include <TeLayer.h>
#include <TeImportRaster.h>
#include <TeImportExport.h>

TeDatabase* OpenConnection()
{
	TeDatabaseFactoryParams params;
	params.dbms_name_ = "PostGIS";
	params.host_ = "localhost";
	params.user_ = "postgres";
	params.password_ = "postgres";
	params.database_ = "test";
	params.port_ = 5432;

	TeDatabase* database = TeDBConnectionsPool::instance().getDatabase(params.dbms_name_, params.database_, params.host_, params.user_, params.password_, params.port_);

	return database;
}

TeDatabase* CreateDatabase()
{
	TeDatabaseFactoryParams params;
	params.dbms_name_ = "PostGIS";

	TeDatabase* database = TeDatabaseFactory::make(params);
	if(database == 0)
	{
		return 0;
	}

	params.host_ = "localhost";
	params.user_ = "postgres";
	params.password_ = "postgres";
	params.database_ = "test";
	params.port_ = 5432;

	if(database->newDatabase(params.database_, params.user_, params.password_, params.host_, params.port_) == false)
	{
		delete database;
		return 0;
	}

	return database;
}

void CloseConnection(TeDatabase* database)
{
	if(database != 0)
	{
		database->close();
		delete database;
	}
}

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
		database->deleteLayer(layer->id());
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

	TeLayer* layer = TeImportShape(shapeFileName, database, layerName);
	if(layer == 0)
	{
		return false;
	}
	return true;
}
