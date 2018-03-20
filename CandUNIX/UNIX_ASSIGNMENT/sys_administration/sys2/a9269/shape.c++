# include <curses.h>

// Abstract shape class

class shape {
	protected:
		WINDOW * & win;
	public:
		shape ( WINDOW * & w ) : win ( w ) {  }
		virtual void draw ()  = 0;
		virtual void erase ()  = 0;
};
