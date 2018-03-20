
class complex {
	double real, img;
	
	public :
		complex ( double re = 0 , double im = 0 ) : real ( re ), img ( im ) { }
/*		complex ( const complex &a ) {
			cout << "copy constructor\n";
			real = a.real;
			img  = a.img;
		} */
		complex & operator += ( const complex &a ) {
			real += a.real;
			img  += a.img;
			return *this;
		}
		complex & operator -= ( const complex &a ) {
			real -= a.real;
			img  -= a.img;
			return *this;
		}
		complex & operator *= ( const complex &a ) {
			real = ( real * a.real ) - ( img * a.img );
			img  = ( real * a.img  ) + ( img * a.real );
			return *this;
		}
		complex & operator /= ( const complex &a ) {
			double deno;
			deno = ( a.real * a.real ) + ( a.img * a.img ); 
			real = ( (real * a.real ) + ( img * a.img ) ) / deno ;
			img  = ( ( img * a.real ) - ( real * a.img ) ) / deno;
			return *this;
		}
		complex & operator =  ( const complex &a ) {
			if ( &a == this ) return *this;
			real = a.real;
			img  = a.img;
			return *this;
		}

		friend complex  operator+ ( const complex &a, const complex &b ) {
			return  complex ( a.real + b.real, a.img + b.img );
		}
		friend complex  operator- ( const complex &a, const complex &b ){
			return  complex ( a.real - b.real, a.img - b.img );
		}
		friend complex  operator* ( const complex &a, const complex &b ){
			complex res;
			res.real = ( a.real * b.real ) - ( a.img * b.img  );
			res.img  = ( a.real * b.img  ) + ( a.img * b.real );
			return  res;
		}
		friend complex  operator/ ( const complex &a, const complex &b ){
			complex res;
			double deno;
			deno =  ( b.real * b.real ) + ( b.img * b.img );
			res.real = ( ( a.real * b.real ) + ( a.img * b.img ) ) / deno;
			res.img  = ( ( a.img * b.real ) - ( a.real * b.img ) ) / deno;
			return  res;
		}
		friend bool operator!=( const complex &a, const complex &b ){
			return ( a.real != b.real ) || (a.img == b.img ) ;
		}
		friend bool operator==( const complex &a, const complex &b ){
			return ( a.real == b.real ) && (a.img == b.img ) ;
		}
		friend ostream & operator << ( ostream &s, const complex &c ){
			cout << '(' << c.real << "," << c.img << ')' ;
			return s;
		}
		friend istream & operator >> ( istream &s, complex &c ){
			double real, img;
			cin >> c.real >> c.img;
			return s;
		}
};
