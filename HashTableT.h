// . generic hash table class

#ifndef GB_HASHTABLET_H
#define GB_HASHTABLET_H

#include <inttypes.h>
#include <stddef.h>


template<class Key_t, class Val_t>
class HashTableT {

 public:

	bool set ( int32_t initialNumSlots = 0     , 
		   char *buf		= NULL  ,
		   int32_t bufSize		= 0     ,
		   bool allowDupKeys    = false );

	 HashTableT( ) ;
	~HashTableT( );

	// . add key/value entry to hash table
	// . will grow hash table if it needs to
	bool addKey ( Key_t key , Val_t value , int32_t *slot = NULL );

	// remove key/value entry to hash table
	bool removeKey ( Key_t key );

	// . used by ../english/Bits.h to store stop words, abbr's, ...
	// . returns the score for this termId (0 means empty usually)
	Val_t* getValuePointer ( Key_t key ) const;

	Val_t* getValuePtr ( Key_t key ) { return getValuePointer ( key ); }

	// value of 0 means empty
	//bool isEmpty ( Key_t key ) { return (getValue(key) == 0); }

	Key_t getKey ( int32_t n ) const { return m_keys[n]; }

	int32_t getSlot ( Key_t key ) const { return getOccupiedSlotNum ( key ); }
	// for hash tables that m_allowDupKeys
	int32_t getNextSlot ( Key_t& key , int32_t n ) const ;

	void setValue ( int32_t n , Val_t val ) { m_vals[n] = val; }

	bool isEmpty ( int32_t n ) { return ( m_keys[n] == 0 ); }

	Val_t getValueFromSlot ( int32_t n ) const { return m_vals[n]; }

	Val_t* getValuePointerFromSlot ( int32_t n ) { return &m_vals[n]; }

	// frees the used memory, etc.
	void  reset  ( );

	// removes all key/value pairs from hash table, vacates all slots
	void  clear  ( );

	// how many are occupied?
	int32_t getNumUsedSlots() const { return m_numSlotsUsed; }

	// how many are there total? used and unused.
	int32_t getNumSlots ( ) const { return m_numSlots; }

	void setAllowDupKeys(bool allow) { m_allowDupKeys = allow; }
	bool getAllowDupKeys( ) const { return m_allowDupKeys; }

	bool setTableSize ( int32_t numSlots, char *buf, int32_t bufSize );

	int32_t getOccupiedSlotNum ( const Key_t& key ) const;

	//private:
	//friend class RequestTable;
	// . the array of buckets in which we store the terms
	// . scores are allowed to exceed 8 bits for weighting purposes
	Key_t  *m_keys;
	Val_t  *m_vals;

	int32_t m_numSlots;
	int32_t m_numSlotsUsed;

	bool m_allowDupKeys;

	bool m_doFree;

	char *m_buf; //. hash table buffer points to callers buffer on stack
	int32_t m_bufSize;
};

#endif // GB_HASHTABLET_H
