#include <iostream>
#include <gtkmm/main.h>
#include <gtkmm/builder.h>
#include <gtkmm/liststore.h>

#include "main-window.h"
#include "json-parser.h"

#define GLADE_FILE "/home/ilan/Dropbox/dev/pmu/pmu.glade"

using namespace Glib;
using namespace Gtk;

class TreeUrlsCols : public TreeModelColumnRecord
{
public:
	
	TreeUrlsCols()
	{ 
    	add(mColSelected);
    	add(mColUrl);
    	add(mColCountry);
    	add(mColScore);
    }

	Gtk::TreeModelColumn<bool> mColSelected;
	Gtk::TreeModelColumn<Glib::ustring> mColUrl;
	Gtk::TreeModelColumn<Glib::ustring> mColCountry;
	Gtk::TreeModelColumn<int> mColScore;
};

Pmu::MainWindow::MainWindow(ustring &title) : 	default_width(400), default_height(550)
{
	TreeUrlsCols cols;
	RefPtr<Builder> builder = Builder::create_from_file(GLADE_FILE);
	RefPtr<ListStore> pList = ListStore::create(cols);
	TreeViewColumn *col = NULL;	
	JsonParser tmp;
	
	builder->get_widget("lblVersion", lblVersion);
	builder->get_widget("lblDate", lblLastCheck);
	builder->get_widget("mainWindow", mwin);
	builder->get_widget("treeUrls", treeUrls);
	builder->get_widget("btnClose", btnClose);
	builder->get_widget("btnApply", btnApply);
	
	// Setting up the columns
	treeUrls->set_model(pList);
	col = treeUrls->get_column(treeUrls->append_column("", cols.mColSelected) - 1);
	col->set_min_width(30);
	col = treeUrls->get_column(treeUrls->append_column("Url", cols.mColUrl) - 1);
	col->set_min_width(120);
	col->set_resizable();
	col = treeUrls->get_column(treeUrls->append_column("Country", cols.mColCountry) - 1);
	col->set_min_width(60);
	col->set_clickable();
	col->set_resizable();
	col->set_sort_column(cols.mColCountry);
	col = treeUrls->get_column(treeUrls->append_column("Score", cols.mColScore) - 1);
	col->set_clickable();
	col->set_sort_column(cols.mColScore);
	col->set_resizable();
	
	mwin->set_title(title);
	mwin->set_default_size(default_width, default_width);
	
	btnClose->signal_clicked().connect(sigc::mem_fun(*this, &Pmu::MainWindow::btnClose_on_click));
	
	/* Testing */
	if(tmp.parse("/home/ilan/Desktop/tmp.json")) {
		ustring ver(ustring("" + tmp.getVersion())), lcheck(ustring(tmp.getLastCheck()));
		
		lblVersion->set_text(ver);
		lblLastCheck->set_text(lcheck);
	
		for(int i=0; i < tmp.getUrls().size(); i++) { 
			std::string url = tmp.getUrls()[i].getUrl();
			std::string country = tmp.getUrls()[i].getCountry();
			
			insert(url, country, tmp.getUrls()[i].getScore());
		}
	} else 
		std::cout<< "could not load the file"<< std::endl;
	/*End of testing */
	mwin->show_all();
}

void Pmu::MainWindow::insert(const std::string& url, const std::string& country, int score)
{
	TreeUrlsCols m;
	RefPtr<ListStore> list = RefPtr<ListStore>::cast_dynamic(treeUrls->get_model());
	Gtk::TreeModel::iterator iter = list->append();
	Gtk::TreeModel::Row row = *iter;
	
	row[m.mColSelected] = false;
	row[m.mColUrl] = url;
	row[m.mColCountry] = country;
	row[m.mColScore] = score;
}

void Pmu::MainWindow::btnClose_on_click()
{
	//std::cout<< "closing the window."<< std::endl;
	Gtk::Main::quit();
}


int main(int argc, char** argv)
{
	Main kit(argc, argv);
	ustring title("Pacman Update Manager");
	Pmu::MainWindow pmu(title);
	
	kit.run(*pmu.mwin);
}
