/*
 * Base.h
 *
 *  Created on: 28.10.2014
 *      Author: jakob
 */

#ifndef BASE_H_
#define BASE_H_

class Base {
protected:
	Base* pointer1; // Successor in chained list
	Base* pointer2; // Pointer to other type
public:
	Base(Base* pointer1, Base* pointer2);
	virtual ~Base();
};

#endif /* BASE_H_ */
