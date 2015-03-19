#include <converterPlugin.h>

#include <TeQtGrid.h>
#include <terraViewBase.h>
#include <TeQtViewsListView.h>

#include "import.h"
#include "rasterImportWizard.h"
#include "importRUMFilesWindow.h"

// Qt
#include <qaction.h>
#include <qmenubar.h>
#include <qobjectlist.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>

converterPlugin::converterPlugin(PluginParameters* params):
QObject(),
TViewAbstractPlugin(params)
{
	loadTranslationFiles("TerraViewPS_");

	m_pluginSignalReceiver.setHostObj(this, pluginSignalHandler);
	m_pluginSignalReceiver.connect(*(params_->signal_emitter_));
}

converterPlugin::~converterPlugin()
{
	end();
}

void converterPlugin::init()
{  
	// Gets TerraView Main Window...
    TerraViewBase* terraView = getMainWindow();
	m_basePopupMenu = getPluginsMenu("TerraViewPlugins.AGRICAB");
	try
	{
		if(terraView != 0 && m_basePopupMenu != 0)
		{
			QAction* showImportRasterWindow = createAction(m_basePopupMenu, tr("Import Raster"), false);
			connect(showImportRasterWindow, SIGNAL(activated()), this, SLOT(showImportRasterWindow()));
			showImportRasterWindow->addTo(m_basePopupMenu);

			QAction* showImportVectorWindow = createAction(m_basePopupMenu, tr("Import Vector"), false);
			connect(showImportVectorWindow, SIGNAL(activated()), this, SLOT(showImportVectorWindow()));
			showImportVectorWindow->addTo(m_basePopupMenu);


			QAction* showImportRUMFilesWindow = createAction(m_basePopupMenu, tr("Import RUM Files"), false);
			connect(showImportRUMFilesWindow, SIGNAL(activated()), this, SLOT(showImportRUMFilesWindow()));
			showImportRUMFilesWindow->addTo(m_basePopupMenu);

			QAction* showImportRUMDatabaseWindow = createAction(m_basePopupMenu, tr("Import RUM Database"), false);
			connect(showImportRUMDatabaseWindow, SIGNAL(activated()), this, SLOT(showImportRUMDatabaseWindow()));
			showImportRUMDatabaseWindow->addTo(m_basePopupMenu);

			

			/*

			QPtrList< QToolBar > tv_tool_bars_list = tview->toolBars( Qt::DockTop );

			if( tv_tool_bars_list.count() > 0 )
				showWinAction_->addTo(tview->toolBars(Qt::DockTop).at(0));

			connect(showWinAction_, SIGNAL(activated()), this, SLOT(showWindow()));
			*/
		}
	}
	catch(...)
	{
		QMessageBox::critical(terraView, tr("TerraView plug-in error"), tr("Can't create plug-in menu."));

		delete m_basePopupMenu;
		m_basePopupMenu = 0;
	}

    // Database
	connect(terraView, SIGNAL(checkWidgetEnablingSignal()), this, SLOT(checkWidgetEnabling()));

	checkWidgetEnabling();
}

void converterPlugin::end()
{
	for(size_t i = 0; i < m_vecActions.size(); ++i)
	{
		delete m_vecActions[i];
	}

	m_vecActions.clear();

	// Gets TerraView Main Window...
    TerraViewBase* tv = getMainWindow();
	if(tv != 0)
	{
		disconnect(tv, SIGNAL(checkWidgetEnablingSignal()), this, SLOT(checkWidgetEnabling()));
	}
}

void converterPlugin::pluginSignalHandler(const PluginsSignal& x, void* objptr)
{
	((converterPlugin*)objptr)->signalHandler(x);
}

void converterPlugin::signalHandler( const PluginsSignal& x)
{

}

void converterPlugin::checkWidgetEnabling()
{
	TeDatabase* database = params_->getCurrentDatabasePtr();
	if(database != 0)
	{
		m_basePopupMenu->setEnabled(true);
	}
	else
	{
		m_basePopupMenu->setEnabled(true);
	}
	

	/*_dbMenu->setEnabled(false);
    _dbToolBar->setEnabled(false);
	_viewMenu->setEnabled(false);
	_viewToolBar->setEnabled(false);
	_themeMenu->setEnabled(false);
	_themeToolBar->setEnabled(false);
	_queryToolBar->setEnabled(false);
	_layerMenu->setEnabled(false);
	_layerToolBar->setEnabled(false);

	if(params_->getCurrentDatabasePtr() != 0)
	{
		_dbMenu->setEnabled(true);
		_dbToolBar->setEnabled(true);
	}

	if(params_->getCurrentViewPtr() != 0)
	{
		_viewMenu->setEnabled(true);
		_viewToolBar->setEnabled(true);
	}

	if(params_->getCurrentThemeAppPtr() != 0)
	{
		_themeMenu->setEnabled(true);
		_themeToolBar->setEnabled(true);
		_queryToolBar->setEnabled(true);
	}

	if(params_->getCurrentLayerPtr() != 0)
	{
		_layerMenu->setEnabled(true);
		_layerToolBar->setEnabled(true);
	}
	*/
}

QAction* converterPlugin::createAction(QObject* parent, const QString& text, bool toggle)
{
	QAction* action = new QAction(parent, "", toggle);
	action->setMenuText(text);
	action->setText(text);
	action->setToolTip(text);

	m_vecActions.push_back(action);

	return action;
}

void converterPlugin::showImportRasterWindow()
{
	TerraViewBase* terraView = getMainWindow();

	RasterImportWizard dialog(terraView, "", 0);
	if(dialog.exec() == QDialog::Accepted)
	{
		params_->updateTVInterface();
	}
}
void converterPlugin::showImportVectorWindow()
{
	TerraViewBase* terraView = getMainWindow();

	ImportWindow dialog(terraView, "", 0);
	if(dialog.exec() == QDialog::Accepted)
	{
		params_->updateTVInterface();
	}
}
void converterPlugin::showImportRUMFilesWindow()
{
	TerraViewBase* terraView = getMainWindow();

	ImportRUMFilesWindow dialog(terraView, "", 0);
	if(dialog.exec() == QDialog::Accepted)
	{
		params_->updateTVInterface();
	}
}

void converterPlugin::showImportRUMDatabaseWindow()
{
}