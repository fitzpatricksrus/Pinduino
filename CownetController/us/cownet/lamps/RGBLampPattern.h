/*
 * RGBLampPattern.h
 *
 *  Created on: Nov 18, 2015
 *      Author: jfitzpatrick
 */

#ifndef RGBLAMPPATTERN_H_
#define RGBLAMPPATTERN_H_

namespace us_cownet_lamps {

class RGBLampPattern {
public:
	class RGB {
	public:
		RGB(byte r, byte g, byte b)
		: R(r), G(g), B(b)
		{
		}

		byte R, G, B;
	};

	RGBLampPattern();
	virtual ~RGBLampPattern();

	virtual int getLampCount() = 0;

	virtual RGB getLamp(int index) = 0;

	virtual void attached();

	virtual void endOfMatrixSync();

	/*
	 Used only by pattern containers.  isDone() should return true when the
	 pattern has displayed its entire state sequence once.  This has no affect
	 on the lamp matrix, which will continue to cycle through columns.  Containers
	 can decide how to proceed and may reset() the pattern, replace it, or
	 continue to refresh the matrix with it.
	 */
	virtual bool isDone();

	/*
	 Start the refresh sequence from the beginning.
	 */
	virtual void reset();

	virtual void detached();

//	template <int size>
//	void setBuffer(int (&newBuffer)[size]);
};

} /* namespace us_cownet_lamps */

#endif /* RGBLAMPPATTERN_H_ */
