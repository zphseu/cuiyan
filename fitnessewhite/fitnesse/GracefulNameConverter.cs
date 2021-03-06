// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using System.Collections;
using System.Text;
using System.Text.RegularExpressions;

namespace fit
{
	public class GracefulNameConverter
	{
		public string GetConvertedName(string name)
		{
			string convertedName = name.ToLower();
			convertedName = RemoveTrailingPeriods(convertedName);
			convertedName = ReplaceIllegalCharactersWithSpaces(convertedName);
			convertedName = SeparateNumbersFromWords(convertedName);
			if (convertedName.IndexOf(" ") > -1) {
				IList words = GetListOfSeparatedWords(convertedName);
				convertedName = MergeWords(words);
			}
			return convertedName;
		}

		private static Regex replaceIllegalCharactersWithSpacesRegex = new Regex(@"[^a-zA-Z0-9]");
		internal string ReplaceIllegalCharactersWithSpaces(string name)
		{
			return replaceIllegalCharactersWithSpacesRegex.Replace(name, " ");
		}

		private static Regex wordSplitterRegex = new Regex(" +");
		internal IList GetListOfSeparatedWords(string name)
		{
			string[] wordArray = wordSplitterRegex.Split(name);
			IList words = new ArrayList();
			foreach (string word in wordArray)
			{
				if (!"".Equals(word.Trim()))
				{
					words.Add(word);
				}
			}
			return words;
		}

		private static Regex separateNumbersFromWordsRegex = new Regex("([a-zA-Z][0-9]|[0-9][a-zA-Z])");
		internal string SeparateNumbersFromWords(string name)
		{
			return separateNumbersFromWordsRegex.Replace(name, new MatchEvaluator(SeparateTwoCharactersEvaluator));
		}

		internal string MergeWords(IList words)
		{
			StringBuilder builder = new StringBuilder();
			foreach (string word in words)
			{
				if (IsNumber(word))
				{
					builder.Append(word);
				}
				else
				{
					builder.Append(word.ToLower());
				}
			}
			return builder.ToString();
		}

		internal bool IsNumber(string s)
		{
			foreach (char c in s)
			{
				if (!Char.IsNumber(c))
				{
					return false;
				}
			}
			return true;
		}

		internal string RemoveTrailingPeriods(string name)
		{
			while (name.EndsWith("."))
			{
				name = RemoveLastCharacter(name);
			}
			return name;
		}

		internal string RemoveLastCharacter(string name)
		{
			return name.Remove(name.Length - 1, 1);
		}

		internal string SeparateTwoCharactersEvaluator(Match m) {
			return SeparateTwoCharacters(m.ToString());
		}

		internal string SeparateTwoCharacters(string input) {
			StringBuilder output = new StringBuilder(input.Substring(0, 1));
			output.Append(" ");
			output.Append(input.Substring(1, 1));
			return output.ToString();
		}
	}
}