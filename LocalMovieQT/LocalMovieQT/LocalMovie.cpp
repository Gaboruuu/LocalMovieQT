#include <iostream>
#include "Ui.h"
#include "MovieRepository.h"
#include "ServiceAdmin.h"
#include "ServiceUser.h"
#include "WatchListRepository.h"
#include "Domain.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <cassert>
#include "Test.h"


void run();

int main(){
	
	run();
	_CrtDumpMemoryLeaks();

	return 0;
}

void run() {
	test_movie();
	test_service_admin();
	test_service_user();
	MovieRepository repo("Movies.txt");
	WatchListRepository watchlist("Watchlist.txt");
	ServiceAdmin admin{ repo };
	ServiceUser user{ repo, watchlist };
	Ui ui{ admin, user };
	ui.run();
}