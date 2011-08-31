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


#include "WebPage.hpp"
#include <QCoreApplication>
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebFrame>

#include <iostream>


namespace Dominus
{
   // - WebPage::WebPage -------------------------------------------------------
   WebPage::WebPage(const std::string& url, int delay)
      : delay_(delay)
   {
      connect(&webPage_, SIGNAL(loadFinished(bool)),
              this, SLOT(onLoadFinished(bool)));
      timer_.setSingleShot(true);
      webPage_.mainFrame()->load(QUrl::fromUserInput(url.c_str()));
   }


   // - WebPage::onLoadFinished ------------------------------------------------
   void WebPage::onLoadFinished(bool ok)
   {
      std::cerr << "WebPage::onLoadFinished()\n";
      connect(&timer_, SIGNAL(timeout()), this, SLOT(onDelayFinished()));
      timer_.start(delay_);
   }


   // - WebPage::onDelayFinished -----------------------------------------------
   void WebPage::onDelayFinished()
   {
      std::cerr << "WebPage::onDelayFinished()\n";

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
   }

} // namespace Dominus
