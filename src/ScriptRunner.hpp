/******************************************************************************\
*  Dominus: A scriptable, window-less, non-browseable web browser.             *
*                                                                              *
*  Copyright 2011  Leandro Motta Barros                                        *
*                                                                              *
*  This program is free software: you can redistribute it and/or modify        *
*  it under the terms of the GNU General Public License as published by        *
*  the Free Software Foundation, either version 3 of the License, or           *
*  (at your option) any later version.                                         *
*                                                                              *
*  This program is distributed in the hope that it will be useful,             *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
*  GNU General Public License for more details.                                *
\******************************************************************************/

#ifndef _DOMINUS_SCRIPTRUNNER_HPP_
#define _DOMINUS_SCRIPTRUNNER_HPP_

#include <QTimer>
#include <QtWebKit/QWebPage>
#include "Diluculum/LuaState.hpp"


namespace Dominus
{
   /// A class responsible for loading a Dominus script and running it.
   class ScriptRunner: public QObject
   {
      Q_OBJECT
      public:
         /**
          * Constructs the \c ScriptRunner.
          * @param scriptFile The path to the script file to run.
          */
         ScriptRunner(const std::string& scriptFilePath);

         /**
          * Starts the script-running magic. This will parse the script,
          * initialize some internal state, start downloading the page requested
          * in the script, and return. The remaining of the script processing
          * will happen asynchronously -- signals and slots will work to make
          * the proper things being called at the right times.
          * @param errMsg In case of error, an error message is returned here.
          * @return \c true if everything went fine; \c false otherwise.
          */
         bool startRunning(std::string& errMsg);

      private slots:
         /// Called when \c webPage_ finishes loading the url.
         void onLoadFinished(bool ok);

         /// Called when the post-finish delay (if any) completes.
         void onDelayFinished();

      private:
         /**
          * Runs the script's \c PostLoad() Lua function, and requests to exit
          * the application. If no \c PostLoad() function was defined, just the
          * exit request will be done.
          */
         void runPostLoadAndQuit();

         /// The path to the script file being run.
         const std::string scriptFilePath_;

         /// The Qt object used to load the web page.
         QWebPage webPage_;

         /// The timer used to wait after finishing.
         QTimer timer_;

         /// The Lua interpreter used to run the script.
         Diluculum::LuaState luaState_;
   };

} // namespace Dominus

#endif // _DOMINUS_SCRIPTRUNNER_HPP_
