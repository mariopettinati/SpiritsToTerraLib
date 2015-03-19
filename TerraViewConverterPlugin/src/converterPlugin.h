#ifndef __TVPS_PLUGIN_H_
#define __TVPS_PLUGIN_H_

//TerraLib
#include <TViewAbstractPlugin.h>
#include <PluginsSignal.h>

//STL includes
#include <vector>

//Qt include files
#include <qobject.h>

//Forward Declarations
class QPopupMenu;
class QAction;
class QString;

class converterPlugin: public QObject, public TViewAbstractPlugin
{
	Q_OBJECT

public:
	/**	\brief Constructor.
	 *	\param params Plugin parameters.
	 */
	converterPlugin(PluginParameters* params);

	/**	\brief Destructor.
	 */
	~converterPlugin();

	/**	\brief Initializer method.
	 */
	void init();

	/**	\brief Finalizer method.
	 */
	void end();

	static void pluginSignalHandler(const PluginsSignal& x, void* objptr);

protected:

	void signalHandler( const PluginsSignal& sig);

	QAction* createAction(QObject* parent, const QString& text, bool toggle);

protected slots:

	virtual void checkWidgetEnabling();
	virtual void showImportRasterWindow();
	virtual void showImportVectorWindow();
	virtual void showImportRUMFilesWindow();
	virtual void showImportRUMDatabaseWindow();

private:

	TeCommunicator<PluginsSignal>	m_pluginSignalReceiver;
	QPopupMenu*						m_basePopupMenu;
	std::vector<QAction*>			m_vecActions;
};

#endif //__TVPS_PLUGIN_H_
