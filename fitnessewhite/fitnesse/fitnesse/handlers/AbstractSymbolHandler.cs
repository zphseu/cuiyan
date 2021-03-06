// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using fit;

namespace fitnesse.handlers
{
	public abstract class AbstractSymbolHandler : AbstractCellHandler
	{
		public override void HandleInput(Fixture fixture, Parse cell, Accessor accessor)
		{
			accessor.Set(fixture, Fixture.Recall(ExtractSymbol(cell)));
		}

		public override bool HandleEvaluate(Fixture fixture, Parse cell, Accessor accessor) {
			object value = Fixture.Recall(ExtractSymbol(cell));
			if (value == null)
				return false;
			return TypeAdapter.AreEqual(accessor.Get(fixture), value);
		}

		protected string ExtractSymbol(Parse cell)
		{
			return cell.Text.Substring(2);
		}
	}
}