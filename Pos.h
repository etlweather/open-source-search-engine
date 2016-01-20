// Matt Wells, copyright Jul 2005

#ifndef _POS_H_
#define _POS_H_

#include <stdint.h>

// this class is used to measure the number of characters between two "words"
// (as defined in the Words.cpp class) in units of "characters". A utf8
// character can be 1, 2, 3 or 4 bytes, so be careful.

#define POS_LOCALBUFSIZE 20

class Words;

class Pos {

 public:

	Pos();
	~Pos();
	void reset();

	bool set(Words *words, int32_t a = 0, int32_t b = -1 );

	// . filter out xml words [a,b] into plain text, stores into "f"
	// . will not exceed "fend"
	// . returns number of BYTES stored into "f"
	int32_t filter(Words *words, int32_t a, int32_t b, bool addEllipsis, char *f, char *fend);

	// . the position in CHARACTERS of word i is given by m_pos[i]
	// . this is NOT the byte position. you can have 2, 3 or even 4
	//   byte characters in utf8. the purpose here is for counting 
	//   "letters" or "characters" for formatting purposes.
	int32_t *m_pos;

private:
	char  m_localBuf [ POS_LOCALBUFSIZE ];
	char *m_buf;
	int32_t  m_bufSize;

	bool  m_needsFree;
};

#endif
