// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using System.Text.RegularExpressions;
using fit;

namespace fitnesse.handlers
{
	public class SubstringHandler : AbstractCellHandler
	{
		private static Regex matchExpression = new Regex("^\\.\\..*\\.\\.$");
		public override bool Match(string searchString, Type type)
		{
			return matchExpression.IsMatch(searchString);
		}

		public override bool HandleEvaluate(Fixture fixture, Parse cell, Accessor accessor)
		{
			if (GetActual(accessor, fixture) == null)
			{
				return false;
			}
			return GetActual(accessor, fixture).ToString().IndexOf(ExtractExpectedSubstring(cell)) > -1;
		}

		private static string ExtractExpectedSubstring(Parse cell)
		{
			return cell.Text.Substring(2, cell.Text.Length - 4);
		}
	}
}