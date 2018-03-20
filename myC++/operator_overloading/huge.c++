# include <iostream>
# include <signal.h>
# include <stdlib.h>
# include <string.h>

using namespace std;

# include "huge.h"

void huge :: do_fragment ( const char *str ) {
	int count, i;
	char *p ,*save_str;

	save_str =  (char *)str ;
	if ( save_str[0] == '\0' ) {
		sign = '+';
		integral = strdup ( "\0" );
		decimal  = strdup ( "\0" );
	}
	for ( ; save_str && isblank ( *save_str )|| *save_str == '0' ; save_str++ );
	if ( *save_str == '-' ) { sign = '-' ; save_str++; }
	else sign = '+';
	if ( *save_str == '+' ) save_str++;
	for ( p = save_str, count = 0; *p != '.' && *p!='\0' ; p++, count++ );
	integral = new char[count+1];
	for ( i = 0; i < count ; i++ )
		integral[i] = *save_str++;
	integral[i] = '\0';
	if ( *save_str == '.' ) {
		save_str++;
		for ( p = save_str, count = 0; !isblank(*p) && *p!= '\0';p++, count++ );
		decimal = new char[count + 1];
		for ( i = 0; i < count; i++ )
			decimal[i] = *save_str++;
		decimal[i] = '\0';
	}
}

huge :: huge ( const char *a_str ) {
	do_fragment ( a_str );
}
/* compare returns 0 on b > a
                   1 on a > b
				   2 on a == b */

int huge :: compare ( const huge &b ) const{
	int a_ilen, b_ilen, a_dlen, b_dlen, dec_len, i;

	a_ilen = strlen ( integral );
	b_ilen = strlen ( b.integral );
	a_dlen = strlen ( decimal );
	b_dlen = strlen ( b.decimal );
	if ( a_ilen > b_ilen )
		return 1;
	else if ( b_ilen > a_ilen ) return 0;
	for ( i = 0; i < a_ilen; i++ ) {
		if ( integral[i] > b.integral[i] )
			return 1;
		else if ( b.integral[i] > integral[i] )
			return 0;
	}
	dec_len = a_dlen < b_dlen ? a_dlen : b_dlen;
	for ( i = 0; i < dec_len; i++ ) {
		if ( decimal[i] > b.decimal[i] )
			return 1;
		else if ( b.decimal[i] > decimal[i] )
			return 0;
	}
	if ( a_dlen > b_dlen ) return 1;
	else if ( b_dlen > a_dlen ) return 0;
	return 2;
}

huge  huge :: add ( const huge &b ) const {
	huge c;
	int a_ilen, b_ilen, a_dlen, b_dlen,diff_dlen;
	int carry, res,i,j ;

	a_ilen = strlen ( integral );
	a_dlen = strlen ( decimal  );
	b_ilen = strlen ( b.integral );
	b_dlen = strlen ( b.decimal  );
	i = a_dlen >= b_dlen ? (a_dlen + 1): (b_dlen + 1 );
	c.decimal = new char[i--];
	c.decimal[i--] = '\0';
	if ( a_dlen != b_dlen ) {
		diff_dlen = a_dlen > b_dlen ? ( a_dlen - b_dlen ) : ( b_dlen - a_dlen );
		for ( j =0 ;j < diff_dlen; i-- ,j++)
			if ( a_dlen > b_dlen )
				c.decimal[i] = decimal[i];
			else if ( b_dlen > a_dlen )
				c.decimal[i] = b.decimal[i];
	} 
	for ( carry = 0; i >= 0; i-- ){
		res = (decimal[i] - '0') + (b.decimal[i] - '0') + carry;
		if ( res > 9 ) {
			c.decimal[i] = ( res % 10 ) + '0';
			carry = res / 10;
		} else c.decimal[i] = res + '0';
	}
	// adding integral part
	i = a_ilen + 2;
	c.integral = new char[i--];
	c.integral[i--] = '\0';
	for ( j = 0, a_ilen--, b_ilen--; a_ilen >= 0 && b_ilen >= 0; 
							j++ , a_ilen--,b_ilen--,i--) {
		res = (integral[a_ilen] - '0') + (b.integral[b_ilen] - '0') + carry;
		if ( res > 9 ) {
			c.integral[i] = (res % 10) + '0';
			carry = res / 10;
		} else c.integral[i] = res + '0';
	}
	j = a_ilen >= 0 ? a_ilen : b_ilen;
	for ( ;j >= 0 ; i--, j--, carry = 0)
		c.integral[i] = ((integral[j] - '0' ) + carry )+ '0';
	if ( carry == 0 ) strcpy ( c.integral, c.integral + 1 );
	else c.integral[i--] = carry + '0';
	cout << "End add\n";
	return c;
}

