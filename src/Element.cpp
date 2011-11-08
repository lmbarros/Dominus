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


#include "Element.hpp"
#include <Diluculum/LuaExceptions.hpp>
#include <Diluculum/LuaWrappers.hpp>


namespace Dominus
{
   // - Element::Element -------------------------------------------------------
   Element::Element(const QWebElement* element)
      : element_(element)
   { }


   Element::Element(const Diluculum::LuaValueList& params)
      : element_(0)
   {
      throw Diluculum::LuaError("Elements cannot be constructed from Lua.");
   }


   // - Element::getFirstAsText ------------------------------------------------
   Diluculum::LuaValueList
   Element::getFirstAsText(const Diluculum::LuaValueList& params)
   {
      if (params.size() != 1 || params[0].type() != LUA_TSTRING)
      {
         throw std::runtime_error(
            "Bad parameters passed to Element::getFirstAsText()");
      }

      QWebElement e = element_->findFirst(params[0].asString().c_str());

      Diluculum::LuaValueList ret;

      if (e.isNull())
         ret.push_back(Diluculum::Nil);
      else
         ret.push_back(e.toPlainText().toStdString());

      return ret;
   }


   // Wrap Element using Diluculum
   DILUCULUM_BEGIN_CLASS(Element);
      DILUCULUM_CLASS_METHOD (Element, getFirstAsText);
   DILUCULUM_END_CLASS(Element);


   // - RegisterElement --------------------------------------------------------
   void RegisterElement(Diluculum::LuaState& luaState)
   {
      DILUCULUM_REGISTER_CLASS(luaState["Element"], Element);
   }

} // namespace Dominus
