## Project Description
MultiFilez allows you to find and replace text, insert before the start or append to the end of every line, and add text to the start or end of any text-based files. 

## Project Origin
This is an old project.  I mean like really old.  Back in the late 90's, I was owner of a couple thousand templates for web pages.  When I built a new version of the service I was supporting, I realized that I had to change a number of pages with the same edit, over and over again.  As part of that work, I created an app that would find/replace across multiple files and could also add to the beginning/end of a line or page.  This was back in the days before Visual Studio had find in files, before Regular Expressions were included in text editors.

So why release the source now?

Frankly, because it *is* old.  This is a working, compiling, and pretty bug free native Win32 C++/MFC application, which is not going to be something you see everyday on GitHub these days.  Even more unique than that is that this doesn't follow the Doc/View architecture that the MFC platform pushed on everyone.  While a new coder today would want to use a ModelViewViewModelViewModelModle, this is a very basic utility that doesn't benefit from multiple layers of abstraction or needs multiple views over a data document.  This was done on purpose!  This app uses the Win32 message loop, some macros that MFC included. and the MFC CString library (as it was the best of its kind at the time) to get the job done in a standalone application that's under a 50KB.

That said, I did have to convert all of the tabs to spaces and I nearly vomited when I saw the lack of {}'s but at the same time, it compiles, runs, and is a happy little app, so enjoy the trip down memory lane or your first look at a project that didn't have garbage collection, managed runtime, just-in-time interpretation, and often had to be mindful of string length to run under 2MB of RAM.

This project was recompiled using Visual Studio 2019.

## Where can I get the compiled version?
Click the Releases button in the header above or go to https://github.com/randyrants/multifilez/releases directly

## How do I use it?
* Run the installer
* Open the app
* Build a list of files you want to edit
* Make a backup of these files, if you are editing them since there is no UNDO option here!
* Set some criteria
* Run the tool

## Hope for GitHub contributions:
* Education mostly, but I'm happy to grab a PR that has any bug fixes

## Not looking for, from GitHub contributions:
* A complete re-write in .NET or UWP; that's something I may do in the not too distant future but it will be in a different codebase rather than incrumenting this one.
