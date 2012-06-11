#ifndef PMU_MAIN_WINDOW_H
#define PMU_MAIN_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/treeview.h>

namespace Pmu
{
	class MainWindow
	{
		public:
			MainWindow(Glib::ustring &title);
			Gtk::Window *mwin;
		private:
			const int default_width;
			const int default_height;
			
			Gtk::Label *lblVersion;
			Gtk::Label *lblLastCheck;
			Gtk::Button *btnClose;
			Gtk::Button *btnApply;
			Gtk::TreeView *treeUrls;
			
			void btnClose_on_click();
			void btnApply_on_click();
			void insert(const std::string& url, const std::string& country, int score);
	};
};

#endif
