ObTestFile is a console application that is used to check the operation of the mod file
code. Format is:

    obtestfile [inputfile] [outputfile] [/o] [/m]

    [inputfile]   - The ESP/ESM file to load.
    [outputfile]  - The file to save as. If this is omitted the output file will
 	            be the input filename with a '.tmp' appended.
    [/o]	  - Forces the output file to be overwritten if it exists.
    [/m]	  - Attempts to find Oblivion's install path in the Windows 
		    registry and use Oblivion.esm as the input file. 

When run, ObTestFile will attempt to load the given input file and save it to the new
output file. On success it will then compare the input and output files, reporting any
mismatch. Ideally the input and output files should be identical.

WARNING: Testing Oblivion.esm wil require ~800 MB of memory and take at least a minute
to occur. On slower computers, especially those with less than 1GB of RAM, the test will
take *much* longer.

Examples:
	
    obtestfile myplugin.esp temp.esp
	Loads myplugin.esp and saves to temp.esp. If temp.esp exists the test
	will be aborted.

    obtestfile myplugin.esp
	Loads myplugin.esp and saves to myplugin.esp.tmp, aborting if the 
	output file already exists.

    obtestfile myplugin.esp /o
	Loads myplugin.esp and saves to myplugin.esp.tmp, overwriting the output
 	file if it exists.

    obtestfile /m /o
	Attempts to load Oblivion.esm from the current installation path and save
	it to Oblivion.esm.tmp in the same path.

	

	
