#ifndef PMU_MAIN_WINDOW_H
#define PMU_MAIN_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/treeview.h>
#include <gtkmm/comboboxtext.h>

#define GLADE_FILE "/home/ilan/Dropbox/dev/pmu/pmu.glade"

namespace Pmu
{
	class MainWindow
	{
		public:
			MainWindow(Glib::ustring &title, const char* file = GLADE_FILE);
			Gtk::Window *mwin;
		private:
			const int default_width;
			const int default_height;
			
			std::string uiFile;
			
			Gtk::ComboBoxText *comboProtocols;
			Gtk::Label *lblVersion;
			Gtk::Label *lblLastCheck;
			Gtk::Button *btnClose;
			Gtk::Button *btnApply;
			Gtk::TreeView *treeUrls;
			
			void btnClose_on_click();
			void btnApply_on_click();
			void insert(const std::string& url, int completion, const std::string& country, double score);
			
	};
};

#endif
