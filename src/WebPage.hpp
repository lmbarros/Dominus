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

#ifndef _DOMINUS_WEBPAGE_H_
#define _DOMINUS_WEBPAGE_H_

#include <QTimer>
#include <QtWebKit/QWebPage>


namespace Dominus
{
   /// The main (and only!) window of Dominus.
   class WebPage: public QObject
   {
      Q_OBJECT
      public:
         /**
          * Constructs the \c WebPage.
          * xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
          */
         WebPage(const std::string& url, int delay);

      private slots:
         /// Called when \c webPage_ finishes loading the url.
         void onLoadFinished(bool ok);

         /**
          * Called when the post-finish waiting finishes.
          * // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
          */
         void onDelayFinished();

      private:
         // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
         QWebPage webPage_;

         /// The timer used to wait after finishing.
         QTimer timer_;

         // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
         const int delay_;
   };

} // namespace Dominus

#endif // _DOMINUS_WEBPAGE_H_
