/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 9:08
 */

using System;
using System.Diagnostics;
using System.Reflection;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using fit;

namespace fitnessewhite
{
    public class Guifixture : Fixture
    {
        protected static Core.UIItems.ListView listView;
        protected static Core.UIItems.TreeItems.Tree tree;
        protected static Core.UIItems.TableItems.Table table;
        protected static Core.Application application;
        protected static Core.UIItems.UIItemContainer uitemcontainer;
        protected static Core.UIItems.WindowItems.Window mainwin;
        protected static Core.UIItems.WindowItems.Window messagebox;

        public static Process Process
        {
            get { return application.Process; }
        }

        protected Parse cells;
        protected static Dictionary<string, Guifixture> actors = new Dictionary<string, Guifixture>();
        protected const string classnamespace = "fitnessewhite";
        protected const string classPrefix = classnamespace + ".T";

        // Utility //////////////////////////////////
        public virtual object doCmd(string classname, string method, string text)
        {
            if (!actors.ContainsKey(classname))
                actors.Add(classname, GetFixture(classname));

            Guifixture actor = actors[classname];
            MethodInfo action = findMethod(actor, method);

            int paramcount = action.GetParameters().Length;
            object ret = null;
            if (paramcount == 0)
            {
                ret = action.Invoke(actor, new Type[] { });
            }
            else if (action.GetParameters().Length == 1)
            {
                Type type = action.GetParameters()[0].ParameterType;
                Object[] args = { new TypeAdapter(type).Parse(text) };
                ret = action.Invoke(actor, args);
            }

            return ret;
        }

        public override void DoCells(Parse cells)
        {
            this.cells = cells;
            try
            {
                object result = doCmd(cells.Text, cells.More.Text, cells.More.More.Text);

                if (result != null && result.GetType() != typeof(void))
                {
                    check(cells.More.More, result);
                }
            }
            catch (Exception e)
            {
                Exception(cells, e);
            }
        }

        // Traversal ////////////////////////////////
        private void check(Parse cell, object result)
        {
            string text = cell.Text;
            TypeAdapter ta = new TypeAdapter(result.GetType());

            if (text == "")
            {
                try
                {

                    Escape(result.ToString());
                }
                catch (Exception)
                {
                    Escape("error");
                }
            }
            else if (result == null)
            {
                Ignore(cell);
            }
            else if (text == "error")
            {
                try
                {
                    Wrong(cell, result.ToString());
                }
                catch (MethodAccessException e)
                {
                    Exception(cell, e);
                }
                catch (Exception)
                {
                    Right(cell);
                }
            }
            else
            {
                try
                {
                    if (TypeAdapter.AreEqual(ta.Parse(text), result))
                    {
                        Right(cell);
                    }
                    else
                    {
                        Wrong(cell, result.ToString());
                    }
                }
                catch (Exception e)
                {
                    Exception(cell, e);
                }
            }
        }

        // /////////////////////////////////////////////////

        protected virtual MethodInfo findMethod(Fixture actor, String test)
        {
            MethodInfo[] methods = actor.GetType().GetMethods();
            MethodInfo result = null;
            for (int i = 0; i < methods.Length; i++)
            {
                MethodInfo m = methods[i];
                if (m.Name.ToLower().Equals(test.ToLower()) && m.GetParameters().Length < 2)
                {
                    if (result == null)
                    {
                        result = m;
                    }
                    else
                    {
                        throw new MissingMethodException("Too many implementations of '" + test + "' in '" + actor.GetType() + "'");
                    }
                }
            }
            if (result == null)
            {
                throw new MissingMethodException("Could not find '" + test + "' in '" + actor.GetType() + "'");
            }
            return result;
        }

        static private ArrayList Assemblies
        {
            get
            {
                ArrayList assemblies = new ArrayList();
                Assembly curAssembly = Assembly.GetExecutingAssembly();
                string spath = curAssembly.Location;
                assemblies.Add(spath);

                spath = spath.Remove(spath.LastIndexOf('\\'));
                try
                {
                    assemblies.AddRange(Directory.GetFiles(spath, classnamespace + ".*.dll"));
                }
                catch (DirectoryNotFoundException)
                {
                    // ignore missing directories
                }

                return assemblies;
            }
        }

        static public Guifixture GetFixture(string className)
        {
            string profixclassName = classPrefix + className;

            foreach (string assemblyName in Assemblies)
            {
                Assembly assembly = Assembly.LoadFrom(assemblyName);
                Guifixture fixture = (Guifixture)assembly.CreateInstance(className);
                if (fixture != null) return fixture;
                fixture = (Guifixture)assembly.CreateInstance(profixclassName);
                if (fixture != null) return fixture;
            }

            throw new ApplicationException("Fixture '" + className + "' could not be found.");
        }

        static public ArrayList GetFixtureNames()
        {
            ArrayList fixtures = new ArrayList();
            foreach (string assemblyName in Assemblies)
            {
                Assembly assembly = Assembly.LoadFrom(assemblyName);
                foreach (Type type in assembly.GetTypes())
                {
                    if ((type.BaseType == typeof(Guifixture) && type.FullName != classnamespace + ".FitUItem`1") ||
                        (type.BaseType.FullName.StartsWith(classnamespace + ".FitUItem`1")))
                    {
                        string classname = type.FullName;
                        if (classname.StartsWith(classPrefix))
                            classname = classname.Remove(0, classPrefix.Length);
                        fixtures.Add(classname);
                    }
                }
            }

            return fixtures;
        }

        static public ArrayList GetMethodNames(string className)
        {
            ArrayList methods = new ArrayList();
            Guifixture fixture = GetFixture(className);
            if (fixture == null) return methods;

            foreach (MethodInfo mi in fixture.GetType().GetMethods())
            {
                if (((mi.GetParameters().Length == 1 && mi.ReturnType == typeof(void)) ||
                    mi.GetParameters().Length == 0) && mi.IsPublic &&
                    (mi.DeclaringType == fixture.GetType() || mi.DeclaringType.FullName.StartsWith(classnamespace + ".FitUItem`1")))
                {
                    methods.Add(mi.Name);
                }
            }

            return methods;
        }

        static public MethodInfo GetMethod(string className, string methodName)
        {
            Guifixture fixture = GetFixture(className);
            return fixture.GetType().GetMethod(methodName);
        }

        static protected string[] SplitString(string value)
        {
            return value.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
        }
    }
}
