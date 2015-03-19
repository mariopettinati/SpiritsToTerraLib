/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

//TerraLib includes
#include <TeDatabase.h>

//Qt includes
#include <qfiledialog.h>
#include <qmessagebox.h>

//ConverterLib includes
#include "PersistenceService.h"

void ImportRUMFilesWindow::init(TeDatabase* database)
{
	m_database = database;
}

void ImportRUMFilesWindow::browsePushButton_clicked()
{
	QStringList strList = QFileDialog::getOpenFileNames("RUM Files (*.rum *.RUM)", "", this);
	filesListBox->insertStringList(strList);

	inputLineEdit->setText(*strList.begin());
}


void ImportRUMFilesWindow::importPushButton_clicked()
{
	if(filesListBox->numRows() == 0)
	{
		QMessageBox::critical(this, tr("AGRICAB"), tr("You must choose at least one RUM file!"));
		return;
	}

	for(size_t i = 0; i < filesListBox->numRows(); ++i)
	{
		QString qFileName = filesListBox->text(i);
		std::string fileName = qFileName.latin1();

		std::string baseTableName = TeGetBaseName(fileName.c_str());
		std::string tableName = baseTableName;

		size_t complement = 0;
		while(m_database->tableExist(tableName) == true)
		{
			tableName = baseTableName + "_" + Te2String(complement);
			++complement;
		}

		bool result = ImportRUMToDatabase(m_database, fileName, tableName);
		if(result == false)
		{
			QMessageBox::critical(this, tr("AGRICAB"), tr("The RUM file: [") + qFileName + tr("] could not be imported!"));
			break;
		}
	}

	QMessageBox::information(this, tr("AGRICAB"), tr("The import process was successfully finished!"));
	accept();
}


void ImportRUMFilesWindow::closePushButton_clicked()
{
	reject();
}
