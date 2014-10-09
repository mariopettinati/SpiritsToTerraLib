#include <TeQtGrid.h>
#include <terraViewBase.h>
#include <TeQtViewsListView.h>

#include <converterPlugin.h>

// Qt
#include <qaction.h>
#include <qmenubar.h>
#include <qobjectlist.h>
#include <qpopupmenu.h>

converterPlugin::converterPlugin(PluginParameters* params):
QObject(),
TViewAbstractPlugin(params)
{
	loadTranslationFiles("TerraViewPS_");

	pluginSignalReceiver_.setHostObj(this, pluginSignalHandler);
	pluginSignalReceiver_.connect(*(params_->signal_emitter_));
}

converterPlugin::~converterPlugin()
{
	end();
}

void converterPlugin::init()
{  
	// Gets TerraView Main Window...
    TerraViewBase* terraView = getMainWindow();
	/*try
	{
		if(terraView)
		{
			showWinAction_ = new QAction(0, "ShowWinAction", false);
			showWinAction_->setMenuText(tr("Add File Theme"));
			showWinAction_->setText( tr("File Theme") );
			showWinAction_->setToolTip( tr("File Theme") );
			//showWinAction_->setIconSet( QIconSet( QPixmap(fileTheme_xpm)));

			QPopupMenu* mnu = getPluginsMenu(tr("TerraViewPlugins.Themes").latin1());

			if(mnu != 0)
			{
				if(!showWinAction_->addTo(mnu))
					throw;
			}

			QPtrList< QToolBar > tv_tool_bars_list = tview->toolBars( Qt::DockTop );

			if( tv_tool_bars_list.count() > 0 )
				showWinAction_->addTo(tview->toolBars(Qt::DockTop).at(0));

			connect(showWinAction_, SIGNAL(activated()), this, SLOT(showWindow()));
		}
	}
	catch(...)
	{
		QMessageBox::critical(tview, tr("TerraView plug-in error"), tr("Can't create plug-in menu."));

		delete showWinAction_;
		showWinAction_ = 0;
	}*/

    // Database
	connect(terraView, SIGNAL(checkWidgetEnablingSignal()), this, SLOT(checkWidgetEnabling()));

	checkWidgetEnabling();
}

void converterPlugin::end()
{
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
