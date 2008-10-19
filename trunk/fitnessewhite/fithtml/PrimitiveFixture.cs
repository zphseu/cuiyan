// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

namespace fit
{
	public class PrimitiveFixture : Fixture
	{

		// format converters ////////////////////////

		public static long parseLong (Parse cell) 
		{
			return long.Parse(cell.text());
		}

		public static double parseDouble (Parse cell) 
		{
			return double.Parse(cell.text());
		}

		// answer comparisons ///////////////////////

		public virtual void check (Parse cell, string actual) 
		{
			if (cell.text() == actual) 
			{
				right(cell);
			} 
			else 
			{
				wrong(cell, actual);
			}
		}

		public virtual void check (Parse cell, long actual) 
		{
			if (parseLong(cell) == actual) 
			{
				right(cell);
			} 
			else 
			{
				wrong(cell, actual.ToString());
			}
		}

		public virtual void check (Parse cell, double actual) 
		{
			if (parseDouble(cell) == actual) 
			{
				right(cell);
			} 
			else 
			{
				wrong(cell, actual.ToString());
			}
		}

	}
}