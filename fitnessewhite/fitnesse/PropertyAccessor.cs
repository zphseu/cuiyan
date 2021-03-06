// Modified or written by Object Mentor, Inc. for inclusion with FitNesse.
// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.
using System.Reflection;

namespace fit
{
	public class PropertyAccessor : AbstractAccessor
	{
		private PropertyInfo property;

		public PropertyAccessor(PropertyInfo property) : base(property.PropertyType)
		{
			this.property = property;
		}

		public override object Get(Fixture fixture)
		{
			return property.GetValue(fixture.GetTargetObject(), null);
		}

		public override void Set(Fixture fixture, object value)
		{
			property.SetValue(fixture.GetTargetObject(), EnsureCorrectType(property.GetType(), value), null);
		}
	}
}