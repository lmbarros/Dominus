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
#include "Element.hpp"
#include <QCoreApplication>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebFrame>
#include <Diluculum/LuaWrappers.hpp>

#include <iostream> // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


namespace Dominus
{
   /// The name of the Lua table used to store Dominus internal stuff.
   const std::string DOMINUS_LUA_TABLE = "__Dominus__";


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
         RegisterElement(luaState_);
         luaState_[DOMINUS_LUA_TABLE] = Diluculum::LuaValueMap();

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
   }


   // - ScriptRunner::runPostLoadAndQuit ---------------------------------------
   void ScriptRunner::runPostLoadAndQuit()
   {
      std::cerr << "ScriptRunner::runPostLoadAndQuit()\n"; // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      if (luaState_["PostLoad"].value().type() == LUA_TFUNCTION)
      {
         QWebElement doc = webPage_.mainFrame()->documentElement();

         if (doc.isNull())
            throw std::runtime_error("Got a null document Web Element");

         Element docElement(&doc);

         DILUCULUM_REGISTER_OBJECT(luaState_[DOMINUS_LUA_TABLE]["e"],
                                   Element, docElement);
         luaState_.doString("PostLoad(" + DOMINUS_LUA_TABLE + ".e)");
      }

      QCoreApplication::quit();
   }

} // namespace Dominus
