// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.Reflection;

namespace fit {
    public class ColumnFixture : Fixture {
        protected internal TypeAdapter[] columnBindings;
        protected bool hasExecuted = false;

        // Traversal ////////////////////////////////

        public override void doRows(Parse rows) {
            bind(rows.parts);
            base.doRows(rows.more);
        }

        public override void doRow(Parse row) {
            hasExecuted = false;
            try {
                reset();
                base.doRow(row);
                if (!hasExecuted) {
                    execute();
                }
            } 
            catch (Exception e) {
                exception(row.leaf(), e);
            }
        }

        public override void doCell(Parse cell, int column) {
            TypeAdapter a = columnBindings[column];
            try {
                string text = cell.text();
                if (text == "") {
                    check(cell, a);
                }
                else if (a == null) {
                    ignore(cell);
                } 
                else if (a.field != null) {
                        a.set(a.parse(text));
                } 
                else if (a.method != null) {
                    check(cell, a);
                }
            } 
            catch(Exception e) {
                exception(cell, e);
            }
        }

        public override void check(Parse cell, TypeAdapter a) {
            if (!hasExecuted) {
                try {
                    execute();
                } 
                catch (Exception e) {
                    exception (cell, e);
                }
                hasExecuted = true;
            }
            base.check(cell, a);
        }

        public virtual void reset() {
            // about to process first cell of row
        }

        public virtual void execute() {
            // about to process first method call of row
        }


        // Utility //////////////////////////////////

        protected virtual void bind (Parse heads) {
            columnBindings = new TypeAdapter[heads.size()];
            for (int i=0; heads!=null; i++, heads=heads.more) {
                String name = heads.text();
                String suffix = "()";
                try {
                    if (name == "") {
                        columnBindings[i] = null;
                    }
                    else if (name.EndsWith(suffix)) {
                        columnBindings[i] = bindMethod(name.Substring(0,name.Length-suffix.Length));
                    } 
                    else {
                        columnBindings[i] = bindField(name);
                    }
                }
                catch (Exception e) {
                    exception (heads, e);
                }
            }

        }

        protected virtual TypeAdapter bindMethod (string name) {
			String camelName = camel(name);
            MethodInfo method = getTargetClass().GetMethod(camelName, new Type[] {});
            if (method == null) throw new MissingMethodException(getTargetClass().FullName, camelName);
            return TypeAdapter.on(this, method);
        }

        protected virtual TypeAdapter bindField (string name) {
			String camelName = camel(name);
			FieldInfo field = getTargetClass().GetField(camelName);
			if (field == null) throw new MissingFieldException(getTargetClass().FullName, camelName);
            return TypeAdapter.on(this, field);
        }

        public virtual Type getTargetClass() {
            return GetType();
        }
    }
}
