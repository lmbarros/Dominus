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


#include "ScriptRunner.hpp"
#include <QCoreApplication>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebFrame>

#include <iostream> // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


namespace Dominus
{
   // - ScriptRunner::ScriptRunner ---------------------------------------------
   ScriptRunner::ScriptRunner(const std::string& scriptFilePath)
      : scriptFilePath_(scriptFilePath)
   { }


   // - ScriptRunner::startRunning ---------------------------------------------
   bool ScriptRunner::startRunning(std::string& errMsg)
   {
      try
      {
         // First load the script
         luaState_.doFile(scriptFilePath_);

         if (luaState_["url"].value().type() != LUA_TSTRING)
         {
            errMsg = "Variable 'url' not defined in '"
               + scriptFilePath_ + "'.";
            return false;
         }

         // Everything is OK, set everything else up
         connect(&webPage_, SIGNAL(loadFinished(bool)),
                 this, SLOT(onLoadFinished(bool)));

         timer_.setSingleShot(true);

         // And, finally, start loading the page.
         webPage_.mainFrame()->load(
            QUrl::fromUserInput(luaState_["url"].value().asString().c_str()));
      }
      catch(std::exception& e)
      {
         errMsg = e.what();
         return false;
      }
      catch(...)
      {
         errMsg = "Unknown error while running '" + scriptFilePath_ + "'.";
         return false;
      }

      return true;
   }


   // - ScriptRunner::onLoadFinished -------------------------------------------
   void ScriptRunner::onLoadFinished(bool ok)
   {
      std::cerr << "ScriptRunner::onLoadFinished()\n"; // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      int delay = 0;

      if (luaState_["delay"].value().type() == LUA_TNUMBER)
         delay = luaState_["delay"].value().asNumber() * 1000;

      if (delay > 0)
      {
         connect(&timer_, SIGNAL(timeout()), this, SLOT(onDelayFinished()));
         timer_.start(delay);
      }
      else
      {
         runPostLoadAndQuit();
      }
   }


   // - ScriptRunner::onDelayFinished ------------------------------------------
   void ScriptRunner::onDelayFinished()
   {
      std::cerr << "ScriptRunner::onDelayFinished()\n"; // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
      runPostLoadAndQuit();

#if 0
      QWebElement doc = webPage_.mainFrame()->documentElement();

      if (doc.isNull())
         std::cerr << "Oh, my!!!\n";

      QWebElement e = doc.findFirst("a#gb_1");

      if (e.isNull())
         std::cerr << ":-(\n";
      else
         std::cerr << e.toPlainText().toStdString() << '\n';

      std::cerr << "Really finished!\n";

      std::cout << doc.toInnerXml().toStdString();
      QCoreApplication::quit();
#endif
   }


   // - ScriptRunner::runPostLoadAndQuit ---------------------------------------
   void ScriptRunner::runPostLoadAndQuit()
   {
      std::cerr << "ScriptRunner::runPostLoadAndQuit()\n"; // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      if (luaState_["PostLoad"].value().type() == LUA_TFUNCTION)
         luaState_["PostLoad"]();

      QCoreApplication::quit();
   }

} // namespace Dominus
