#include "Writer.h"

void CSVWriter::write(std::vector<Tutorial> tutorials)
{
	std::ofstream fout("tutorials.csv");
	for (auto& t : tutorials)
	{
		fout << t.getTitle() << ',' << t.getPresenter() << ',' << t.getLink() << ',' << t.getDuration() << ',' << t.getLikes() << '\n';
	}
	fout.close();
}

void CSVWriter::open()
{
	system("notepad tutorials.csv");
}

void HTMLWriter::write(std::vector<Tutorial> tutorials)
{
	std::ofstream fout("tutorials.html");
	fout << "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>Watchlist</title>\n\t</head>\n";
	fout << "\t<body>\n\t\t<table border=\"1\">\n\t\t<tr>\n";
	fout << "\t\t\t<td>Title</td>\n";
	fout << "\t\t\t<td>Presenter</td>\n";
	fout << "\t\t\t<td>Link</td>\n";
	fout << "\t\t\t<td>Duration</td>\n";
	fout << "\t\t</tr>\n";
	for (auto& t : tutorials)
	{
		fout << "<tr>\n";
		fout << "\t\t\t<td>" << t.getTitle() << "</td>\n";
		fout << "\t\t\t<td>" << t.getPresenter() << "</td>\n";
		fout << "\t\t\t<td><a href = \"" << t.getLink() << "\">Link</a></td>\n";
		fout << "\t\t\t<td>" << t.getDuration() << "</td>\n";
		fout << "</tr>\n";
	}
	fout << "\t\t</table>\n\t</body>\n</html>";
	fout.close();
}

void HTMLWriter::open()
{
	system("tutorials.html");
}
