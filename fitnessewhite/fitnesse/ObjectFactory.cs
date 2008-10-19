// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using System.Collections;
using System.IO;
using System.Reflection;
using System.Text;

namespace fit
{
	public class ObjectFactory
	{
		private static IList assemblyList = new ArrayList();
		private static IList loadedAssemblies = new ArrayList();
		private static IList namespaces = new ArrayList();

		public static IList AssemblyList
		{
			get { return assemblyList; }
		}

		public static IList LoadedAssemblies
		{
			get { return loadedAssemblies; }
		}

		public static IList Namespaces
		{
			get { return namespaces; }
			set { namespaces = value; }
		}

		public static void AddAssembly(string assemblyPath)
		{
			if (assemblyPath != null && !assemblyList.Contains(assemblyPath))
			{
				try
				{
					Assembly assembly = Assembly.LoadFrom(assemblyPath);
					loadedAssemblies.Add(assembly);
					assemblyList.Add(assemblyPath);
					FileInfo fileInfo = new FileInfo(assemblyPath);
					DirectoryInfo directoryInfo = fileInfo.Directory;
					foreach (FileInfo configFileInfo in directoryInfo.GetFiles("*.config"))
					{
						AppDomain.CurrentDomain.SetData("APP_CONFIG_FILE", configFileInfo);
					}
				}
					//TODO - explain why we need to catch exceptions but don't
					//need to do anything with them
				catch (Exception)
				{
				}
			}
		}

		public static void AddNamespace(string name)
		{
			namespaces.Add(name);
		}

		public static void ClearNamespaces()
		{
			namespaces.Clear();
		}

		public object CreateInstance(string submittedName)
		{
			TypeName typeName = new TypeName(submittedName);
			if (typeName.IsFullyQualified())
			{
				Type type = Type.GetType(typeName.OriginalName);
				if (type != null)
					return GetInstance(typeName, type);
			}
			foreach (Assembly assembly in loadedAssemblies)
			{
				foreach (Type type in assembly.GetExportedTypes())
					if (typeName.IsMatch(type, namespaces))
						return GetInstance(typeName, type);
			}
			return GetInstance(typeName, null);
		}

		private object GetInstance(TypeName typeName, Type type)
		{
			try
			{
				return type.Assembly.CreateInstance(type.FullName);
			}
			catch (NullReferenceException)
			{
				throw new ApplicationException(GetCouldNotFindTypeMessage(typeName.ConvertedName));
			}
		}

		private string GetCouldNotFindTypeMessage(string submittedName)
		{
			StringBuilder builder = new StringBuilder();
			builder.Append("Type '");
			builder.Append(submittedName);
			builder.Append("' could not be found in assemblies.\n");
			builder.Append("Assemblies searched:");
			foreach (Assembly assembly in loadedAssemblies)
			{
				builder.Append("    ");
				builder.Append(assembly.CodeBase);
				builder.Append("\n");
			}
			return builder.ToString();
		}
	}
}