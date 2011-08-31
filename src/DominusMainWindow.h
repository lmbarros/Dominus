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

#ifndef _DOMINUS_MAINWINDOW_H_
#define _DOMINUS_MAINWINDOW_H_

#include "ui_DominusMainWindow.h"
#include <QTimer>


namespace Dominus
{
   /// The main (and only!) window of Dominus.
   class DominusMainWindow: public QMainWindow, public Ui::DominusMainWindow
   {
      Q_OBJECT
      public:
         /// Constructs the \c DominusMainWindow.
         DominusMainWindow(QMainWindow* parent = 0);

         /// Destroys the \c DominusMainWindow.
         ~DominusMainWindow();

      private slots:
         /// Called when \c webView finishes loading a page.
         void on_webView_loadFinished(bool ok);

         /**
          * Called when the post-finish waiting finishes.
          */
         void waitingFinished();

      private:
         /// The timer used to wait after finishing.
         QTimer timer_;

   };

} // namespace Dominus

#endif // _DOMINUS_MAINWINDOW_H_
