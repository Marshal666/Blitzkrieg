///////////////////////////////////////////////////////////////////////////////
// This source file is part of the Script (Lua Wrapper) source distribution
// and is Copyright 2000 by Joshua C. Jensen (jjensen@workspacewhiz.com).
// The latest version may be obtained from http://www.workspacewhiz.com/.
//
// The code presented in this file may be freely used and modified for all
// non-commercial and commercial purposes.
///////////////////////////////////////////////////////////////////////////////
#include "Script.h"
#ifdef WIN32
#include <windows.h>
#undef GetObject
#endif
#include <stdio.h>
#include <string.h>

static int Script_LOG(lua_State* state)
{
	Script script(state);
	Script::Object obj = script.GetObject(script.GetTop());
#ifdef WIN32
	OutputDebugStringA(obj.GetString());
	OutputDebugStringA("\n");
#else
	printf("%s\n", obj.GetString());
#endif
	return 0;
}


static void FatalError()
{
	throw -1;
}


void Script::Register( const SRegFunction *pList )
{
	const SRegFunction *pCur = pList;
	for(; pCur->func && pCur->name; ++pCur )
		Register( pCur->name, pCur->func );
}

void Script::Init( bool initStandardLibrary) 
{
	m_ownState = false;

	m_state = lua_open(0);
	m_ownState = true;

// EPIK: for cut lua std lib
//	if (initStandardLibrary)
//		lua_baselibopen(m_state);

	// Register some basic functions with Lua.
//	Register("LOG", Script_LOG);
	Register("_ERRORMESSAGE", Script_LOG);
//	lua_setfatalerrorhandler(FatalError);
}

Script::Script(bool initStandardLibrary)
{
	Init( initStandardLibrary );
}


/**
	@return Retrieves the value at [section].[entry].  If either
		[section] or [entry] doesn't exist, [defaultValue] is returned.
**/
int Script::ConfigGetInteger(const char* section, const char* entry,
							 int defaultValue)
{
	return static_cast<int>(ConfigGetReal(section, entry, defaultValue));
}


/**
	@return Retrieves the value at [section].[entry].  If either
		[section] or [entry] doesn't exist, [defaultValue] is returned.
**/
float Script::ConfigGetReal(const char* section, const char* entry,
							double defaultValue)
{
	AutoBlock block(*this);

	Object obj = GetGlobal(section);
	if (obj.IsNil())
		return (float)defaultValue;
	obj = obj.GetByName(entry);
	if (obj.IsNumber())
		return obj.GetNumber();
	return (float)defaultValue;
}


/**
	@return Retrieves the value at [section].[entry].  If either
		[section] or [entry] doesn't exist, [defaultValue] is returned.
**/
const char* Script::ConfigGetString(const char* section, const char* entry,
									const char* defaultValue)
{
	AutoBlock block(*this);

	Object obj = GetGlobal(section);
	if (obj.IsNil())
		return defaultValue;
	obj = obj.GetByName(entry);
	if (obj.IsString())
		return obj.GetString();
	return defaultValue;
}


/**
	Assigns [value] to [section].[entry].
**/
void Script::ConfigSetInteger(const char* section, const char* entry, int value)
{
	AutoBlock block(*this);

	// section.entry = value
	// Difficult in code.  Do it this way.
	Object sectionTable = GetGlobal(section);

	// If the global table isn't there, then create it.
	if (sectionTable.IsNil())
	{
		sectionTable = GetGlobals().CreateTable(section);
	}

	sectionTable.SetNumber(entry, value);
}


/**
	Assigns [value] to [section].[entry].
**/
void Script::ConfigSetReal(const char* section, const char* entry, double value)
{
	AutoBlock block(*this);

	// section.entry = value
	// Difficult in code.  Do it this way.
	Object sectionTable = GetGlobal(section);

	// If the global table isn't there, then create it.
	if (sectionTable.IsNil())
	{
		sectionTable = GetGlobals().CreateTable(section);
	}

	sectionTable.SetNumber(entry, value);
}


/**
	Assigns [value] to [section].[entry].
**/
void Script::ConfigSetString(const char* section, const char* entry, const char* value)
{
	AutoBlock block(*this);

	// section.entry = value
	// Difficult in code.  Do it this way.
	Object sectionTable = GetGlobal(section);

	// If the global table isn't there, then create it.
	if (sectionTable.IsNil())
	{
		sectionTable = GetGlobals().CreateTable(section);
	}

	sectionTable.SetString(entry, value);
}


/**
	Adds [indentLevel] number of spaces to the file.
**/
static void IndentFile(FILE* file, unsigned int indentLevel)
{
	// Write out indentation.
	char spaces[500];
	for (unsigned int i = 0; i < indentLevel; ++i)
		spaces[i] = ' ';
	spaces[i] = 0;
	fputs(spaces, file);
}