huge huge :: sub ( const huge &b ) const {
	int a_ilen, b_ilen, a_dlen, b_dlen, diff_len;
	int i,j, barrow = 0, res;
	huge c;
	
	a_ilen = strlen ( integral   );
	a_dlen = strlen ( decimal    );
	b_ilen = strlen ( b.integral );
	b_dlen = strlen ( b.decimal  );
	i = a_dlen >= b_dlen ? (a_dlen + 1) : (b_dlen + 1);
	c.decimal = new char[i--];
	c.decimal[i--] = '\0';
	a_dlen--;
	b_dlen--;
	for ( ;a_dlen > b_dlen ;i--, a_dlen--) 
		c.decimal[i] = decimal[a_dlen];
	for ( ;b_dlen > a_dlen; i--, b_dlen-- ) {
		res = '0' - b.decimal[b_dlen] + barrow;
		if ( res < 0 ) {
			res += 10;
			barrow = -1;
		}else barrow = 0;
		c.decimal[i] = res + '0';
	}
	for ( ; a_dlen>=0 && b_dlen >=0 ; a_dlen--, b_dlen--,i-- ) {
		res = ( decimal[a_dlen] - '0' ) - (b.decimal[b_dlen] - '0' ) + barrow;
		if ( res < 0 ) {
			res += 10;
			barrow = -1;
		} else	barrow = 0;
		c.decimal[i] = res + '0';
	}
	i = a_ilen + 1;
	a_ilen--;
	b_ilen--;
	c.integral = new char[i--];
	c.integral[i--] = '\0';
	for (; a_ilen >=0 && b_ilen >=0; i--, a_ilen--, b_ilen-- ) {
		res = (integral[a_ilen] - '0' ) - ( b.integral[b_ilen] - '0' ) + barrow;
		if ( res < 0 ) {
			res += 10;
			barrow  = -1;
		} else barrow = 0;
		c.integral[i] = res + '0';
	}
	for ( ; a_ilen >=0 ; a_ilen--, i-- , barrow = 0)
		c.integral[i] = integral[a_ilen] + barrow;
	return c;
}

huge & huge :: operator+= ( const huge &b ) {
	int bigger;
	
	if ( sign != b.sign ) {
		bigger = compare ( b );
		if ( bigger == 1 || bigger == 2 ) 
			*this = sub ( b );
		else {
			*this = b.sub ( *this );
			sign = b.sign;
		}
	} else  *this = add ( b );
	return *this;
}

huge operator+ ( const huge &a, const huge &b ) {
	huge c;
	int bigger;

	if ( a.sign != b.sign ) {
		bigger = a.compare ( b );
		if ( bigger == 1 || bigger == 2 ) {
			c = a.sub( b );
			c.sign = a.sign;
		}
		else {
			c = b.sub( a );
			c.sign = b.sign;
		}
	}
	else {
		cout << "before add\n";
		c = a.add( b );
		cout << "after add\n";
		c.sign = a.sign;
	}
	return c;
}

huge & huge :: operator-= ( const huge &b ) {
	int bigger;

	bigger = compare ( b );
	if ( sign == b.sign ) 
		if ( bigger != 1 ) {
			*this = b.sub ( *this );
			if ( b.sign == '-' )
				sign = '+';
			else sign = '-';
		} else  *this = sub ( b );
	else *this = add ( b );
	return *this;
}

huge operator- ( const huge &a, const huge &b ) {
	huge c;
	int bigger;

	bigger = a.compare ( b );
	if ( a.sign == b.sign ) {
		if ( bigger == 1 || bigger == 2 ) {
			c = a.sub ( b );
			c.sign = a.sign;
		}
		else {
			c = b.sub ( a );
			if ( b.sign == '-' )
				 c.sign = '+';
			else c.sign = '-';
		}
	} else { 
		c = a.add ( b );
		c.sign = a.sign;
	}
	return c;
}

