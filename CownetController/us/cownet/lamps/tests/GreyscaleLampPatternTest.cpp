/*
 * GreyscaleLampPatternTest.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: jfitzpatrick
 */

#include "GreyscaleLampPatternTest.h"

namespace us_cownet_lamps_tests {

GreyscaleLampPatternTest::GreyscaleLampPatternTest(LampMatrix* greyMatrixIn)
: greyMatrix(greyMatrixIn)
{
}

GreyscaleLampPatternTest::~GreyscaleLampPatternTest() {
}


static int patternValues[] = {
		0, 1, 3, 7, 15, 31, 63, 127,
		0, 5, 10, 15, 20, 25, 30, 35,
		40, 45, 50, 55, 60, 65, 70, 75,
		80, 85, 90, 95, 100, 105, 110, 115,
		120, 125, 130, 135, 140, 145, 150, 155,
		160, 165, 170, 175, 180, 185, 190, 195,
		200, 205, 210, 215, 220, 225, 230, 235,
		240, 245, 250, 251, 252, 253, 254, 255
	};

void GreyscaleLampPatternTest::setup() {
	int pos = 0;
	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 8; row++) {
			patternValues[col][row] = 4 * pos++;
		}
	}

//		GreyscaleLampPattern pattern = new GreyscaleLampPattern(patternValues);
//		AbstractGreyscaleLampPattern pattern = new Pattern(patternValues);
	AbstractGreyscaleLampPattern pattern = new Pattern2();
	greyLampMatrix.setPattern(pattern);
}

	@Override
	public void loop() {
		TimerUtil.INSTANCE.tick();
	}

	// simple greyscale from lamp 0 - 63
	public static class Pattern extends AbstractGreyscaleLampPattern {
		private int greyPattern[][];

		public Pattern(int[][] greyPattern) {
			this(greyPattern, 8);
		}

		public Pattern(int[][] greyPattern, int grayscaleBits) {
			this(greyPattern, grayscaleBits, 0);
		}

		public Pattern(int[][] greyPattern, int grayscaleBits, int startPosition) {
			this.greyPattern = greyPattern;
			setPattern(grayscaleBits, startPosition);
		}

		@Override
		public int getColCount() {
			return greyPattern[0].length;
		}

		@Override
		protected int getLampValue(int col, int row) {
			return greyPattern[col][row];
		}
	}

	// pulsing lamp pattern
	public static class Pattern2 extends AbstractGreyscaleLampPattern {
		private int position = 0;

		public Pattern2() {
			this(8);
		}

		public Pattern2(int grayscaleBits) {
			this(grayscaleBits, 0);
		}

		public Pattern2(int grayscaleBits, int startPosition) {
			setPattern(grayscaleBits, startPosition);
		}

		@Override
		public int getColCount() {
			return 8;
		}

		@Override
		protected int getLampValue(int col, int row) {
			int ndx = col * 8 + row;	// 0 - 63
			int adj = Math.abs(((position + ndx) % 128) - 64);	// -64..64
//			if (ndx == 0) {
//				System.out.println(Math.min(adj * 4, 255));
//			}
			return Math.min(adj * 4, 255);
		}

		@Override
		protected void greyscaleEndOfSync() {
			position = (position + 1) % 128;
		}
	}

	public static void main(String args[]) {
		new GreyscaleLampPatternTest(LampMatrixTest.createTestMatrix()).execute();
	}

} /* namespace us_cownet_lamps_tests */

