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


#include "DominusMainWindow.h"
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebFrame>

#include <iostream>


namespace Dominus
{
   // - DominusMainWindow::DominusMainWindow -----------------------------------
   DominusMainWindow::DominusMainWindow(QMainWindow* parent)
   {
      setupUi(this);
      timer_.setSingleShot(true);
      webView->load(QUrl::fromUserInput("http://www.google.com"));
   }


   // - DominusMainWindow::~DominusMainWindow ----------------------------------
   DominusMainWindow::~DominusMainWindow()
   {
      // Empty
   }


   // - DominusMainWindow::on_webView_loadFinished -----------------------------
   void DominusMainWindow::on_webView_loadFinished(bool ok)
   {
      std::cerr << "DominusMainWindow::on_webView_loadFinished()\n";
      connect(&timer_, SIGNAL(timeout()), this, SLOT(waitingFinished()));
      timer_.start(10000);
   }


   // - DominusMainWindow::waitingFinished -------------------------------------
   void DominusMainWindow::waitingFinished()
   {
      std::cerr << "DominusMainWindow::waitingFinished()\n";

      QWebFrame* mainFrame = webView->page()->mainFrame();

      QWebElement doc = mainFrame->documentElement();

      if (doc.isNull())
         std::cerr << "Oh, my!!!\n";

      QWebElement e = doc.findFirst("a#gb_1");

      if (e.isNull())
         std::cerr << ":-(\n";
      else
         std::cerr << e.toPlainText().toStdString() << '\n';

      std::cerr << "Really finished!\n";

      std::cout << doc.toInnerXml().toStdString();

      close();
   }

} // namespace Dominus
