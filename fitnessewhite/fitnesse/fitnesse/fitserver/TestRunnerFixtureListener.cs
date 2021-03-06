// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using fit;

namespace fitnesse.fitserver
{
	public class TestRunnerFixtureListener : FixtureListener
	{
		public Counts counts = new Counts();
		private bool atStartOfResult = true;
		private PageResult currentPageResult;
		private TestRunner runner;

		public TestRunnerFixtureListener(TestRunner runner)
		{
			this.runner = runner;
		}

		public void TableFinished(Parse table)
		{
			String data = FitServer.FirstTableOf(table);
			if(atStartOfResult)
			{
				int indexOfFirstLineBreak = data.IndexOf("\n");
				String pageTitle = data.Substring(0, indexOfFirstLineBreak);
				data = data.Substring(indexOfFirstLineBreak + 1);
				currentPageResult = new PageResult(pageTitle);
				atStartOfResult = false;
			}
			currentPageResult.Append(data);
		}

		public void TablesFinished(Counts count)
		{
			currentPageResult.setCounts(count);
			runner.AcceptResults(currentPageResult);
			atStartOfResult = true;
			counts.Tally(count);
		}
	}
}
