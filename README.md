# File-Mover
<div>
<img src="https://img.shields.io/badge/C%2B%2B17-blue?logo=cplusplus"/>
<img src="https://img.shields.io/badge/Qt_6-darkgreen?logo=qt"/>
</div>
A program for monitoring and cleaning the file system.

## What can the program do?
The program allows you to manage files using a set of simple rules. The rules are configured separately for each folder. There is regex support, and it is also possible to work in the tray.

## How program works?
Using the graphical application, you specify the folders in which the files will be monitored. When the program detects changes in one of the specified folders, the sorter is started, which sequentially goes through all the rules for this folder to move and delete. To work properly, run the program as an administrator.

## Instruction
When you open the app, you are greeted by the folder management screen. The control panel for configs and the program is marked in red. The editor is highlighted in blue.

The program is navigated by switching the tabbar.
You can add rules tab by double-clicking on the folder.

### The sidebar:
- The program control button. Starts sorting and monitoring. The program will not start if there are no rules;
- Exporting the existing configuration from JSON;
- Saving the configuration in JSON;
- Creating a new configuration. When clicked, the program will prompt you to save the available data;
- Settings. In development.

### Editor Panel - Folders:
Add the entered folder or delete the selected one. The program will not allow you to add one folder twice.

### Editor Panel - Rules:
Supported actions:
- Add file;
- Delete file.

Supported types of rules:
- By extensions;
- By date of last use;
- By name (with regex support);
- All files.

You can add exceptions to each rule.

If you are working inside a folder and sorting into its subfolders, add all target folders to each other as exceptions. This will avoid cyclical checks.

When the main window is closed, the program is automatically minimized to the tray.  Use it to restore the program or permanently close it.

## Requirments
The program requires the C++17 standard and Qt6 to compile.

## Commit Description
| Name     | Description                                                     |
|----------|-----------------------------------------------------------------|
| feat     | Adding new functionality                                        |
| chore    | Changing dependencies                                           |
| style    | Editing the code style                                          |
| docs	   | Updating documentation                                          |
| refactor | Changes without adding new functionality or bug fixes           |
| fix	     | Bug fix                                                         |
| perf	   | Performance improvement                                         |
| revert   | Rolling back changes                                            |
