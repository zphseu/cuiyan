// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.IO;
using System.Text;

namespace fit {
    public class FileRunner {
		//cycy private const int WINDOWS_STANDARD_ENCODING = 1252;

        public string input;
        public Parse tables;
        public Fixture fixture = new Fixture();
        public TextWriter output;

        public virtual void run (String[] argv) {
            args(argv);
            process();
            exit();
        }

        public virtual void process() {
            try {
                tables = new Parse(input);
                fixture.doTables(tables);
            } 
            catch (Exception e) {
                exception(e);
            }
            tables.print(output);
        }

        public virtual void args(String[] argv) {
            if (argv.Length != 2 && argv.Length != 3) {
                Console.Error.WriteLine("usage: runFile input-file output-file [fixture-dir]");
                Console.Error.WriteLine("fixture-dir: The directory containing your fixture DLL.  You can specify");
                Console.Error.WriteLine("  multiple directories by separating them with semicolons.  If you leave this");
                Console.Error.WriteLine("  out, runFile will look in a number of default locations.");
                Console.Error.WriteLine("Example: runFile doc\\arithmetic.html report\\arithmetic.html bin");
                Console.Error.WriteLine("Default fixture-dir:");
                Console.Error.WriteLine("  " + fixturePath);
                Environment.Exit(-1);
            }
            string inFile = argv[0];
            string outFile = argv[1];
            if (argv.Length > 2) {
                string fixtureDir = argv[2];
                if (fixtureDir.ToLower().IndexOf(".dll") >= 0) {
                    Console.Error.WriteLine("Warning: fixture-dir parameter should only contain directories");
                }
                Fixture.assemblyDirs = argv[2].Split(';');
            }
            fixture.summary["input file"] = inFile;
            fixture.summary["input update"] = File.GetLastWriteTime(inFile);
            fixture.summary["output file"] = outFile;
            fixture.summary["fixture path"] = fixturePath;
            try {
                input = read(inFile);
                //cycy output = new StreamWriter(outFile, false, Encoding.GetEncoding(WINDOWS_STANDARD_ENCODING));
                output = new StreamWriter(outFile, false, Encoding.Unicode);
                
            } 
            catch (IOException e) {
                Console.Error.WriteLine(e.Message);
                Environment.Exit(-1);
            }
        }

        private string fixturePath {
            get {
                return string.Join(";", Fixture.assemblyDirs);
            }
        }

        protected virtual string read(string input) {
            //cycy StreamReader reader = new StreamReader(input, Encoding.GetEncoding(WINDOWS_STANDARD_ENCODING));
            StreamReader reader = new StreamReader(input, Encoding.Unicode);
            
            try {
                return reader.ReadToEnd();
            }
            finally {
                reader.Close();
            }
        }

        protected virtual void exception(Exception e) {
            tables = new Parse("body","Unable to parse input. Input ignored.", null, null);
            fixture.exception(tables, e);
        }

        protected virtual void exit() {
            output.Close();
            Console.Error.WriteLine(fixture.counts.ToString());
            Environment.Exit(fixture.counts.wrong + fixture.counts.exceptions);
        }
    }
}
