# LocalMovieQT

LocalMovieQT is a small C++/Qt application for managing a local movie collection with Admin and User modes. It provides features to add/remove/update movies (admin), browse and maintain a watchlist (user), and includes undo/redo support.

Key features
- Admin mode: add, edit, delete movies
- User mode: browse movies, add to watchlist, view watchlist
- Watchlist persisted in `Watchlist.txt`
- Simple file-based storage in `Movies.txt`
- Undo/Redo support

Requirements
- Windows
- Visual Studio 2019 or 2022 (MSVC toolset)
- Qt (Qt 5.x or Qt 6.x) and Qt Visual Studio Tools configured
- C++14-compatible compiler

Build instructions
1. Open the `LocalMovieQT` project in Visual Studio by loading the `.sln` or `LocalMovieQT.vcxproj` file.
2. Ensure Qt is installed and Qt VS Tools are configured so that the project can find Qt include/libs.
3. Set the desired configuration (Debug/Release) and build the solution.
4. Run the application from Visual Studio or run the produced executable from the `Debug` / `Release` folder.

Project layout (important files)
- `UserScreen.h`, `UserScreen.cpp` - UI and logic for the user interface
- `AdminScreen.h`, `AdminScreen.cpp` - UI and logic for the admin interface
- `ServiceUser.h`, `ServiceAdmin.cpp` - application service layer
- `WatchlistTableModel.h` - Qt table model for the watchlist view
- `Movies.txt`, `Watchlist.txt` - simple file-based data stores

Usage
- Launch the application and choose Admin or User mode.
- Admin: manage the movie repository (add/update/delete movies).
- User: browse movies and add entries to your watchlist.

Contributing
- Feel free to open issues or submit pull requests. Follow the existing code style and target C++14 for compatibility.

License
This project is provided under the terms described in the `LICENSE` file.

