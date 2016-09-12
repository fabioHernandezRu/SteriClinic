/*
 * Fuzzy.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */


// http://www.chebucto.ns.ca/Science/AIMET/archive/ddj/fuzzy_logic_in_C/
// http://www.thegeekstuff.com/2014/09/fuzzy-logic-cpp/
// http://ffll.sourceforge.net/downloads.htm
//https://github.com/MichaelMure/FmkProject

#ifndef FUZZY_H_
#define FUZZY_H_


class Fuzzy {
public:
	Fuzzy();
	void testOp();
	void testTriangle();
	void testMamdani();
	void testSugeno();

	virtual ~Fuzzy();
};

#endif /* FUZZY_H_ */
