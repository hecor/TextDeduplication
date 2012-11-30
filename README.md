TextDeduplication
=================

(fuzzy)duplication detection for texts from not too large corpora.

This version only use Lookup3 hash algorithm for detect exact match, fuzzy match just preprocess the text first.

String hash function:  lookup3.c
http://code.google.com/p/gross/source/browse/trunk/src/lookup3.c?spec=svn500&r=499 

const static uint32_t MAX_HASH_SIZE = 0xffffffff;
std::bitset< MAX_HASH_SIZE > hashtable;
So the hashtable only takes about 500M memory.

OnlineFuzzHasher: 
how to fuzz preprocess the texts which will be used to calculate hashvalue
- lowercase;
- tokenize (only continous alphanumber or ‘ would be a token);
- sort the token list;
- discard the tokens of which the length is less than minTokenLength, default as 2.
- trim URL