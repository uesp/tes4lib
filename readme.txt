
       Name: tes4lib
    Version: 0.2-Alpha
       Date: 28 April 2006
    Contact: Dave Humphrey, uesp@sympatico.ca (www.uesp.net)
    Website: http://tes4lib.sf.net/


== Overview ==
tes4lib is a library of code which can be used to manipulate various file 
formats used in the game of The Elder Scrolls:Oblivion. Its intended target
is C/C++ developers who wish to load, edit, and save these formats without
having to create the necessary file handlers from scratch.


== Features ==
This is the initial release of the library so only the more basic loading
of mod files (ESM/ESP) have been added. More advanced mod file handling and
additional formats will be added as time permits and demand ditates.

   - Load ESM and ESP mod files
   - Can successfully load and save Oblivion.esm with 100% accuracy
   - Manipulate some types of records (Ammo, Apparatus, Armor, Books,
     Clothing, Enchantments, Ingrediants, Leveled Item Lists, Misc, 
     Scripts, Spells, and Weapons). Other records can be manipulated
     as raw data if required. 
   - Written with high performance in mind. Currently loads Oblivion.esm
     twice as fast the Construction Set (13 secs vs 22 secs on my computer)
     although any required record indexing will increase the loading time.
     Typical mods load very fast (1.5 MB mod loads in 0.1 secs and saves in
     0.3 secs).


== Installation ==
Just unzip into a directory of your choice. You will need to copy zlib1.dll
in the "common/zlib" directory into your Windows "system" path or in each path
of any executable using the library.


== Requirements ==

   Compiler
      - Has been compiled with Visual C++ v6.0 and gcc (under CygWin)
      - Additional compilers can likely be supported as needed

   Operating System
      - Windows
      - Other OSs can potentially be supported as Windows specific code is
        currently very limited and mostly optional.

   Minimum Specifications
      - 1GB RAM if you intend to try loading Oblivion.esm in any decent time
      - Memory usage for other files can be estimated by taking the file size
        and multiplying by 3 (ex: a 1 MB ESP would take 3 MB of memory).


== Content ==
The following is a brief description of the contents of the library by root
directories:

   common
      Base level common code and definitions.
   modfile
      Code for manipulating ESP and ESM files.
   buildtest
      A test VC6 project used for developing purposes.
   oblibtest
      A VC6 project with test units for all code in the library. 
   obtestfile
      A VC6 console application used for loading a specified file, saving
      it and comparing the original and new files ensuring they are exact.


== Using ==
Currently the library is provided as is and assumes you have some coding
experience in C++. Look at the several example projects for an idea of how
to define and use the library features.

Support and feature requests can be directed to Dave at uesp@sympatico.ca.
 

== Versions ==

0.1-Alpha, 19 April 2006
	- Initial Release

0.2-Alpha, 28 April 2006
	- Fixed mispelling of LVLI records/subrecords which prevented them
          from being processed.
	- Added many string tables and accessor functions to convert a string
          to a basic type value and vice-versa.
	- Assorted bug fixes and minor improvements.

