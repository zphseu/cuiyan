// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using System.Collections;
using System.Text;
using System.Text.RegularExpressions;

namespace fit
{
	public class TypeName
	{
		private string originalName;
		private string submittedName;
		private string[] parts;

		public TypeName(string name)
		{
			originalName = name;
			if (name != null && isFullyQualifiedRegex.IsMatch(name))
				submittedName = name;
			else
				submittedName = new GracefulNameConverter().GetConvertedName(name);
			parts = submittedName.Split('.');
		}

		public bool IsMatch(Type type, IList namespaces)
		{
			if (NameMatches(type))
			{
				if (IsFullyQualified() && NamespaceMatches(type))
					return true;
				if (NamespaceIsRegistered(type, namespaces))
					return true;
				if (NoNamespace(type))
					return true;
			}
			return false;
		}

		private static bool NamespaceIsRegistered(Type type, IList namespaces)
		{
			return namespaces.Contains(type.Namespace);
		}

		private static bool NoNamespace(Type type)
		{
			return type.Namespace == null;
		}

		private bool NamespaceMatches(Type type)
		{
			return Namespace.Equals(type.Namespace);
		}

		private bool NameMatches(Type type)
		{
			return type.Name.ToLower() == Name.ToLower() || type.Name.ToLower() == (Name + "fixture").ToLower();
		}

		public string Name
		{
			get { return parts[parts.Length - 1]; }
		}

		public string Namespace
		{
			get
			{
				StringBuilder builder = new StringBuilder(parts[0]);
				for (int i = 1; i < parts.Length - 1; i++)
				{
					builder.Append(".");
					builder.Append(parts[i]);
				}
				return builder.ToString();
			}
		}

		private Regex isFullyQualifiedRegex = new Regex(@"^([A-Za-z_][A-Za-z\d_]+\.)+[A-Za-z_][A-Za-z\d_]+$");

		public bool IsFullyQualified()
		{
			return isFullyQualifiedRegex.IsMatch(submittedName);
		}

		public string OriginalName
		{
			get { return originalName; }
		}

		public string ConvertedName
		{
			get { return submittedName; }
		}

		public override int GetHashCode()
		{
			return submittedName != null ? submittedName.GetHashCode() : 0;
		}

		public override bool Equals(object obj)
		{
			if (this == obj) return true;
			TypeName typeName = obj as TypeName;
			if (typeName == null) return false;
			if (!Equals(submittedName, typeName.submittedName)) return false;
			return true;
		}
	}
}