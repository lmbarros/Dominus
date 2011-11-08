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

#ifndef _DOMINUS_ELEMENT_HPP_
#define _DOMINUS_ELEMENT_HPP_

#include <QtWebKit/QWebElement>
#include <Diluculum/LuaState.hpp>


namespace Dominus
{
   /**
    * An HTML element. Basically, this wraps a Qt QWebElement, exposing some
    * methods for use in Lua.
    */
   class Element
   {
      public:
         /**
          * Constructs the \c Element.
          * @param element The Qt HTML element to be wrapped by this \c element.
          */
         Element(const QWebElement* element);

         /**
          * The constructor required by Diluculum. Simply issues an error,
          * because <tt>Element</tt>s cannot be created in the Lua side.
          */
         Element(const Diluculum::LuaValueList& params);

         /**
          * Returns the first HTML element matching a given CSS selector. In
          * Lua, this function takes one parameter: the desired selector (a
          * string). If the requested element does not exist, returns \c
          * nil. Otherwise, returns the element as plain text (a string).
          */
         Diluculum::LuaValueList
         getFirstAsText(const Diluculum::LuaValueList& params);

      private:
         /// The Qt HTML element wrapped by this \c element.
         const QWebElement* element_;
   };


   /**
    * Registers the Element class in a given Lua interpreter.
    * @param luaState The desired interpreter.
    */
   void RegisterElement(Diluculum::LuaState& luaState);

} // namespace Dominus

#endif // _DOMINUS_ELEMENT_HPP_
