CC=g++

LIBS=-lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lpangomm-1.4 -lgtk-3 -lglibmm-2.4 -lcairomm-1.0 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lsigc-2.0 -lgobject-2.0 -lglib-2.0 -ljson_linux-gcc-4.7.0_libmt -lcurl

CFLAGS=-pthread -I/usr/include/gtkmm-3.0 -I/usr/lib/gtkmm-3.0/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/pangomm-1.4/include -I/usr/include/gtk-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/cairomm-1.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/gdkmm-3.0 -I/usr/lib/gdkmm-3.0/include -I/usr/include/atk-1.0 -I/usr/include/glibmm-2.4 -I/usr/lib/glibmm-2.4/include -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sigc++-2.0 -I/usr/lib/sigc++-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/gio-unix-2.0/ 


OBJECTS=mirror.o json-parser.o main-window.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o pmu

main-window.o: src/main-window.cpp
	$(CC) $(CFLAGS) $(LIBS)  -c $< -o main-window.o

mirror.o: src/mirror.cpp
	$(CC) -c $<

json-parser.o: src/json-parser.cpp
	$(CC) $(LIBS) -c  $<

clean:
	rm *.o

cleanall: clean
	rm pmu

