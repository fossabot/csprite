# Changelog
All notable changes to this project will be documented in this file.

The project follows [Semantic Versioning v2.0.0](https://semver.org/spec/v2.0.0.html), all the changes are added every new release.

- **v1.0.0 (coming soon)**
	- Switched From OpenGL To SDL2
		- Now CSprite Supports OpenGL, Direct3D, Metal, Vulkan & Software Based Rendering.

	- New Tool Line Tool (<kbd>L</kbd> or <kbd>Shift</kbd> + <kbd>L</kbd>)
	- New Tool Rectangle Tool (<kbd>R</kbd> or <kbd>Shift</kbd> + <kbd>R</kbd>)
	- New Tool Circle Tool (<kbd>C</kbd>)
	- New Configuration System
		- You Can Edit CSprite's Configuration By Going into Edit -> Preferences

	- New Palette System
		- CSprite Provides 3 Palettes By Default.
		- Palettes Can Be Changed Via Edit -> Palette
		- New Palettes Can Be Added By Going into Palette Directory Inside CSprite's Config Directory

	- New Custom Cursors
		- CSprite Provides New Custom Cursor Icons Which are enabled by default
		- If you are having performance problems you can disable that in Edit -> Preferences

- **[v0.1.0](https://github.com/pegvin/csprite/releases/tag/v0.1.0)**
	- Re-Format The Code
		- Define Include Directories
		- Remove The Absolute Path in Include Headers

	- Add Window Icon & Executable Icon (For Windows)
		- Add 32 & 48 Resolution Icons
		- Convert PNG Icons To Header Files 16, 32 & 48
		- Add 256 Resolution .ico For Windows
		- Add Executable Version & Icon RC For Windows
		- Add Batch Script For Converting RC To Object File

	- Add Stripping Step in Workflow To Remove Debug Information
	- Create My Own "Original" Icon

## Unreleased

- May 25, 2022
	- Rename Function Names To Pascal Case

- May 23, 2022
	- Add 2 New Templates For Issues (Bug, Feature Request)

- May 22, 2022
	- Reduce Build Size.
	- Fix Shader Loading From a File in debug mode.
	- Update Username

- May 20-21, 2022
	- Add Undo/Redo Functionality [#6](https://github.com/pegvin/CSprite/pull/6).
	- Add Undo/Redo Option in Menu [#6](https://github.com/pegvin/CSprite/pull/6).
	- Lazy Memory Allocation For Undo/Redo [#6](https://github.com/pegvin/CSprite/pull/6).
	- Separate Code into Clamp Function [#6](https://github.com/pegvin/CSprite/pull/6)
	- Clamp Redo To Max Available History [#6](https://github.com/pegvin/CSprite/pull/6).
	- Call `ResetHistory();` To Reset Undo/Redo Array When Opening a new Image/Creating a new canvas.
	- Add Include/Header Guards in `.h` files.
	- Add Customize-able Options When Building ([How To Use](https://github.com/pegvin/CSprite/wiki/Building-From-Source#customizing)).

- May 18, 2022
	- Reduce Compiler Warnings.

- May 10, 2022
	- Fix filepath issue in save as in menu.

- May 9, 2022
	- Remove The Temporary Code.
	- Fix Selection Of Transparent Part Of Canvas Using Ink Dropper Tool.
	- Splitted The Code.
	- Add JPG, BMP & TGA Export Formats (PNG Was Already there).
	- Remove BMP & TGA Export Formats.

- May 8, 2022
	- Optimize Code.

- May 7, 2022
	- Fix Gaps When Drawing With Fast Moving Mouse.

- May 6, 2022
	- Change Global Variable Naming Style.
	- Fix mouse click not working when clicking on a color on the color palette.
	- Add Help Menu.
	- Change Variable Naming Convention.

- May 5, 2022
	- Add [Montserrat Bold](https://fonts.google.com/specimen/Montserrat) Font For UI.
	- Add Canvas Zoom to auto adjust when creating a canvas or opening a image to fit the screen.
	- Change Circle brush to be the default brush.
	- Fix Color not being selected from palette using mouse click.

- May 4, 2022

	- Add Ink Dropper Tool.
	- Add Menu Bar & New Button To Create A new empty canvas [#4](https://github.com/pegvin/CSprite/pull/4).
	- Add New, Open, Save & Save As in Menu Bar [#4](https://github.com/pegvin/CSprite/pull/4).
	- Fix Memory Leaks.
	- Remove Zoom Limit (Max Zoom Limit Now is `4294967295`).

- May 3, 2022
	- Add Simple Menu.
	- Add `New`, `Open`, `Save` & `Save As` in Menu.
	- Fix Memory Leaks.

- May 2, 2022
	- Remove UPX Compression From Linux Binary.
	- Add Comments.
	- Fix Flags.
	- A Little Refactoring.
	- Add Conditional Code For Debug & Release.
	- Made The Code More Readable By Comments And Variable Names.
	- Add Conditional Code For Windows Only.
	- Remove Unused Headers.

- May 1, 2022
	- Fix high CPU & GPU Usage.
	- Add Error Callback Function To Log GLFW Errors With Clear Description.
	- Fix Console Popping Up When Launching CSprite On Windows.

- April 30, 2022
	- Add Building For Windows.
	- Update Open/Save File Dialogs.
		- Remove [ImGui File Dialogs](https://github.com/aiekick/ImGuiFileDialog) Because Of Compiling Errors on Windows.
		- Add [Tiny File Dialogs](https://sourceforge.net/projects/tinyfiledialogs/) Because Of Being Native And Less Code Required To Implement.
	- Add GLFW Compiled Library ( glfw3_mt.lib ) To Link With On Windows.
	- Fix Random Pixels On Blank Canvas Because Of The Memory allocated not being empty.
	- Tweak Makefile For Conditional Flags depending on Platform.
