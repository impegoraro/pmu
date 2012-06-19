#include <iostream>
#include <stdlib.h>
#include <gtkmm/main.h>
#include <gtkmm/builder.h>
#include <gtkmm/liststore.h>
#include <curl/curl.h>
#include <unistd.h>

#include "error-codes.h"
#include "main-window.h"
#include "json-parser.h"

using namespace Glib;
using namespace Gtk;
using namespace std;

class TreeUrlsCols : public TreeModelColumnRecord
{
public:
	
	TreeUrlsCols()
	{ 
    	add(mColSelected);
    	add(mColUrl);
    	add(mColCompletion);
    	add(mColCountry);
    	add(mColScore);
    }

	Gtk::TreeModelColumn<bool> mColSelected;
	Gtk::TreeModelColumn<ustring> mColUrl;
	Gtk::TreeModelColumn<int> mColCompletion;
	Gtk::TreeModelColumn<ustring> mColCountry;
	Gtk::TreeModelColumn<double> mColScore;
};


Pmu::MainWindow::MainWindow(ustring &title, const char *file) : 
	default_width(400), default_height(550), uiFile(file)
{

	if (downloadFile() == OK) {

	TreeUrlsCols cols;
	RefPtr<Builder> builder = Builder::create_from_file(uiFile);
	RefPtr<ListStore> pList = ListStore::create(cols);
	TreeViewColumn *col = NULL;	
	JsonParser tmp;
	
	builder->get_widget("lblVersion", lblVersion);
	builder->get_widget("comboProtocols", comboProtocols);
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
	col = treeUrls->get_column(treeUrls->append_column("Completion", cols.mColCompletion) - 1);
	col->set_min_width(68);
	col->set_resizable();
	col->set_clickable();
	col->set_sort_column(cols.mColCompletion);
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
	mwin->set_size_request(default_width, default_width);
	
	btnClose->signal_clicked().connect(sigc::mem_fun(*this, &Pmu::MainWindow::btnClose_on_click));
	
	/* Testing */
	if(tmp.parse(filePath)) {
		ustring ver(ustring("" + tmp.getVersion())), lcheck(ustring(tmp.getLastCheck()));
		
		lblVersion->set_text(ver);
		lblLastCheck->set_text(lcheck);
	
		comboProtocols->remove_all();
		comboProtocols->append("");
		for(int i = 0; i < tmp.getProtocols().size(); i++) {
			cout<< tmp.getProtocols()[i]<< endl;	
			comboProtocols->append(tmp.getProtocols()[i]);
		}
	
		for(int i=0; i < tmp.getUrls().size(); i++) { 
			std::string url = tmp.getUrls()[i].getUrl();
			std::string country = tmp.getUrls()[i].getCountry();
			
			insert(url, (int) (tmp.getUrls()[i].getCompletion() * 100), country, tmp.getUrls()[i].getScore());
		}
	} else 
		std::cout<< "could not load the file"<< std::endl;
	/*End of testing */
	mwin->show_all();
	}
}

void Pmu::MainWindow::insert(const std::string& url, int completion,const std::string& country, double score)
{
	TreeUrlsCols m;
	RefPtr<ListStore> list = RefPtr<ListStore>::cast_dynamic(treeUrls->get_model());
	TreeModel::iterator iter = list->append();
	TreeModel::Row row = *iter;
	
	row[m.mColSelected] = false;
	row[m.mColUrl] = url;
	row[m.mColCompletion] = completion;
	row[m.mColCountry] = country;
	row[m.mColScore] = score;
}

void Pmu::MainWindow::btnClose_on_click()
{
	//std::cout<< "closing the window."<< std::endl;
	Gtk::Main::quit();
}

int Pmu::MainWindow::downloadFile() {

	int returnValue = NO_FILE;

	CURL *curl;
	CURLcode curlGetResult;

	string tmpDownloadFile ("/tmp/pmuTmp.json");

	filePath = JSON_DIRECTORY;
	filePath = filePath.append("/").append(JSON_FILE);

	FILE *jsonFile;

	curl_global_init(CURL_GLOBAL_ALL);

	/* Initialize curl */
	curl = curl_easy_init();

	/* Set the download URL */
	curl_easy_setopt(curl, CURLOPT_URL, JSON_URL);
	/* Set no progress display */
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

	returnValue = access(filePath.c_str(), F_OK);

	jsonFile = fopen(tmpDownloadFile.c_str() , "wb");

	if (jsonFile != NULL) {

		/* DownloadFile from web */
		curl_easy_setopt(curl, CURLOPT_FILE, jsonFile);
		curlGetResult = curl_easy_perform(curl);

		fclose(jsonFile);

		if (curlGetResult == CURLE_OK) {
			remove(filePath.c_str());
			rename(tmpDownloadFile.c_str(), filePath.c_str());

			returnValue = OK;
		}
	}

	curl_easy_cleanup(curl);

	cout << "Result of CURL getting file:  " << curlGetResult << endl;

	return returnValue;

}

int main(int argc, char** argv)
{
	Main kit(argc, argv);
	ustring title("Pacman Update Manager");
	char *uiFile = getenv("PMU_GLADE_FILE");
	Pmu::MainWindow *pmu;

	if(uiFile != NULL) {
		cout<< "Find out PMU_GLADE_FILE environment variable, using that instead of the installed file."<< endl;
		pmu = new Pmu::MainWindow(title, uiFile);
	}
	else
		pmu = new Pmu::MainWindow(title);

	kit.run(*pmu->mwin);

	delete pmu;
}



