#ifndef PARSER_INI_HH_
# define PARSER_INI_HH_

# include <iostream>
# include <fstream>
# include <string>
# include "Debug.hh"

class ParserIni
{
public:
	ParserIni(const std::string& file);
	virtual ~ParserIni();

	// Parsing
	int getValue(const std::string& categorie, const std::string& variable);
	const std::string getText(const std::string& categorie, const std::string& variable);

	void setValue(const std::string& categorie, const std::string& variable, int value);
	void setText(const std::string& categorie, const std::string& variable, const std::string& value);

private:
	std::string _nameFile;
	std::fstream _file;
};

#endif /* !PARSER_INI_HH_*/