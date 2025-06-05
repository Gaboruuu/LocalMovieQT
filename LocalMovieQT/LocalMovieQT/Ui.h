#pragma once

#include "ServiceAdmin.h"
#include "ServiceUser.h"

class Ui {
public:
	Ui(ServiceAdmin& admin, ServiceUser& user) : admin{ admin }, user{ user } {}
	~Ui() {}

	void run();
	void user_commands();
	void admin_commands();
	void user_list();
private:
	ServiceAdmin& admin;
	ServiceUser& user;

	static void print_welcome();
	static void print_admin_commands();
	static void print_user_commands();
};