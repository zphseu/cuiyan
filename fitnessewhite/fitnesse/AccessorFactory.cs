// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System;
using System.Reflection;

namespace fit
{
	public class AccessorFactory
	{
		public static Accessor Create(Type targetType, string memberName)
		{
			GracefulNameConverter converter = new GracefulNameConverter();
			MemberInfo[] memberInfos = targetType.GetMembers();
			foreach (MemberInfo memberInfo in memberInfos)
			{
				if (memberInfo.Name.ToLower() == converter.GetConvertedName(memberName))
				{
					if (memberInfo is FieldInfo)
					{
						return new FieldAccessor((FieldInfo) memberInfo);
					}
					if (memberInfo is PropertyInfo)
					{
						return new PropertyAccessor((PropertyInfo) memberInfo);
					}
					if (memberInfo is MethodInfo)
					{
						return new MethodAccessor((MethodInfo) memberInfo);
					}
				}
			}
			return null;
		}
	}
}