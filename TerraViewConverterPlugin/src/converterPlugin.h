#ifndef __TVPS_PLUGIN_H_
#define __TVPS_PLUGIN_H_

#include <TViewAbstractPlugin.h>

#include <PluginsSignal.h>

//Qt include files
#include <qobject.h>

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

protected slots:

	virtual void checkWidgetEnabling();

private:

	TeCommunicator<PluginsSignal> pluginSignalReceiver_;
};

#endif //__TVPS_PLUGIN_H_
