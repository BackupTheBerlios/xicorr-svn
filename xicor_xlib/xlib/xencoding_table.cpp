#include "xencoding_table.h"

#include <X11/keysym.h>
#include <X11/keysymdef.h>

namespace xicor {
namespace xlib {
	
	xEncodingTable* xEncodingTable::instance = NULL;
	
	xEncodingTable* xEncodingTable::makeObject(Lang lang)
	{
		if (!xEncodingTable::instance) {
			xEncodingTable::instance = new xEncodingTable();
		}
		if (lang != UNSUPPORTED_LANG)
			xEncodingTable::instance->initTables(lang);
		return xEncodingTable::instance;
	}
	
	xEncodingTable::xEncodingTable()
	{
	}
	
	xEncodingTable::~xEncodingTable()
	{
	}
	
	void xEncodingTable::initTables(Lang lang) throw(XlibException)
	{
		DecodingTable& decoding_table = decoding_tables[lang];
		DecodingTable& inv_decoding_table = inv_decoding_tables[lang];
		switch (lang)
		{
			case RUSSIAN:
			{
				decoding_table[XK_quotedbl] = XK_Cyrillic_E;
				decoding_table[XK_apostrophe] = XK_Cyrillic_e;
				decoding_table[XK_bracketleft] = XK_Cyrillic_HA;
				decoding_table[XK_bracketright] = XK_Cyrillic_HARDSIGN;
				decoding_table[XK_comma] = XK_Cyrillic_be;
				decoding_table[XK_period] = XK_Cyrillic_yu;
				decoding_table[XK_colon] = XK_Cyrillic_ZHE;
				decoding_table[XK_semicolon] = XK_Cyrillic_zhe;
				decoding_table[XK_less] = XK_Cyrillic_BE;
				decoding_table[XK_greater] = XK_Cyrillic_YU;
				decoding_table[XK_braceleft] = XK_Cyrillic_ha;
				decoding_table[XK_braceright] = XK_Cyrillic_hardsign;
				decoding_table[XK_A] = XK_Cyrillic_EF;
				decoding_table[XK_B] = XK_Cyrillic_I;
				decoding_table[XK_C] = XK_Cyrillic_ES;
				decoding_table[XK_D] = XK_Cyrillic_VE;
				decoding_table[XK_E] = XK_Cyrillic_U;
				decoding_table[XK_F] = XK_Cyrillic_A;
				decoding_table[XK_G] = XK_Cyrillic_PE;
				decoding_table[XK_H] = XK_Cyrillic_ER;
				decoding_table[XK_I] = XK_Cyrillic_SHA;
				decoding_table[XK_J] = XK_Cyrillic_O;
				decoding_table[XK_K] = XK_Cyrillic_EL;
				decoding_table[XK_L] = XK_Cyrillic_DE;
				decoding_table[XK_M] = XK_Cyrillic_SOFTSIGN;
				decoding_table[XK_N] = XK_Cyrillic_TE;
				decoding_table[XK_O] = XK_Cyrillic_SHCHA;
				decoding_table[XK_P] = XK_Cyrillic_ZE;
				decoding_table[XK_Q] = XK_Cyrillic_SHORTI;
				decoding_table[XK_R] = XK_Cyrillic_KA;
				decoding_table[XK_S] = XK_Cyrillic_YERU;
				decoding_table[XK_T] = XK_Cyrillic_IE;
				decoding_table[XK_U] = XK_Cyrillic_GHE;
				decoding_table[XK_V] = XK_Cyrillic_EM;
				decoding_table[XK_W] = XK_Cyrillic_TSE;
				decoding_table[XK_X] = XK_Cyrillic_CHE;
				decoding_table[XK_Y] = XK_Cyrillic_EN;
				decoding_table[XK_Z] = XK_Cyrillic_YA;
				decoding_table[XK_a] = XK_Cyrillic_ef;
				decoding_table[XK_b] = XK_Cyrillic_i;
				decoding_table[XK_c] = XK_Cyrillic_es;
				decoding_table[XK_d] = XK_Cyrillic_ve;
				decoding_table[XK_e] = XK_Cyrillic_u;
				decoding_table[XK_f] = XK_Cyrillic_a;
				decoding_table[XK_g] = XK_Cyrillic_pe;
				decoding_table[XK_h] = XK_Cyrillic_er;
				decoding_table[XK_i] = XK_Cyrillic_sha;
				decoding_table[XK_j] = XK_Cyrillic_o;
				decoding_table[XK_k] = XK_Cyrillic_el;
				decoding_table[XK_l] = XK_Cyrillic_de;
				decoding_table[XK_m] = XK_Cyrillic_softsign;
				decoding_table[XK_n] = XK_Cyrillic_te;
				decoding_table[XK_o] = XK_Cyrillic_shcha;
				decoding_table[XK_p] = XK_Cyrillic_ze;
				decoding_table[XK_q] = XK_Cyrillic_shorti;
				decoding_table[XK_r] = XK_Cyrillic_ka;
				decoding_table[XK_s] = XK_Cyrillic_yeru;
				decoding_table[XK_t] = XK_Cyrillic_ie;
				decoding_table[XK_u] = XK_Cyrillic_ghe;
				decoding_table[XK_v] = XK_Cyrillic_em;
				decoding_table[XK_w] = XK_Cyrillic_tse;
				decoding_table[XK_x] = XK_Cyrillic_che;
				decoding_table[XK_y] = XK_Cyrillic_en;
				decoding_table[XK_z] = XK_Cyrillic_ya;
				
				std::map<KeySym,KeySym>::iterator itr;
				for(itr = decoding_table.begin();
					itr != decoding_table.end(); itr++)
					inv_decoding_table[(*itr).second] = (*itr).first;
			}
			break;
			default:
				throw XlibException("Unsupported language");
			break;
		}
	}
	
