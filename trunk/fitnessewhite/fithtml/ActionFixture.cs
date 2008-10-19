// Copyright (c) 2002, 2003 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.Reflection;

namespace fit {

    public class ActionFixture : Fixture {
        protected Parse cells;
        public static Fixture actor;

        // Traversal ////////////////////////////////

        public override void DoCells(Parse cells) {
            this.cells = cells;
            try {
                MethodInfo action = GetType().GetMethod(cells.text(), new Type[] {});
                action.Invoke(this, new Type[] {});
            } 
            catch (Exception e) {
                exception(cells, e);
            }
        }

        // Actions //////////////////////////////////

        public virtual void start() {
            actor = loadFixture(cells.more.text());
        }

        public virtual void enter() {
            MethodInfo method = findMethod(1);
            Type type = method.GetParameters()[0].ParameterType;
            String text = cells.more.more.text();
            Object[] args = {TypeAdapter.on(actor, type).parse(text)};
            method.Invoke(actor, args);
        }

        public virtual void press() {
            findMethod(0).Invoke(actor, new Type[] {});
        }

        public virtual void check() {
            TypeAdapter adapter = TypeAdapter.on(actor, findMethod(0));
            check (cells.more.more, adapter);
        }

        // Utility //////////////////////////////////

        protected virtual MethodInfo findMethod(int args) {
            return findMethod(camel(cells.more.text()), args);
        }

        protected virtual MethodInfo findMethod(String test, int args) {
            MethodInfo[] methods = actor.GetType().GetMethods();
            MethodInfo result = null;
            for (int i=0; i<methods.Length; i++) {
                MethodInfo m = methods[i];
                if (m.Name.ToLower().Equals(test.ToLower()) && m.GetParameters().Length == args) {
                    if (result==null) {
                        result = m;
                    } else {
                        throw new MissingMethodException("Too many implementations of '" + test + "' in '" + actor.GetType() + "'");
                    }
                }
            }
            if (result==null) {
                throw new MissingMethodException("Could not find '" + test + "' in '" + actor.GetType() + "'");
            }
            return result;
        }
    }
}