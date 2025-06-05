#include "MainWindow.h"
#include "ServiceAdmin.h"
#include "ServiceUser.h"
#include "MovieRepository.h"
#include "WatchListRepository.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

	MovieRepository repo("Movies.txt");
	WatchListRepository watchlist("Watchlist.txt");

    ServiceAdmin adminService(repo); 
    ServiceUser userService(repo, watchlist);

    MainWindow w(adminService, userService);
    w.show();

    return a.exec();
}