	KeySym xEncodingTable::getLatinKeysym(KeySym nonlatin_keysym, Lang lang) 
												throw (XlibException)
	{
		KeySym latin_keysym = inv_decoding_tables[lang][nonlatin_keysym];
		if(latin_keysym == None)
			throw XlibException("Unknown keysym");
		return latin_keysym;
	}

	//TODO:	
	char xEncodingTable::getSpecialCharFromKeysym(KeySym keysym) throw (XlibException)
	{
		int iterator;
		char res = '\0';
		KeySym ks[] = { XK_quotedbl, XK_apostrophe, XK_bracketleft, XK_bracketright,
			XK_comma, XK_period, XK_colon, XK_semicolon,
			XK_less, XK_greater, XK_braceleft, XK_braceright,
			XK_space, XK_exclam, XK_at, XK_numbersign,
			XK_ssharp, XK_dollar, XK_percent, XK_degree,
			XK_ampersand, XK_asterisk, XK_parenleft, XK_parenright,
			XK_underscore, XK_equal, XK_plus, XK_minus,
			XK_slash, XK_bar, XK_backslash, XK_question
		};
		char ch[] = { '"', '\'', '{', '}',
			',', '.', ':', ';',
			'<', '>', '[', ']',
			' ', '!', '@', '#',	//TODO
			'#', '$', '%', '^',
			'&', '*', '(', ')',
			'_', '=', '+', '-',
			'/', '|', '\\', '?'
		};
	
		for (iterator = 0; iterator < 32; iterator++)
			if (keysym == ks[iterator]) {
				res = ch[iterator];
				break;
			}
		return res;
	}
	
	//TODO:	
	KeySym xEncodingTable::getKeysymFromSpecialChar(char c) throw (XlibException)
	{
		int iterator;
		KeySym res = None;
		KeySym ks[] = { XK_quotedbl, XK_apostrophe, XK_bracketleft, XK_bracketright,
			XK_comma, XK_period, XK_colon, XK_semicolon,
			XK_less, XK_greater, XK_braceleft, XK_braceright,
			XK_space, XK_exclam, XK_at, XK_numbersign,
			XK_ssharp, XK_dollar, XK_percent, XK_degree,
			XK_ampersand, XK_asterisk, XK_parenleft, XK_parenright,
			XK_underscore, XK_equal, XK_plus, XK_minus,
			XK_slash, XK_bar, XK_backslash, XK_question
		};
		char ch[] = { '"', '\'', '{', '}',
			',', '.', ':', ';',
			'<', '>', '[', ']',
			' ', '!', '@', '#',	//TODO
			'#', '$', '%', '^',
			'&', '*', '(', ')',
			'_', '=', '+', '-',
			'/', '|', '\\', '?'
		};
	
		for (iterator = 0; iterator < 32; iterator++)
			if (c == ch[iterator]) {
				res = ks[iterator];
				break;
			}
		return res;
	}

} //namespace xlib
} //namespace xicor
