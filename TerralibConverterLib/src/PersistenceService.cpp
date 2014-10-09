#include "PersistenceService.h"

#include <TeDatabase.h>
#include <TeDBConnectionsPool.h>
#include <TeDatabaseFactory.h>
#include <TeLayer.h>
#include <TeImportRaster.h>
#include <TeImportExport.h>
#include <TeAsciiFile.h>

std::vector<std::string> SplitInputParameters(int argc, char** argv)
{
	std::string params;
	for(int i = 1; i < argc; ++i)
	{
		params += argv[i]; 
	}

	//here we split the string using the separator: --
	std::vector<std::string> vecParams; 
	TeSplitString(params, "--", vecParams);

	//here we trim each parameter
	for(unsigned int i = 0; i < vecParams.size(); ++i)
	{
		std::string param = vecParams[i];
		TeTrim(param);
		vecParams[i] = param;
	}

	//we split again into the pair key/value
	for(unsigned int i = 0; i < vecParams.size(); ++i)
	{
		std::string param = vecParams[i];
		std::size_t index = param.find(' ');
		if(index > 0)
		{
			std::string key = param.substr(0, index);
			std::string value = param.substr(index + 1, param.size() - index);
		}
	}

	return vecParams;
}

TeDatabase* OpenConnection()
{
	//TeSetEnv("GDAL_DATA", "D:/mario/devel/Sources/dependencies/install/common/data");
	TeInitializeTerralib("D:/mario/devel/Sources/dependencies/install/common/");

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

bool ImportCSVToDatabase(TeDatabase* database, const std::string& csvFileName, const std::string& tableName)
{
	if(database == 0)
	{
		return false;
	}
	if(database->isConnected() == false)
	{
		return false;
	}
	if(csvFileName.empty() == true)
	{
		return false;
	}
	if(tableName.empty() == true)
	{
		return false;
	}

	bool firstLineIsHeader = true;

	TeAsciiFile csvFile(csvFileName);

	// try to guess the separator
	std::string firstLine = csvFile.readLine();

	std::string separator;
	if (firstLine.find(',') != -1)
	{
		separator = ",";
	}
	else if(firstLine.find(';') != -1)
	{
		separator = ";";
	}
	else if(firstLine.find(' ') != -1)
	{
		separator = " ";
	}
	else if(firstLine.find('\t') != -1)
	{
		separator = "\t";
	}
	else
	{
		return false;
	}
	char cSeparator = separator[0];
	
	std::vector<string> vecNames;
	TeTrim(firstLine);
	TeSplitString(firstLine, separator, vecNames);

	TeAttributeList attrList;
	for(unsigned int i = 0; i < vecNames.size(); ++i)
	{
		std::string colName;
		if (firstLineIsHeader == true)  //first line is a header
			colName = vecNames[i];
		else
			colName  = "Col" + Te2String(i);
		TeAttribute at;
		at.rep_.name_= colName;
		at.rep_.type_ = TeSTRING;
		at.rep_.numChar_ = 255;
		attrList.push_back(at);
	}

	TeTable table(tableName);
	table.setAttributeList(attrList);

	bool result = TeImportCSVFile(csvFileName, table, database, 0, cSeparator, firstLineIsHeader);

	return result;
}

TeAttributeList GetRUMAttributeList()
{
	TeAttributeList attrList;

	{
		TeAttribute at;
		at.rep_.name_= "region_id";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "class_id";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "unmixing_method";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "threshold";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "sensor_id";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "variable_id";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "periodicity";
		at.rep_.type_ = TeINT;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "date";
		at.rep_.type_ = TeDATETIME;
		at.dateSeparator_ = "";
		at.dateTimeFormat_ = "YYYYMMDD";
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "ra1";
		at.rep_.type_ = TeREAL;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "ra2";
		at.rep_.type_ = TeREAL;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "mean";
		at.rep_.type_ = TeREAL;
		attrList.push_back(at);
	}

	{
		TeAttribute at;
		at.rep_.name_= "standard_deviation";
		at.rep_.type_ = TeREAL;
		attrList.push_back(at);
	}

	return attrList;
}

bool ImportRUMToDatabase(TeDatabase* database, const std::string& rumFileName, const std::string& tableName)
{
	if(database == 0)
	{
		return false;
	}
	if(database->isConnected() == false)
	{
		return false;
	}
	if(rumFileName.empty() == true)
	{
		return false;
	}
	if(tableName.empty() == true)
	{
		return false;
	}

	TeAttributeList attrList = GetRUMAttributeList();

	TeTable table(tableName);
	table.setAttributeList(attrList);
	table.setUniqueName("region_id");
	table.setLinkName("region_id");

	bool result = TeImportCSVFile(rumFileName, table, database, 0, ',', false);

	return result;
}