int operator== ( const huge &a, const huge &b ) {
	if ( (a.sign == b.sign) && a.compare ( b ) == 2)
		return 1;
	return 0;
}

int operator!= ( const huge &a, const huge &b ) {
	if ( a.sign != b.sign || a.compare ( b ) != 2 )
		return 1;
	return 0;
}

int operator> ( const huge &a, const huge &b ) {
	if ( a.sign != b.sign ) {
		if ( a.sign == '+' )
			return 1;
		return 0;
	}
	else {
		if ( a.compare ( b ) == 1 )
			return 1;
		return 0;
	}
}

int operator< ( const huge &a, const huge &b ) {
	if ( a.sign != b.sign ) {
		if ( a.sign == '-' )
			return 1;
		return 0;
	}
	else {
		if ( a.compare ( b ) == 0 )
			return 1;
		return 0;
	}
}

int operator<= ( const huge &a, const huge &b ) {
	if ( a.sign != b.sign ) {
		if ( a.sign == '-' )
			return 1;
		return 0;
	}
	else {
		if ( a.compare ( b ) != 1  )
			return 1;
		return 0;
	}
}

int operator>= ( const huge &a, const huge &b ) {
	if ( a.sign != b.sign ) {
		if ( b.sign == '-' )
			return 1;
		return 0;
	}
	else {
		if ( a.compare ( b ) != 0 )
			return 1;
		return 0;
	}
}

istream & operator>> ( istream &s, huge &a ) {
	string str1;

	cin >> str1;
	a.do_fragment ( str1.data( ) );
	return s;
}

ostream & operator<< ( ostream &s, const huge &a ) {
	cout << a.sign << a.integral << "." << a.decimal ;
	return s;
}
void katch ( int sig ) {
	cout << "Improper data for manipulation ( stop ). \n";
	exit ( 1 );
}

main ( ) {
	huge h1, h2,h3, h4;
	int res;
	
	signal ( SIGSEGV, katch );
	cout << "Enter two huge numbers\n";
	cin >> h1;
	cin >> h2;
	h4 = h1;
	cout << "ADDITION\n";
	h3 = h1 + h2;
	cout << " h3 = h1 + h2 is " << h3 << endl;
	h1 += h2;
	cout << "h1 += h2 is " << h1 << endl;
	h1 = h4;
	cout << "SUBTRACTION\n";
	h3 = h1 - h2;
	cout << "h3 = h1 - h2 is " << h3 << endl;
	h1 -= h2;
	cout << "h1 -= h2 is "<< h1 << endl;
	h1 = h4;
	cout << "COMPARISIONS\n";
	/*res = h1 > h2;
	res > 0 ? cout << "h1 is greater\n": cout << "h2 is greater\n";
	res = h1 >= h2;
	res > 0 ? cout << "h1 is greater or equal\n" : 
		      cout << "h2 is greater or equal\n";
	res = h1 < h2;
	res > 0 ? cout << "h1 is lesser\n" : cout << "h2 is lesser\n";
	res = h1 <= h2;
	res > 0 ? cout << "h1 is lesser or equal\n" : 
		      cout << "h2 is lesser or equal\n";
	res = h1 == h2;
	cout << "res for h1==h2 is "<< res;
	res > 0 ? cout << "EQUAL\n" : cout << "UNEQUAL\n";
	res = h1 != h2;
	cout << res << endl;
	res > 0 ? cout << "UNEQUAL\n" : cout << "EQUAL\n"; */
	if ( h1 > h2 ) 
		 cout << "h1 > h2" << endl;
	else cout << "h1 not > h2" << endl;
	if ( h1 < h2 )
		 cout << "h1 < h2" << endl;
	else cout << "h1 not < h2" << endl;
	if ( h1 >= h2 )
		 cout << "h1 >= h2" << endl;
	else cout << "h1 not >= h2" << endl;
	if ( h1 <= h2 )
		 cout << "h1 <= h2" << endl;
	else cout << "h1 not <= h2" << endl;
	if ( h1 == h2 )
		 cout << "h1 == h2" << endl;
	else cout << "h1 not == h2" << endl;
	if ( h1 != h2 )
		 cout << "h1 != h2" << endl;
	else cout << "h1 not != h2" << endl;
	char * p = h1;
	cout << p << endl;
}
