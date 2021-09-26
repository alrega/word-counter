## Build & run

Open Qt Creator, open CMakeLists.txt, configure project for desktop application.

Targets:
- **app** - UI application
- **test_ranked_words**, **test_dictionary**  - unit tests for business logic

Build target *app* and run it.

## Project directories

- 3rdparty - Google Test library source code as is
- business - source files that implement business logic            
- tests - unit tests for business logic
- user - UI application

## Supported text files

Since business logic is not Unicode, supported text on input is limited to:

- ANSI text
- UTF-8 text, but only symbols available in the current locale

Sample files are in 'tests' directory:

- NEWS - English text (OpenSSL new file)
- Russian.utf8.txt - sample of Cyrillict UTF-8 encoded text
- vm.txt - large cyrillic text