/**
	Writes a Lua object to a text file.
**/
static void WriteObject(Script& script, FILE* file, const char* name,
						Script::Object value, unsigned int indentLevel)
{
	// If there is nothing in the variable, then don't write it.
	if (value.IsNil())
		return;

	// If the variable is user data or a function, then don't write it.
	if (value.IsUserData()  ||  value.IsFunction())
	{
		return;
	}

	using Script::Object;

	// Indent the line the number of spaces for the current indentation level.
	const unsigned int INDENT_SIZE = 4;
	const unsigned int indentSpaces = indentLevel * INDENT_SIZE;
	IndentFile(file, indentSpaces);
	
	// If the object has a name, write it out.
	if (name)
		fprintf(file, "%s = ", name);

	// If the object's value is a number, write it as a number.
	if (value.IsNumber())
		fprintf(file, "%.16g", value.GetNumber());

	// Or if the object's value is a string, write it as a quoted string.
	else if (value.IsString())
		fprintf(file, "\"%s\"", value.GetString());

	// Otherwise, see if the object's value is a table.
	else if (value.IsTable())
	{
		// Write the table header.
		fputs("\n", file);
		IndentFile(file, indentSpaces);
		fputs("{\n", file);

		// Rename, just for ease of reading.
		Script::Object table = value;

		// upperIndex is the upper index value of a sequential numerical array
		// items.
		int upperIndex = 1;
		bool wroteSemi = false;
		bool hasSequential = false;

		// Block to search for array items.
		{
			// Pop the stack state when done.
			Script::AutoBlock block(script);

			// Grab index 1 and index 2 of the table.
			Object value1 = table.GetByIndex(1);
			Object value2 = table.GetByIndex(2);

			// If they both exist, then there is a sequential list.
			if (!value1.IsNil()  &&  !value2.IsNil())
			{
				// Cycle through the list.
				bool firstSequential = true;
				for (; ; ++upperIndex)
				{
					// Restore the stack state each iteration.
					Script::AutoBlock block(script);

					// Try retrieving the table entry at upperIndex.
					Object value = table.GetByIndex(upperIndex);

					// If it doesn't exist, then exit the loop.
					if (value.IsNil())
						break;

					// Only add the comma and return if not on the first item.
					if (!firstSequential)
						fputs(",\n", file);
					
					// Write the object as an unnamed entry.
					WriteObject(script, file, NULL, value, indentLevel + 1);

					// We've definitely passed the first item now.
					firstSequential = false;
				}
			}
		}

		// Did we find any sequential table values?
		if (upperIndex > 1)
		{
			hasSequential = true;
		}
		
		// Cycle through the table.
		int i;
		script.PushNil();
		while ((i = script.Next(table.GetStackIndex())) != 0)
		{
			char keyName[255];

			// Retrieve the table entry's key and value.
			Object key = script.GetObject(script.GetTop() - 1);
			Object value = script.GetObject(script.GetTop());

			// Is the key a number?
			if (key.IsNumber())
			{
				// Yes, were there sequential array items in this table?
				if (hasSequential)
				{
					// Is the array item's key an integer?
					float realNum = key.GetNumber();
					int intNum = (int)realNum;
					if (realNum == (float)intNum)
					{
						// Yes.  Is it between 1 and upperIndex?
						if (intNum >= 1  &&  intNum < upperIndex)
						{
							// We already wrote it as part of the sequential
							// list.
							script.Pop();
							continue;
						}
					}
				}

				// Build the table entry name for the number.
				sprintf(keyName, "[%.16g]", key.GetNumber());
			}
			else
			{
				// Build the table entry name for the string key name.
				strcpy(keyName, key.GetString());
			}

			// If we wrote a sequential list, the value we're about to write
			// is not nil, and we haven't written the semicolon to separate
			// the sequential table entries from the keyed table entries...
			if (hasSequential  &&  !value.IsNil()  &&  !wroteSemi)
			{
				// Then add a comma (for good measure) and the semicolon.
				fputs(", ;\n", file);
				wroteSemi = true;
			}

			// Write the table entry.
			WriteObject(script, file, keyName, value, indentLevel + 1);

			// Add a comma after the table entry.
			fputs(",\n", file);

			// Go to the next item.
			script.Pop();
		}

		// If we wrote a sequential list and haven't written a semicolon, then
		// there were no keyed table entries.  Just write the final comma.
		if (hasSequential  &&  !wroteSemi)
		{
			fputs(",\n", file);
		}
		
		// Indent, with the intent of closing up the table.
		IndentFile(file, indentSpaces);

		// If the indentation level is 0, then we're at the root position.
		if (indentLevel == 0)
		{
			// Add a couple extra returns for readability's sake.
			fputs("}\n\n", file);
		}
		else
		{
			// Close the table.  The comma is written when WriteObject()
			// returns from the recursive call.
			fputs("}", file);
		}
	}

	// If the indentation level is at the root, then add a return to separate
	// the lines.
	if (indentLevel == 0)
	{
		fputs("\n", file);
	}
}


/**
	Save the complete script state.
**/
void Script::SaveText(const char* filename)
{
	// Open the text file to write the script state to.
	FILE* file = fopen(filename, "wt");

	// For safety, just in case we leave something behind on the script stack.
	AutoBlock block(*this);

	// Run through all the globals.
	int i;
	Object table = GetGlobals();
	PushNil();
	while ((i = Next(table.GetStackIndex())) != 0)
	{
		// Retrieve the global's key and value.
		Object key = GetObject(GetTop() - 1);
		Object value = GetObject(GetTop());

		// Save the global to the text file.
		if (strcmp(key.GetString(), "_VERSION") != 0)
		{
			WriteObject(*this, file, key.GetString(), value, 0);
		}

		// Go to the next global.
		Pop();
	}

	// Close the text file.
	fclose(file);
}
