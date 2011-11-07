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


#include <iostream>
#include <stdexcept>
#include <QApplication>
#include "ScriptRunner.hpp"


void ShowUsage(const std::string& argv0)
{
   std::cerr << "Usage: " << argv0 << " <SCRIPT FILE>\n"
             << "Dominus is a scriptable, window-less, non-browseable "
             << "web browser.\n";
}


/// Dominus' entry point.
int main(int argc, char* argv[])
{
   try
   {
      using namespace Dominus;

      QApplication app(argc, argv);

      if (argc != 2)
      {
         ShowUsage(argv[0]);
         return EXIT_FAILURE;
      }

      const std::string scriptFile(argv[1]);

      ScriptRunner runner(scriptFile);

      std::string errMsg;
      const bool success = runner.startRunning(errMsg);

      if (!success)
      {
         std::cerr << "Error: " << errMsg << '\n';
         return EXIT_FAILURE;
      }

      return app.exec();
   }
   catch (std::exception& e)
   {
      std::cerr << "Standard exception caught at 'main()':\n"
                << e.what() << '\n';
      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cerr << "Unknown exception caught at 'main()'.\n";
      return EXIT_FAILURE;
   }
}
